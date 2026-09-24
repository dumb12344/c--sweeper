#pragma once
#include <SDL3/SDL_pixels.h>

enum GameProgress : int; 

enum TileState {
    HIDDEN_MINE,
    HIDDEN_BLANK,
    FLAGGED_MINE,
    FLAGGED_BLANK,
    REVEALED_MINE,
    REVEALED_BLANK
};

struct Tile {
    TileState state;
    int surroundingMines;
    bool altColor;
    SDL_Color getColor ();
    public:
    GameProgress reveal ();
    void flag ();
    bool isMine ();
    bool isFlagged ();
    bool isRevealed ();
};