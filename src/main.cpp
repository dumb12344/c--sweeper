#include "graphics/drawboard.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cmath>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include "gamemanager.h"
#include "constants.h"
#include <unistd.h>

float constants::TILE_SIZE = 50;
int constants::SCREEN_WIDTH = 50;
int constants::SCREEN_HEIGHT = 50;
int constants::SIZE_X = 10;
int constants::SIZE_Y = 8;
int constants::MINE_COUNT = 10;
// const int SIZE_X = 10;
// const int SIZE_Y = 8;
// const int MINE_COUNT = 10;
// const int SIZE_X = 18;
// const int SIZE_Y = 14;
// const int MINE_COUNT = 40;
// const int SIZE_X = 24;
// const int SIZE_Y = 20;
// const int MINE_COUNT = 99;

int main (int argCount, char **argValues) {
    if (argCount > 1) {
        int opt;
        while ((opt = getopt(argCount, argValues, "x:y:c:")) != -1) {
            switch (opt) {
            case 'x':
                constants::SIZE_X = atoi(optarg);
                break;
            case 'y':
                constants::SIZE_Y = atoi(optarg);
                break;
            case 'c':
                constants::MINE_COUNT = atoi(optarg);
                break;
            default:
                SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Usage: %s [-x xsize] [-y ysize] [-c minecount]\n", argValues[0]);
                return 1;
            }
        }
    }
    
    init();
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Rect displayRect;
    SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
    SDL_GetDisplayBounds(displayID, &displayRect);
    constants::SCREEN_WIDTH = displayRect.w;
    constants::SCREEN_HEIGHT = displayRect.h;
    constants::TILE_SIZE = std::min((float) displayRect.h / constants::SIZE_Y, (float) displayRect.w / constants::SIZE_X);
    
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_CreateWindowAndRenderer("C++Sweeper", displayRect.w, displayRect.h, 0, &window, &renderer);
    SDL_RenderClear(renderer);
    SDL_ShowWindow(window);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

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
            
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_R) {
                init();
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