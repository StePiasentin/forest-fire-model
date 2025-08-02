#include <windows.h>
#include <SDL.h>
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

    SDL_Event e;
    int quit = 0;

    while (!quit)
    {
        // Events handling
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = 1;
        }

        render_grid(current);
        update_grid(current, next);

        // swap
        int *temp = current;
        current = next;
        next = temp;

        SDL_Delay(DELAY); // delay
    }

    // Cleaning SDL
    SDL_Quit();

    return 0;
}