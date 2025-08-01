#ifndef CONFIG_H
#define CONFIG_H

// forest width and height
#define WIDTH 80
#define HEIGHT 40

// pixel status
#define EMPTY 0
#define TREE 1
#define FIRE 2

#define TREE_T0_SPAWN_RATE 0.6   // spawn tree probability at T0 time
#define TREE_SPAWN_RATE 0.01     // new tree growth probability
#define FIRE_IGNITION_RATE 0.001 // new fire starting probability

// converts from 2D to 1D array coordinates
#define COORDINATES_TO_INDEX(x, y) ((y) * WIDTH + (x))

// checks if forest margins are respected
#define FOREST_MARGINS_CHECK(x, y) ((x) >= 0 && (x) < WIDTH && (y >= 0) && (y) <= HEIGHT)

#endif