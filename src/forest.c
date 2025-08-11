#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "config.h"

// starts the forest with a causal pattern
void init_grid(int *grid)
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        grid[i] = ((float)rand() / RAND_MAX < TREE_T0_SPAWN_RATE) ? TREE : EMPTY;
    }
}

// updates grid state
void update_grid(const int *current, int *next)
{
    // current is T forest
    // next is T+1 forest

    /*
    Schema of coordinates to check in the forest:
        (x-1, y-1)  (x, y-1)  (x+1, y-1)

        (x-1,   y)   (x, y)   (x+1,   y)

        (x-1, y+1)  (x, y+1)  (x+1, y+1)    
    */

    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        switch (current[i])
        {
        case FIRE:
            // fire ends in T+1
            next[i] = EMPTY;
            break;

        case TREE:
            // casual ignition probability
            next[i] = ((float)rand() / RAND_MAX < FIRE_IGNITION_RATE) ? FIRE : TREE;
            if (next[i] == FIRE)
                break;

            // checks adjacent fires
            if(is_neighbor_on_fire(current, i, GET_X(i) - 1, GET_Y(i) - 1)) { next[i] = FIRE; break; }
            if(is_neighbor_on_fire(current, i, GET_X(i)    , GET_Y(i) - 1)) { next[i] = FIRE; break; }
            if(is_neighbor_on_fire(current, i, GET_X(i) + 1, GET_Y(i) - 1)) { next[i] = FIRE; break; }
            if(is_neighbor_on_fire(current, i, GET_X(i) - 1, GET_Y(i)    )) { next[i] = FIRE; break; }
            if(is_neighbor_on_fire(current, i, GET_X(i) + 1, GET_Y(i)    )) { next[i] = FIRE; break; }
            if(is_neighbor_on_fire(current, i, GET_X(i) - 1, GET_Y(i) + 1)) { next[i] = FIRE; break; }
            if(is_neighbor_on_fire(current, i, GET_X(i)    , GET_Y(i) + 1)) { next[i] = FIRE; break; }
            if(is_neighbor_on_fire(current, i, GET_X(i) + 1, GET_Y(i) + 1)) { next[i] = FIRE; break; }  
            break;

        case EMPTY:
            // can spawn a tree
            next[i] = ((float)rand() / RAND_MAX < TREE_SPAWN_RATE) ? TREE : EMPTY;
            break;
        }
    }
}

// checks if neighbor tree is burning
int is_neighbor_on_fire(const int *current, int current_i, int x_to_check, int y_to_check)
{
    if (!FOREST_MARGIN_1D_CHECK(COORDINATES_TO_INDEX(x_to_check, y_to_check)))
        return 0;

        /*
            blocking horizontal wrap-around.
            conditions to satisfy:
            x ∈ [cx - 1, cx + 1]
            y ∈ [cy - 1, cy + 1]
        */

    if (x_to_check < GET_X(current_i) - 1 ||
        x_to_check > GET_X(current_i) + 1 ||
        y_to_check < GET_Y(current_i) - 1 ||
        y_to_check > GET_Y(current_i) + 1)
        return 0;

    int index = COORDINATES_TO_INDEX(x_to_check, y_to_check);
    return current[index] == FIRE;
}

// grid rendering logic

void render_grid(const int *grid)
{
    static SDL_Window *window = NULL;
    static SDL_Renderer *renderer = NULL;
    static int initialized = 0;

    if (!initialized)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            SDL_Log("SDL_Init Error: %s", SDL_GetError());
            return; // SDL is needed, return if not loaded
        }

        window = SDL_CreateWindow("Forest Fire",
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE,
                                  SDL_WINDOW_SHOWN);
        if (!window) {
            SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
            SDL_Quit();
            return;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer) {
            SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
            SDL_DestroyWindow(window);
            SDL_Quit();
            return;
        }

        initialized = 1;
    }

    // Cleaning the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Painting cells with proper color
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            SDL_Rect rect = {x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE};
            int cell = grid[y * WIDTH + x];

            switch (cell)
            {
                case EMPTY:
                    SDL_SetRenderDrawColor(renderer, 65, 34, 6, 255); // brown
                    break;
                case TREE:
                    SDL_SetRenderDrawColor(renderer, 13, 135, 71, 255); // green
                    break;
                case FIRE:
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
                    break;
                default:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    break;
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
}

// frame delay (needed?)
void post_frame_delay(void);
