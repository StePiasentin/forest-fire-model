#include <windows.h>
#include "forest.h"

void enable_vt_mode() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

int main()
{
    int forest1[WIDTH * HEIGHT]; // forest at odd T time instant
    int forest2[WIDTH * HEIGHT]; // forest status at event T time instant
    int *current = forest1;
    int *next = forest2;

    init_grid(current);

    enable_vt_mode();

    while (1)
    {
        render_grid(current);
        sleep_ms(1);
        update_grid(current, next);

        // grids swapping logic
        int *temp = current;
        current = next;
        next = temp;
    }

    return 0;
}