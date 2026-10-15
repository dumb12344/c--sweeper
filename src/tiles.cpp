#include "tiles.h"
#include "gamemanager.h"
#include "graphics/drawboard.h"
#include <SDL3/SDL_pixels.h>

SDL_Color Tile::getColor()
{
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
        return SDL_Color{0xFF, 0, 0, 0xFF};
        case REVEALED_BLANK:
            if (altColor) {
                return colorHex(0xd7b899);
            }
            else {
                return colorHex(0xe5c29f);
            }
    }
    return SDL_Color{0, 0, 0, 0xFF};
}

GameProgress Tile::reveal()
{
    constexpr TileState newStates[6] = {REVEALED_MINE, REVEALED_BLANK, FLAGGED_MINE, FLAGGED_BLANK, REVEALED_MINE, REVEALED_BLANK};
    state = newStates[state];
    if (state == REVEALED_MINE) return Lose;
    else return Playing;
}

void Tile::flag()
{
    constexpr TileState newStates[6] = {FLAGGED_MINE, FLAGGED_BLANK, HIDDEN_MINE, HIDDEN_BLANK, REVEALED_MINE, REVEALED_BLANK};
    state = newStates[state];
}

void Tile::toggleRevealed() {
    constexpr TileState newStates[6] = {REVEALED_MINE, REVEALED_BLANK, HIDDEN_MINE, HIDDEN_BLANK, HIDDEN_MINE, HIDDEN_BLANK};
    state = newStates[state];
}

void Tile::toggleMine() {
    constexpr TileState newStates[6] = {HIDDEN_BLANK, HIDDEN_MINE, FLAGGED_BLANK, FLAGGED_MINE, REVEALED_BLANK, REVEALED_MINE};
    state = newStates[state];
}

bool Tile::isFlagged()
{
    switch (state) {
        case FLAGGED_BLANK:
        case FLAGGED_MINE:
            return true;
        default:
            return false;
    }
}

bool Tile::isMine()
{
    switch (state) {
        case HIDDEN_MINE:
        case FLAGGED_MINE:
        case REVEALED_MINE:
            return true;
        default:
            return false;
    }
}

bool Tile::isRevealed()
{
    switch (state) {
        case REVEALED_MINE:
        case REVEALED_BLANK:
            return true;
        default:
            return false;
    }
}
