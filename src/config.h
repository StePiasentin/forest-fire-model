#ifndef CONFIG_H
#define CONFIG_H

// forest width and height
#define WIDTH 120
#define HEIGHT 120

// pixel status
#define EMPTY 0
#define TREE 1
#define FIRE 2

#define TREE_T0_SPAWN_RATE 0.6   // spawn tree probability at T0 time
#define TREE_SPAWN_RATE 0.01     // new tree growth probability
#define FIRE_IGNITION_RATE 0.001 // new fire starting probability

// converts from 2D to 1D array coordinates
#define COORDINATES_TO_INDEX(x, y) ((y) * WIDTH + (x))

// get single coordinate from index i
#define GET_X(i) ((i) % WIDTH)
#define GET_Y(i) ((i) / HEIGHT)

// checks if forest margins are respected in 1D
#define FOREST_MARGIN_1D_CHECK(i)             \
    ((GET_X(i)) >= 0 && (GET_X(i)) < WIDTH && \
     (GET_Y(i)) >= 0 && (GET_Y(i)) < HEIGHT)

// COLORS
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"

// SYMBOLS
#define SYMBOL_EMPTY   " "
#define SYMBOL_TREE    "🌲"
#define SYMBOL_FIRE    "🔥"

// TIMER
#ifdef _WIN32
#include <windows.h>
#define sleep_ms(ms) Sleep(ms)
#else
#include <unistd.h>
#define sleep_ms(ms) usleep((ms)*1000)
#endif

#endif