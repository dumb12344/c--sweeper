#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
class DrawBoard {
    public:
    static void draw (SDL_Renderer * renderer);
};

SDL_Color colorHex (Uint32 code);