#include "drawboard.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <cstdlib>
#include "../constants.h"
#include "../gamemanager.h"
#include "../tiles.h"
#include "cache.h"

using namespace constants;

static void drawRevealed(SDL_Renderer * renderer)
{
    for (int x = 0; x < SIZE_X; x++) {
        for (int y = 0; y < SIZE_Y; y++) {
            Tile& tile = tiles[x][y];
            if (!tile.isRevealed()) continue;
            SDL_Color color = tile.getColor();
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_FRect tileRect = {(float) x * TILE_SIZE + OFFSET_X, (float) y * TILE_SIZE + OFFSET_Y, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }
}

static void drawOutline(SDL_Renderer * renderer)
{
    for (int x = 0; x < SIZE_X; x++) {
        for (int y = 0; y < SIZE_Y; y++) {
            Tile& tile = tiles[x][y];
            if (tile.isRevealed()) continue;
            SDL_Color color = colorHex(0x87af3a);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_FRect tileRect = {
                (float) x * TILE_SIZE - (float) TILE_SIZE / 15 + OFFSET_X,
                (float) y * TILE_SIZE - (float) TILE_SIZE / 15 + OFFSET_Y,
                (TILE_SIZE + TILE_SIZE / 7.5f),
                (TILE_SIZE + TILE_SIZE / 7.5f)
            };
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }
}

static void drawUnrevealed(SDL_Renderer * renderer)
{
    for (int x = 0; x < SIZE_X; x++) {
        for (int y = 0; y < SIZE_Y; y++) {
            Tile& tile = tiles[x][y];
            if (tile.isRevealed()) continue;
            SDL_Color color = tile.getColor();
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_FRect tileRect = {(float) x * TILE_SIZE + OFFSET_X, (float) y * TILE_SIZE + OFFSET_Y, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }
}

static void drawSelected(SDL_Renderer * renderer, bool underOutline, float mouseX, float mouseY)
{
    int mouseTileX = mouseX / TILE_SIZE;
    int mouseTileY = mouseY / TILE_SIZE;
    if (outOfBounds(mouseTileX, mouseTileY)) return;
    Tile& tile = tiles[mouseTileX][mouseTileY];
    if (underOutline && !tile.isRevealed()) return;
    else if (!underOutline && tile.isRevealed()) return;
    if (tile.surroundingMines > 0 || !tile.isRevealed()) {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF * 0.2);
        SDL_FRect tileRect = {(float) mouseTileX * TILE_SIZE + OFFSET_X, (float) mouseTileY * TILE_SIZE + OFFSET_Y, TILE_SIZE, TILE_SIZE};
        SDL_RenderFillRect(renderer, &tileRect);
    }
}

static void drawExtras(SDL_Renderer * renderer)
{
    for (int x = 0; x < SIZE_X; x++) {
        for (int y = 0; y < SIZE_Y; y++) {
            Tile& tile = tiles[x][y];
            if (tile.isFlagged()) {
                SDL_FRect destination_rect = {(float) x * TILE_SIZE + OFFSET_X, (float) y * TILE_SIZE + OFFSET_Y, TILE_SIZE, TILE_SIZE};
                SDL_RenderTexture(renderer, cache::flag_texture, NULL, &destination_rect);
            }

            if (tile.surroundingMines > 0 && tile.isRevealed() && !tile.isMine()) {
                SDL_Texture * texture = cache::number_textures[tile.surroundingMines];
                SDL_FRect destination_rect = {
                    (float) x * TILE_SIZE + (TILE_SIZE - texture -> w) / 2.0f + OFFSET_X,
                    (float) y * TILE_SIZE + (TILE_SIZE - texture -> h) / 2.0f + OFFSET_Y,
                    (float) texture -> w,
                    (float) texture -> h
                };
                SDL_RenderTexture(renderer, texture, NULL, &destination_rect);
            }
        }
    }

    if (GameState::getInstance().progress == Lose || GameState::getInstance().progress == Win) {
        SDL_Texture * texture = GameState::getInstance().progress == Lose ? cache::lose_text : cache::win_text;
        SDL_FRect destination_rect = {
            (float) (constants::SCREEN_WIDTH - texture -> w) / 2.0f,
            (float) (constants::SCREEN_HEIGHT - texture -> h) / 2.0f,
            (float) texture -> w,
            (float) texture -> h
        };
        SDL_RenderTexture(renderer, texture, NULL, &destination_rect);
    }
}

void drawBoard(SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    float mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    mouseX -= OFFSET_X;
    mouseY -= OFFSET_Y;

    drawRevealed(renderer);
    drawSelected(renderer, true, mouseX, mouseY);
    drawOutline(renderer);
    drawUnrevealed(renderer);
    drawSelected(renderer, false, mouseX, mouseY);
    drawExtras(renderer);

    SDL_RenderPresent(renderer);
}

SDL_Color colorHex(Uint32 code)
{
    return {
        (Uint8) ((code >> 16) & 0xFF),
        (Uint8) ((code >> 8)  & 0xFF),
        (Uint8) ((code)       & 0xFF),
        0xFF
    };
};
