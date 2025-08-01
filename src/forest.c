#ifndef FOREST_H
#define FOREST_H

#include <stdlib.h>
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
    //(x-1,y-1) (x, y-1) (x+1,y-1)
    //(x-1,y)   (x, y)   (x+1,y)
    //(x-1,y+1) (x, y+1) (x+1,y+1)
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
    if (!FOREST_MARGIN_CHECK(x_to_check, y_to_check))
        return 0;

    // blocking horizontal wrap-around:
    // conditions:
    // x ∈ [cx - 1, cx + 1]
    // y ∈ [cy - 1, cy + 1]

    if (x_to_check < GET_X(current_i) - 1 ||
        x_to_check > GET_X(current_i) + 1 ||
        y_to_check < GET_Y(current_i) - 1 ||
        y_to_check > GET_Y(current_i) + 1)
        return 0;

    int index = COORDINATES_TO_INDEX(x_to_check, y_to_check);
    return current[index] == FIRE;
}

// grid rendering logic
void render_grid(const int *grid);

// frame delay (needed?)
void post_frame_delay(void);

#endif
