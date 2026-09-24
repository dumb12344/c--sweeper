#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
class DrawBoard {
    public:
    static void draw (SDL_Renderer * renderer);
};

inline static SDL_Color colorHex (Uint32 code) {
    return {
        static_cast<Uint8>((code >> 16) & 0xFF),
        static_cast<Uint8>((code >> 8)  & 0xFF),
        static_cast<Uint8>((code)       & 0xFF),
        0xFF
    };
};
