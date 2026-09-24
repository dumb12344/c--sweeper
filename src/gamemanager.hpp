#pragma once
#include <vector>

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

#include "tiles.hpp"
extern std::vector<std::vector<Tile>> tiles;