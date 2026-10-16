#include "cache.h"
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "../constants.h"
#include <stdlib.h>

namespace cache
{
    SDL_Texture * number_textures[10];
    TTF_Font * font;
    SDL_Texture * flag_texture;
    SDL_Texture * lose_text;
    SDL_Texture * win_text;

    static const uint8_t imageData[] = {
        #embed "../../assets/flag_icon.png"
    };

    static const uint8_t fontData[] = {
        #embed "../../assets/google_sans.otf"
    };

    void initCache(SDL_Renderer * renderer)
    {
        SDL_IOStream * imageStream = SDL_IOFromConstMem(imageData, sizeof(imageData));
        SDL_Surface * surface = IMG_Load_IO(imageStream, true);
        cache::flag_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        if (!cache::flag_texture)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Flag texture failed to load");
            exit(1);
        }

        SDL_IOStream * fontStream = SDL_IOFromConstMem(fontData, sizeof(fontData));
        cache::font = TTF_OpenFontIO(fontStream, true, constants::TILE_SIZE);

        for (int i = 0; i <= 9; i++)
        {
            SDL_Surface * surface = TTF_RenderText_Blended(font, std::to_string(i).c_str(), 0, colorHex(constants::NUMBER_COLORS[i]));
            number_textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_DestroySurface(surface);
        }

        TTF_SetFontSize(cache::font, (float) constants::SCREEN_WIDTH / 10);
        SDL_Surface * lose_surface = TTF_RenderText_Blended(
            cache::font,
            "You Lose!",
            0,
            SDL_Color{0xaa, 0x00, 0x00, 0xFF}
        );
        SDL_Surface * win_surface = TTF_RenderText_Blended(
            cache::font,
            "You Win!",
            0,
            SDL_Color{0x88, 0x55, 0x00, 0xFF}
        );
        lose_text = SDL_CreateTextureFromSurface(renderer, lose_surface);
        win_text = SDL_CreateTextureFromSurface(renderer, win_surface);
        SDL_DestroySurface(lose_surface);
        SDL_DestroySurface(win_surface);
        TTF_SetFontSize(cache::font, constants::TILE_SIZE);
    }

    void destroyCache(SDL_Renderer * renderer)
    {
        for (int i = 0; i <= 9; i++)
        {
            SDL_DestroyTexture(cache::number_textures[i]);
        }
        TTF_CloseFont(cache::font);
        SDL_DestroyTexture(cache::flag_texture);
        SDL_DestroyTexture(cache::lose_text);
        SDL_DestroyTexture(cache::win_text);
    }
}
