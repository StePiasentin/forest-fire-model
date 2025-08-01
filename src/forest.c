#include <stdlib.h>
#include <stdio.h>
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
    if (!FOREST_MARGIN_1D_CHECK(COORDINATES_TO_INDEX(x_to_check, y_to_check)))
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
void render_grid(const int *grid)
{
    static HANDLE hConsole = NULL;
    if (!hConsole)
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    printf("\x1b[H"); // Move cursor to top-left

    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        switch (grid[i])
        {
        case EMPTY:
            SetConsoleTextAttribute(hConsole, 0); // Nero (vuoto)
            putchar(' ');
            break;

        case TREE:
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Verde brillante
            putchar('#');
            break;

        case FIRE:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // Rosso brillante
            putchar('*');
            break;
        }

        if ((i + 1) % WIDTH == 0)
            putchar('\n');
    }

    // Reset color a default bianco su nero
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    fflush(stdout);
}

// frame delay (needed?)
void post_frame_delay(void);
