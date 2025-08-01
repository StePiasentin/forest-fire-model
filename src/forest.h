#ifndef FOREST_H
#define FOREST_H

#include "config.h"

void init_grid(int *grid);
void update_grid(const int *current, int *next);
int is_neighbor_on_fire(const int *current, int current_i, int x_to_check, int y_to_check);
void render_grid(const int *grid);

#endif