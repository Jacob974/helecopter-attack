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
    helecopter.helecopterPos = (Vec2f){.x = 0.0, .y = 0.0};
    helecopter.size = (Vec2){.x = 64, .y = 32};

    helecopter.bombSize = (Vec2){.x = 15, .y = 10};
    helecopter.containsBomb = 1;

    GameHandler gameHandler;
    createGameHandler(&gameHandler, &helecopter, (Vec2){.x = 0, .y = 200}, 500, 1.0);
    buildingCreate(&gameHandler, 0, 5);
    buildingCreate(&gameHandler, 100, 3);
    buildingCreate(&gameHandler, 250, 7);
    buildingCreate(&gameHandler, 450, 1);

    /*key press variables*/
    const Uint8* keyState;
    Vec2 mouseCoords;

    /*time variables*/
    unsigned long long beginningFrameTime;
    unsigned long long endFrameTime;

    int fps = 60;
    unsigned long long realFps = 1000 / fps;

    /*game loop*/
    while (gameRunning)
    {
        beginningFrameTime = SDL_GetTicks64();
        keyState = SDL_GetKeyboardState(NULL);
        SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                gameRunning = 0;
                break;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                helecopter.firedGun = 1;
            }
            if(event.type == SDL_MOUSEBUTTONUP)
            {
                helecopter.firedGun = 0;
            }
        }
        
        if(keyState[SDL_SCANCODE_S])
        {
            helecopter.helecopterPos.y += 5.0;
        }
        if(keyState[SDL_SCANCODE_W])
        {
            helecopter.helecopterPos.y -= 5.0;
        }
        if(keyState[SDL_SCANCODE_D])
        {
            helecopter.helecopterPos.x += 5.0;
        }
        if(keyState[SDL_SCANCODE_A])
        {
            helecopter.helecopterPos.x -= 5.0;
        }
        if(keyState[SDL_SCANCODE_SPACE])
        {
            helecopter.containsBomb = 0;
        }

        /*updates*/

        helecopterDropBomb(&helecopter, &gameHandler);

        SDL_GetWindowSize(window, &windowSize.x, &windowSize.y);
        gameHandlerUpdate(&gameHandler, windowSize);

        if(helecopter.firedGun == 1)
        {
            helecopterFireGun(&helecopter, mouseCoords, &gameHandler);
        }

        /*render stuff in here*/
        SDL_RenderClear(renderer);

        //renders a helecopter (kinda)
        helecopterRender(renderer, &helecopter, &gameHandler);
        
        //renders the buildings
        buildingRender(renderer, &gameHandler);

        //renders the ground
        SDL_SetRenderDrawColor(renderer, 146, 76, 0, 255);
        SDL_RenderDrawLine(renderer, 0, gameHandler.offset.y + gameHandler.groundHight, 20000, gameHandler.offset.y + gameHandler.groundHight);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);

        endFrameTime = SDL_GetTicks64();
        if(realFps > (endFrameTime - beginningFrameTime))
        {
            SDL_Delay(realFps - (endFrameTime - beginningFrameTime));
        }
    }
    /*destroys SDL objects*/
    SDL_DestroyWindow(window);
    SDL_Quit();

    /*destroys game objects*/

    return 0;
}