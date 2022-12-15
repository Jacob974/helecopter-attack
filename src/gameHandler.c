#include "gameHandler.h"
#include <stdlib.h>

void createGameHandler(GameHandler* gameHandler, Helecopter* helecopter, Vec2 helecopterScreenCoords, int groundHight, double gameScale)
{
    gameHandler->helecopter = helecopter;
    gameHandler->helecopter->velocity = (Vec2f){.x = 0.0, .y = 0.0};

    gameHandler->offset.x = helecopterScreenCoords.x - (int)(helecopter->helecopterPos.x);
    gameHandler->offset.y = helecopterScreenCoords.y - (int)(helecopter->helecopterPos.y); 

    gameHandler->buildingAmount = 0;
    gameHandler->missilePadAmount = 0;
    gameHandler->soldierAmount = 0;
    gameHandler->explosionAmount = 0;

    gameHandler->buildingList = malloc(1);
    gameHandler->missilePadList = malloc(1);
    gameHandler->soldierList = malloc(1);
    gameHandler->explosionList = malloc(1);

    gameHandler->gameScale = gameScale;
    gameHandler->groundHight = groundHight;


    gameHandler->alertAmount = 0;
}
void gameHandlerUpdate(GameHandler* gameHandler, Vec2 windowSize)
{
    //updates the offset
    gameHandler->offset.x = (int)(-gameHandler->helecopter->helecopterPos.x * gameHandler->gameScale) + (windowSize.x / 2) - (gameHandler->helecopter->size.x * gameHandler->gameScale / 2) + (gameHandler->helecopter->velocity.x * 2);
    gameHandler->offset.y = (int)(-gameHandler->helecopter->helecopterPos.y * gameHandler->gameScale) + (windowSize.y / 2) - (gameHandler->helecopter->size.y * gameHandler->gameScale / 2) + (gameHandler->helecopter->velocity.y * 2);
}
void addexplosion(GameHandler* gameHandler, Vec2f coords, double size)
{
    gameHandler->explosionList = realloc(gameHandler->explosionList, (gameHandler->explosionAmount + 1) * sizeof(Explosion));

    gameHandler->explosionList[gameHandler->explosionAmount].size = size;
    gameHandler->explosionList[gameHandler->explosionAmount].pos = coords;
    gameHandler->explosionList[gameHandler->explosionAmount].duration = 1;

    gameHandler->explosionAmount++;
}
void destroyExplosion(GameHandler* gameHandler, int element)
{
    gameHandler->explosionAmount--;
    for(int i = element; i < gameHandler->explosionAmount; i++)
    {
        gameHandler->explosionList[i] = gameHandler->explosionList[i+1];
    }
    if(gameHandler->explosionAmount > 0)
    {
        gameHandler->explosionList = realloc(gameHandler->explosionList, sizeof(Explosion) * gameHandler->explosionAmount);
    }
    else
    {
        gameHandler->explosionList = realloc(gameHandler->explosionList, 1);
    }
}
void gameRender(SDL_Renderer* renderer, GameHandler* gameHandler)
{
    int vectors = 30;
    double pi = 3.14159263 * 2.0;

    for(int i = 0; i < gameHandler->explosionAmount; i++)
    {
        if(gameHandler->explosionList[i].duration <= 60)
        {
            double explosionSize = gameHandler->explosionList[i].size * (double)(gameHandler->explosionList[i].duration);
            SDL_SetRenderDrawColor(renderer, 255 - (255 * gameHandler->explosionList[i].duration / 60),
                255 - (255 * gameHandler->explosionList[i].duration / 60),
                0,255);
            gameHandler->explosionList[i].duration += 5;

            //I know there is some algorythm that does this better but I dont care, 
            //I came up with this method myself and I'm going to use it
            for(int j = 0; j < vectors; j++)
            {
                SDL_RenderDrawLine(renderer, 
                (explosionSize * cos(j * pi / vectors)) * gameHandler->gameScale + gameHandler->explosionList[i].pos.x * gameHandler->gameScale + gameHandler->offset.x, 
                (explosionSize * sin(j * pi / vectors)) * gameHandler->gameScale + gameHandler->explosionList[i].pos.y * gameHandler->gameScale + gameHandler->offset.y, 
                (explosionSize * cos((j + 1) * pi / vectors)) * gameHandler->gameScale + gameHandler->explosionList[i].pos.x * gameHandler->gameScale + gameHandler->offset.x, 
                (explosionSize * sin((j + 1) * pi / vectors)) * gameHandler->gameScale + gameHandler->explosionList[i].pos.y * gameHandler->gameScale + gameHandler->offset.y);
            }
        }
        else
        {
            destroyExplosion(gameHandler, i);
        }
    }
}