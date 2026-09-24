#include "graphics/drawboard.hpp"
#include <SDL3/SDL_pixels.h>
namespace constants {
    static const int SIZE_X = 10;
    static const int SIZE_Y = 8;
    static const int MINE_COUNT = 10;
    static const int TILE_SIZE = 100;
    static const SDL_Color NUMBER_COLORS[] = {
        colorHex(0xffffff),
        colorHex(0x1976d2),
        colorHex(0x388e3c),
        colorHex(0xd32f2f),
        colorHex(0x7b1fa2),
        colorHex(0xff8f00),
        colorHex(0x0097a7),
        colorHex(0x424242),
        colorHex(0x9e9e9e)
    };
}