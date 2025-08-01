#include "forest.h"

int main()
{
    int forest1[WIDTH * HEIGHT]; // forest at odd T time instant
    int forest2[WIDTH * HEIGHT]; // forest status at event T time instant
    int *current = forest1;
    int *next = forest2;

    init_grid(current);

    // WIP ...

    while (1)
    {
        render_grid(current);
        update_grid(current, next);

        // grids swapping logic
        int *temp = current;
        current = next;
        next = temp;
    }

    return 0;
}