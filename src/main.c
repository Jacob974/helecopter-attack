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
    helecopter.bombExists = 1;
    helecopter.containsBomb = 1;

    GameHandler gameHandler;
    createGameHandler(&gameHandler, &helecopter, (Vec2){.x = 0, .y = 200}, 500.0, 1.0);
    buildingCreate(&gameHandler, 0.0, 5);
    buildingCreate(&gameHandler, 100.0, 3);
    buildingCreate(&gameHandler, 250.0, 7);
    buildingCreate(&gameHandler, 450.0, 1);

    missilePadCreate(&gameHandler, 550.0);

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
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    //helecopterFireGun(&helecopter, (Vec2){0, 0}, &gameHandler);
                }
                if(event.type == SDL_MOUSEBUTTONUP)
                {
                    //helecopter.firedGun = 0;
                }
            }
            if(event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                gameRunning = 0;
            }
            if(event.key.keysym.scancode == SDL_SCANCODE_E && event.type == SDL_KEYDOWN)
            {
                if(helecopter.stabalizeMode == 1)
                {
                    helecopter.stabalizeMode = 0;
                }
                else if(helecopter.stabalizeMode == 0)
                {
                    helecopter.stabalizeMode = 1;
                }
            }
            if(event.key.keysym.scancode == SDL_SCANCODE_Q && event.type == SDL_KEYDOWN)
            {
                if(helecopter.displayMode == 1)
                {
                    helecopter.displayMode = 0;
                }
                else if(helecopter.displayMode == 0)
                {
                    helecopter.displayMode = 1;
                }
            }

        }
        
        if(keyState[SDL_SCANCODE_S])
        {
            helecopter.velocity.y += 0.2;
        }
        if(keyState[SDL_SCANCODE_W])
        {
            helecopter.velocity.y -= 0.2;
        }
        if(keyState[SDL_SCANCODE_D])
        {
            helecopter.velocity.x += 0.2;
        }
        if(keyState[SDL_SCANCODE_A])
        {
            helecopter.velocity.x -= 0.2;
        }
        if(keyState[SDL_SCANCODE_SPACE])
        {
            helecopter.containsBomb = 0;
        }
        if(keyState[SDL_SCANCODE_UP])
        {
            gameHandler.gameScale += 0.05 * gameHandler.gameScale;
        }
        if(keyState[SDL_SCANCODE_DOWN])
        {
            gameHandler.gameScale -= 0.05 * gameHandler.gameScale;
        }
        if(keyState[SDL_SCANCODE_F])
        {
            helecopter.shootGun = 1;
        }
        else
        {
            helecopter.shootGun = 0;
        }

        /*updates*/

        helecopterMove(&helecopter);
        helecopterDropBomb(&helecopter, &gameHandler);

        SDL_GetWindowSize(window, &windowSize.x, &windowSize.y);
        gameHandlerUpdate(&gameHandler, windowSize);

        //if(helecopter.firedGun == 1)
        //{
            helecopterFireGun(&helecopter, mouseCoords, &gameHandler);
        ///}

        /*render stuff in here*/
        SDL_RenderClear(renderer);


        //renders the ground
        SDL_SetRenderDrawColor(renderer, 146, 76, 0, 255);
        SDL_RenderDrawLine(renderer, 0, gameHandler.offset.y + gameHandler.groundHight  * gameHandler.gameScale, 20000, gameHandler.offset.y + gameHandler.groundHight * gameHandler.gameScale);

        for(int i = 0; i < (2000 / 3 * gameHandler.gameScale); i++)
        {
            SDL_RenderDrawLine(renderer, 
                (gameHandler.gameScale * i * 30 - (int)(helecopter.helecopterPos.x) % 30 * gameHandler.gameScale + (helecopter.velocity.x * 2)), 
                gameHandler.offset.y + gameHandler.groundHight * gameHandler.gameScale, 
                (gameHandler.gameScale * i * 30 - (int)(helecopter.helecopterPos.x) % 30 * gameHandler.gameScale + (helecopter.velocity.x * 2)), 
                gameHandler.offset.y + gameHandler.groundHight * gameHandler.gameScale - 2 * gameHandler.gameScale);
        }
        //MAIN RENDER FUNCTION
        gameRender(renderer, &gameHandler);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
        /*print some stuff*/
        if(helecopter.displayMode == 1)
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //\n\n\n\n
            printf("coords: %f, %f\n", helecopter.helecopterPos.x, helecopter.helecopterPos.y);
            printf("velocity: %f, %f\n", helecopter.velocity.x, helecopter.velocity.y);
            printf("bullet count: %d\n", helecopter.bulletListSize);
            if(helecopter.containsBomb)
            {
                printf("contains bomb\n");
            }
            else
            {
                printf("doesnt contain bomb\n");
            }
        }

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