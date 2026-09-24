#include "graphics/drawboard.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cmath>
#include "main.hpp"
#include "gamemanager.hpp"
#include "constants.hpp"

int main() {
    SDL_Window* window;
    SDL_Renderer* renderer;
    init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("C++Sweeper", 1920, 1080, 0, &window, &renderer);
    TTF_Init();
    SDL_RenderClear(renderer);
    SDL_ShowWindow(window);
    bool running = true;
    while (running) {
        SDL_Event event;
        if (gameState.remainingMines <= 0) gameState.progress = Win;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_M) {
                for (int x = 0; x < constants::SIZE_X; x++) {
                    for (int y = 0; y < constants::SIZE_Y; y++) {
                        if (!tiles[x][y].isMine()) revealNoSpread(x, y);
                    }
                }
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                int tileX = floor(event.button.x / constants::TILE_SIZE);
                int tileY = floor(event.button.y / constants::TILE_SIZE);
                if (outOfBounds(tileX, tileY)) continue;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (gameState.progress != Playing) {
                        init();
                    }
                    else {
                        reveal(tileX, tileY);
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    flag(tileX, tileY);
                }
            }
            DrawBoard::draw(renderer);
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}