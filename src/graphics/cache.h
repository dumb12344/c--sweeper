#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace cache {
    extern SDL_Texture * numberCache[10];
    extern TTF_Font * font;
    extern SDL_Texture * flag_texture;

    void initCache(SDL_Renderer * renderer);
    void destroyCache(SDL_Renderer * renderer);
}