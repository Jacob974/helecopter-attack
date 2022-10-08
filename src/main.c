#include <SDL2/SDL.h>
#include "datatypes.h"

int main()
{
    /*SDL variables*/
    SDL_Window* window = SDL_CreateWindow("helecopter game", 0, 0, 1000, 700, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;

    Int8 gameRunning = 1;

    /*game loop*/
    while (gameRunning)
    {
        SDL_PollEvent(&event);

        if(event.type == SDL_QUIT)
        {
            gameRunning = 0;
        }

        SDL_RenderClear(renderer);
        
        /*render shit in here*/

        SDL_RenderPresent(renderer);
    }

    /*destroys SDL objects*/
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}