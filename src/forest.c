#ifndef FOREST_H
#define FOREST_H

#include <stdlib.h>
#include "config.h"

// starts the forest with a causal pattern
void init_grid(int* grid) {
    for(int i = 0; i < WIDTH * HEIGHT; i ++) {
        grid[i] = ((float)rand() / RAND_MAX < TREE_T0_SPAWN_RATE) ? TREE : EMPTY;
    }
}

// updates grid state
void update_grid(const int* current, int* next);

// grid rendering logic
void render_grid(const int* grid);

// frame delay (needed?)
void post_frame_delay(void);

#endif
