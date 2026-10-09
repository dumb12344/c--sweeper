#include "cache.h"
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "../constants.h"

namespace cache {
    SDL_Texture * numberCache[10];
    TTF_Font * font;
    SDL_Texture * flag_texture;

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
        SDL_IOStream * fontStream = SDL_IOFromConstMem(fontData, sizeof(fontData));
        cache::font = TTF_OpenFontIO(fontStream, true, constants::TILE_SIZE);
        if (!cache::flag_texture) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Flag texture failed to load");
            exit(1);
        }
        for (int i = 0; i <= 9; i++) {
            SDL_Surface * surface = TTF_RenderText_Blended(font, std::to_string(i).c_str(), 0, colorHex(constants::NUMBER_COLORS[i]));
            numberCache[i] = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_DestroySurface(surface);
        }
    }
    
    void destroyCache(SDL_Renderer * renderer)
    {
        for (int i = 0; i <= 9; i++) {
            SDL_DestroyTexture(numberCache[i]);
        }
        TTF_CloseFont(cache::font);
        SDL_DestroyTexture(cache::flag_texture);
    }
}