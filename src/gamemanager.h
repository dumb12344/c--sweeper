#pragma once
#include <vector>
#include "tiles.h"

enum GameProgress : int
{
    Initializing,
    Playing,
    Lose,
    Win
};

struct GameState
{
    GameProgress progress = Initializing;
    int remainingTiles = 0;
    static GameState& getInstance();
};

bool outOfBounds(int x, int y);
void init();
void initSurroundingMines();
void reveal(int x, int y);
void revealNoSpread(int x, int y);
void flag(int x, int y);

struct Tile;

extern std::vector<std::vector<Tile>> tiles;
