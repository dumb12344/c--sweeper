#include "drawboard.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <string>
#include "../constants.hpp"
#include "../gamemanager.hpp"
#include "../tiles.hpp"
using namespace constants;


void drawRevealed (SDL_Renderer * renderer) {
    for (int x = 0; x < SIZE_X; x++) {
        for (int y = 0; y < SIZE_Y; y++) {
            Tile tile = tiles[x][y];
            if (!tile.isRevealed()) continue;
            SDL_Color color = tile.getColor();
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_FRect tileRect = {(float) x * TILE_SIZE, (float) y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }
}

void drawOutline (SDL_Renderer * renderer) {
    for (int x = 0; x < SIZE_X; x++) {
        for (int y = 0; y < SIZE_Y; y++) {
            Tile tile = tiles[x][y];
            if (tile.isRevealed()) continue;
            SDL_Color color = colorHex(0x87af3a);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_FRect tileRect = {
                (float) x * TILE_SIZE - (float) TILE_SIZE / 15,
                (float) y * TILE_SIZE - (float) TILE_SIZE / 15,
                (TILE_SIZE + TILE_SIZE / 7.5f),
                (TILE_SIZE + TILE_SIZE / 7.5f)
            };
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }
}

void drawUnrevealed (SDL_Renderer * renderer) {
    for (int x = 0; x < SIZE_X; x++) {
        for (int y = 0; y < SIZE_Y; y++) {
            Tile tile = tiles[x][y];
            if (tile.isRevealed()) continue;
            SDL_Color color = tile.getColor();
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_FRect tileRect = {(float) x * TILE_SIZE, (float) y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }
}

void drawExtras (SDL_Renderer * renderer, TTF_Font * font, SDL_Texture * flag_texture) {
    for (int x = 0; x < SIZE_X; x++) {
        for (int y = 0; y < SIZE_Y; y++) {
            Tile tile = tiles[x][y];
            SDL_FRect destination_rect = {(float) x * TILE_SIZE, (float) y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if (tile.isFlagged()) {
                SDL_RenderTexture(renderer, flag_texture, NULL, &destination_rect);
            }

            if (tile.surroundingMines > 0 && tile.isRevealed() && !tile.isMine()
        ) {
                SDL_Surface * surface = TTF_RenderText_Blended(font, std::to_string(tile.surroundingMines).c_str(), 0, NUMBER_COLORS[tiles[x][y].surroundingMines]);
                destination_rect = {
                    (float) x * TILE_SIZE + (TILE_SIZE - surface -> w) / 2.0f,
                    (float) y * TILE_SIZE + (TILE_SIZE - surface -> h) / 2.0f,
                    (float) surface -> w,
                    (float) surface -> h
                };
                SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_DestroySurface(surface);
                SDL_RenderTexture(renderer, texture, NULL, &destination_rect);
                SDL_DestroyTexture(texture);
            }
        }
    }

    if (gameState.progress == Lose) {
        SDL_Surface * surface = TTF_RenderText_Blended(font, "You Lose!", 0, {0xFF, 0x00, 0x00, 0xFF});
        SDL_FRect destination_rect = {
            (float) (1920 - surface -> w) / 2.0f,
            (float) (1080 - surface -> h) / 2.0f,
            (float) surface -> w,
            (float) surface -> h
        };
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        SDL_RenderTexture(renderer, texture, NULL, &destination_rect);
        SDL_DestroyTexture(texture);
    }

    if (gameState.progress == Win) {
        SDL_Surface * surface = TTF_RenderText_Blended(font, "You Win!", 0, {0x88, 0x55, 0x00, 0xFF});
        SDL_FRect destination_rect = {
            (float) (1920 - surface -> w) / 2.0f,
            (float) (1080 - surface -> h) / 2.0f,
            (float) surface -> w,
            (float) surface -> h
        };
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        SDL_RenderTexture(renderer, texture, NULL, &destination_rect);
        SDL_DestroyTexture(texture);
    }
}

static const unsigned char imageData[] = {
    #embed "../../assets/flag_icon.png"
};

static const unsigned char fontData[] = {
    #embed "../../assets/google_sans.otf"
};

void DrawBoard::draw (SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_IOStream * imageStream = SDL_IOFromConstMem(imageData, sizeof(imageData));
    SDL_Surface * surface = IMG_Load_IO(imageStream, true);
    SDL_Texture * flag_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_IOStream * fontStream = SDL_IOFromConstMem(fontData, sizeof(fontData));
    TTF_Font * font = TTF_OpenFontIO(fontStream, true, TILE_SIZE);
    if (!flag_texture) {return;}
    drawRevealed(renderer);
    drawOutline(renderer);
    drawUnrevealed(renderer);
    drawExtras(renderer, font, flag_texture);

    SDL_RenderPresent(renderer);
    TTF_CloseFont(font);
    SDL_DestroyTexture(flag_texture);
}
