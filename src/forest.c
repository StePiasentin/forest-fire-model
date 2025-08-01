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
            // todo: ...
            break;

        case TREE:
            next[i] = ((float)rand() / RAND_MAX < FIRE_IGNITION_RATE) ? FIRE : TREE;
            break;

        case EMPTY:
            next[i] = ((float)rand() / RAND_MAX < TREE_SPAWN_RATE) ? TREE : EMPTY;
            break;
        }
    }
}

// grid rendering logic
void render_grid(const int *grid);

// frame delay (needed?)
void post_frame_delay(void);

#endif
