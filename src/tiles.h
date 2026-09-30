#pragma once
#include <SDL3/SDL_pixels.h>
#include "gamemanager.h"

enum TileState {
    HIDDEN_MINE,
    HIDDEN_BLANK,
    FLAGGED_MINE,
    FLAGGED_BLANK,
    REVEALED_MINE,
    REVEALED_BLANK
};

enum GameProgress : int; 

struct Tile {
    TileState state;
    int surroundingMines;
    bool altColor;
    SDL_Color getColor ();
    GameProgress reveal ();
    void flag ();
    bool isMine ();
    bool isFlagged ();
    bool isRevealed ();
};