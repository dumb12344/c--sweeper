#pragma once
#include "graphics/drawboard.h"
#include <SDL3/SDL_pixels.h>

namespace constants {
    extern int SIZE_X;
    extern int SIZE_Y;
    extern int MINE_COUNT;
    extern float TILE_SIZE;
    extern int SCREEN_WIDTH;
    extern int SCREEN_HEIGHT;
    extern int OFFSET_X;
    extern int OFFSET_Y;
    const Uint32 NUMBER_COLORS[] = {
        0xffffff,
        0x1976d2,
        0x388e3c,
        0xd32f2f,
        0x7b1fa2,
        0xff8f00,
        0x0097a7,
        0x424242,
        0x9e9e9e
    };
}