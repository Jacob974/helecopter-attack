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

    Int8 gameRunning = 1;

    /*game objects here*/
    Helecopter helecopter;
    helecopter.helecopterPos = (Vec2){.x = 0, .y = 0};
    helecopter.size = (Vec2){.x = 128, .y = 64};
    Vec2 windowSize;

    GameHandler gameHandler;
    createGameHandler(&gameHandler, &helecopter, (Vec2){.x = 0, .y = 200}, 500, 1.0);

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

        /*updates*/
        SDL_GetWindowSize(window, &windowSize.x, &windowSize.y);
        gameHandlerUpdate(&gameHandler, windowSize);

        SDL_RenderClear(renderer);
        
        /*render shit in here*/
        SDL_SetRenderDrawColor(renderer, 0, 255, 100, 255);

        //renders a helecopter (kinda)
        SDL_RenderDrawLine(renderer, gameHandler.offset.x + helecopter.helecopterPos.x, gameHandler.offset.y + helecopter.helecopterPos.y, gameHandler.offset.x + helecopter.helecopterPos.x + helecopter.size.x, gameHandler.offset.y + helecopter.helecopterPos.y);
        SDL_RenderDrawLine(renderer, gameHandler.offset.x + helecopter.helecopterPos.x, gameHandler.offset.y + helecopter.helecopterPos.y, gameHandler.offset.x + helecopter.helecopterPos.x, gameHandler.offset.y + helecopter.helecopterPos.y + helecopter.size.y);
        SDL_RenderDrawLine(renderer, gameHandler.offset.x + helecopter.helecopterPos.x, gameHandler.offset.y + helecopter.helecopterPos.y + helecopter.size.y, gameHandler.offset.x + helecopter.helecopterPos.x + helecopter.size.x, gameHandler.offset.y + helecopter.helecopterPos.y + helecopter.size.y);
        SDL_RenderDrawLine(renderer, gameHandler.offset.x + helecopter.helecopterPos.x + helecopter.size.x, gameHandler.offset.y + helecopter.helecopterPos.y, gameHandler.offset.x + helecopter.helecopterPos.x + helecopter.size.x, gameHandler.offset.y + helecopter.helecopterPos.y + helecopter.size.y);

        //renders the ground
        SDL_SetRenderDrawColor(renderer, 146, 76, 0, 255);
        SDL_RenderDrawLine(renderer, 0, gameHandler.offset.y + 200, 2000, gameHandler.offset.y + 200);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);
    }

    /*destroys SDL objects*/
    SDL_DestroyWindow(window);
    SDL_Quit();

    /*destroys game objects*/

    return 0;
}