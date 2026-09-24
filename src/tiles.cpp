#include "tiles.hpp"
#include "gamemanager.hpp"
#include "graphics/drawboard.hpp"
#include <SDL3/SDL_pixels.h>
SDL_Color Tile::getColor() {
    switch (state) {
        case HIDDEN_BLANK:
        case HIDDEN_MINE:
        case FLAGGED_BLANK:
        case FLAGGED_MINE:
            if (altColor) {
                return colorHex(0xa2d149);
            }
            else {
                return colorHex(0xaad751);
            }
        case REVEALED_MINE:
        return SDL_Color{0xFF,0,0,0xFF};
        case REVEALED_BLANK:
            if (altColor) {
                return colorHex(0xd7b899);
            }
            else {
                return colorHex(0xe5c29f);
            }
    }
    return SDL_Color{0,0,0,0xFF};
}

GameProgress Tile::reveal () {
    TileState newstates[6] = {REVEALED_MINE, REVEALED_BLANK, FLAGGED_MINE, FLAGGED_BLANK, REVEALED_MINE, REVEALED_BLANK};
    state = newstates[state];
    if (state == REVEALED_MINE) return Lose;
    return Playing;
}
void Tile::flag () {
    TileState newstates[6] = {FLAGGED_MINE, FLAGGED_BLANK, HIDDEN_MINE, HIDDEN_BLANK, REVEALED_MINE, REVEALED_BLANK};
    state = newstates[state];
}

bool Tile::isFlagged () {
    switch (state) {
        case FLAGGED_BLANK:
        case FLAGGED_MINE:
            return true;
        default:
            return false;
    }
}

bool Tile::isMine () {
    switch (state) {
        case HIDDEN_MINE:
        case FLAGGED_MINE:
        case REVEALED_MINE:
            return true;
        default:
            return false;
    }
}

bool Tile::isRevealed () {
    switch (state) {
        case REVEALED_MINE:
        case REVEALED_BLANK:
            return true;
        default:
            return false;
    }
}