#include <cstdlib>
#include <iostream>
#include <vector>
#include "gamemanager.hpp"
#include "constants.hpp"
#include "tiles.hpp"

std::vector<std::vector<Tile>> tiles;
GameState gameState;

bool outOfBounds (int x, int y) {
    return (x < 0 || x >= constants::SIZE_X || y < 0 || y >= constants::SIZE_Y);
}

void initTiles () {
    tiles = std::vector<std::vector<Tile>>(constants::SIZE_X);
    for (int x = 0; x < constants::SIZE_X; x++) {
        tiles[x] = std::vector<Tile>(constants::SIZE_Y);
        for (int y = 0; y < constants::SIZE_Y; y++) {
            bool alt_color = (x % 2 == 0) ^ (y % 2 == 0);
            tiles[x][y] = Tile {TileState::HIDDEN_BLANK, 0, alt_color};
        }
    }
}

void initMines () {
    srand(time(0));
    int remainingMines = constants::MINE_COUNT;
    while (remainingMines > 0) {
        int randX = rand() % constants::SIZE_X;
        int randY = rand() % constants::SIZE_Y;
        if (tiles[randX][randY].state == HIDDEN_BLANK) {
            tiles[randX][randY].state = HIDDEN_MINE;
            remainingMines--;
        }
    }
    gameState.remainingMines = constants::SIZE_X * constants::SIZE_Y - constants::MINE_COUNT;
}

void initSurroundingMines () {
    for (int x = 0; x < constants::SIZE_X; x++) {
        for (int y = 0; y < constants::SIZE_Y; y++) {
            int surroundingMines = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (outOfBounds(x + dx, y + dy)) continue;
                    if (tiles[x + dx][y + dy].isMine()) surroundingMines++;
                }
            }
            tiles[x][y].surroundingMines = surroundingMines;
        }
    }
}

void init () {
    gameState.progress = Initializing;
    initTiles();
    initMines();
    initSurroundingMines();
    std::cout << "Initialized" << std::endl;
    gameState.progress = Playing;
}

void reveal (int x, int y) {
    if (gameState.progress != Playing) return;
    if (tiles[x][y].isRevealed()) return;
    revealNoSpread(x, y);
    if (tiles[x][y].surroundingMines == 0) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (outOfBounds(x + dx, y + dy)) continue;
                if (dx == 0 && dy == 0) continue;
                reveal(x + dx, y + dy);
            }
        }
    }
    if (gameState.progress == Lose) {
        for (int x1 = 0; x1 < constants::SIZE_X; x1++) {
            for (int y1 = 0; y1 < constants::SIZE_Y; y1++) {
                if (x1 == x && y1 == y) continue;
                if (tiles[x1][y1].isMine()) revealNoSpread(x1, y1);
            }
        }
    }
}

void revealNoSpread (int x, int y) {
    gameState.progress = tiles[x][y].reveal();
    if (tiles[x][y].state == REVEALED_BLANK) gameState.remainingMines --;
}

void flag (int x, int y) {
    if (gameState.progress != Playing) return;
    tiles[x][y].flag();
}