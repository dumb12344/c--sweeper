#pragma once
#include <vector>
#include "tiles.h"

enum GameProgress : int {
    Initializing,
    Playing,
    Lose,
    Win
};

struct GameState {
    GameProgress progress = Initializing;
    int remainingMines = 0;
};

extern GameState gameState;
bool outOfBounds (int x, int y);
void init ();
void reveal (int x, int y);
void revealNoSpread (int x, int y);
void flag (int x, int y);

struct Tile;

extern std::vector<std::vector<Tile>> tiles;