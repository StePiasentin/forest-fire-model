#ifndef FOREST_H
#define FOREST_H

#include "config.h"

void init_grid(int *grid);
void update_grid(const int *current, int *next);
int is_neighbor_on_fire(const int *current, int i, int x, int y);
void render_grid(const int *grid);

#endif