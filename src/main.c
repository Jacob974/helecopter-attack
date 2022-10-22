#include <SDL2/SDL.h>
#include "datatypes.h"

#include "gameHandler.h"
#include "helecopter.h"

int main()
{
    /*SDL variables*/
    SDL_Window* window = SDL_CreateWindow("helecopter game", 0, 0, 1000, 700, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;

    Vec2 windowSize;
    Int8 gameRunning = 1;

    /*game objects here*/
    Helecopter helecopter;
    helecopter.helecopterPos = (Vec2){.x = 0, .y = 0};
    helecopter.size = (Vec2){.x = 64, .y = 32};

    GameHandler gameHandler;
    createGameHandler(&gameHandler, &helecopter, (Vec2){.x = 0, .y = 200}, 500, 1.0);
    buildingCreate(&gameHandler, 0, 5);
    buildingCreate(&gameHandler, 100, 3);
    buildingCreate(&gameHandler, 250, 7);

    /*game loop*/
    while (gameRunning)
    {
        SDL_PollEvent(&event);

        if(event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        {
            gameRunning = 0;
            break;
        }
        if(event.key.keysym.scancode == SDL_SCANCODE_S)
        {
            helecopter.helecopterPos.y += 5;
        }
        if(event.key.keysym.scancode == SDL_SCANCODE_W)
        {
            helecopter.helecopterPos.y -= 5;
        }
        if(event.key.keysym.scancode == SDL_SCANCODE_D)
        {
            helecopter.helecopterPos.x += 5;
        }
        if(event.key.keysym.scancode == SDL_SCANCODE_A)
        {
            helecopter.helecopterPos.x -= 5;
        }

        /*updates*/
        SDL_GetWindowSize(window, &windowSize.x, &windowSize.y);
        gameHandlerUpdate(&gameHandler, windowSize);

        SDL_RenderClear(renderer);
        
        /*render stuff in here*/

        //renders a helecopter (kinda)
        helecopterRender(renderer, &helecopter, &gameHandler);
        
        //renders the buildings
        buildingRender(renderer, &gameHandler);

        //renders the ground
        SDL_SetRenderDrawColor(renderer, 146, 76, 0, 255);
        SDL_RenderDrawLine(renderer, 0, gameHandler.offset.y + gameHandler.groundHight, 2000, gameHandler.offset.y + gameHandler.groundHight);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);
    }
    /*destroys SDL objects*/
    SDL_DestroyWindow(window);
    SDL_Quit();

    /*destroys game objects*/

    return 0;
}