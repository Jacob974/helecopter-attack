#include "missilePad.h"
#include <stdlib.h>

void missilePadCreate(GameHandler* gameHandler, double pos)
{
    gameHandler->missilePadList = realloc(gameHandler->missilePadList, (gameHandler->missilePadAmount + 1) * sizeof(MissilePad));

    gameHandler->missilePadList[gameHandler->missilePadAmount].size.y = 20;
    gameHandler->missilePadList[gameHandler->missilePadAmount].size.x = 55;

    gameHandler->missilePadList[gameHandler->missilePadAmount].pos = pos;

    gameHandler->missilePadList[gameHandler->missilePadAmount].damage = 1.0;

    gameHandler->missilePadList[gameHandler->missilePadAmount].missilePos.x = 1;
    gameHandler->missilePadList[gameHandler->missilePadAmount].missilePos.y;

    gameHandler->missilePadAmount++;
}
void missilePadRemove(GameHandler* gameHandler, int element)
{
    gameHandler->missilePadAmount--;
    for(int i = element; i < gameHandler->missilePadAmount; i++) //moves the elements in the array over to the left 1
    {
        gameHandler->missilePadList[i] = gameHandler->missilePadList[i+1];
    }

    gameHandler->missilePadList = realloc(gameHandler->missilePadList, gameHandler->missilePadAmount * sizeof(MissilePad)); //gets rid of the empty slot at the end
}
void missilePadRender(SDL_Renderer *renderer, GameHandler *gameHandler)
{
    for (int i = 0; i < gameHandler->missilePadAmount; i++)
    {
        int drawColor = (int)(gameHandler->missilePadList[i].damage * 255.0);
        SDL_SetRenderDrawColor(renderer, 255, drawColor, drawColor, 255);

        SDL_RenderDrawLine(renderer, 
            gameHandler->missilePadList[i].pos * gameHandler->gameScale + gameHandler->offset.x, 
            gameHandler->groundHight           * gameHandler->gameScale + gameHandler->offset.y, 
            gameHandler->missilePadList[i].pos * gameHandler->gameScale + gameHandler->offset.x, 
            gameHandler->groundHight           * gameHandler->gameScale + gameHandler->offset.y - gameHandler->missilePadList[i].size.y * gameHandler->gameScale);
        SDL_RenderDrawLine(renderer, 
            gameHandler->missilePadList[i].pos * gameHandler->gameScale + gameHandler->offset.x, 
            gameHandler->groundHight           * gameHandler->gameScale + gameHandler->offset.y, 
            gameHandler->missilePadList[i].pos * gameHandler->gameScale + gameHandler->offset.x + gameHandler->missilePadList[i].size.x * gameHandler->gameScale, 
            gameHandler->groundHight           * gameHandler->gameScale + gameHandler->offset.y);
        SDL_RenderDrawLine(renderer, 
            gameHandler->missilePadList[i].pos * gameHandler->gameScale + gameHandler->offset.x + gameHandler->missilePadList[i].size.x * gameHandler->gameScale, 
            gameHandler->groundHight           * gameHandler->gameScale + gameHandler->offset.y, 
            gameHandler->missilePadList[i].pos * gameHandler->gameScale + gameHandler->offset.x + gameHandler->missilePadList[i].size.x * gameHandler->gameScale, 
            gameHandler->groundHight           * gameHandler->gameScale + gameHandler->offset.y - gameHandler->missilePadList[i].size.y * gameHandler->gameScale);
        SDL_RenderDrawLine(renderer, 
            gameHandler->missilePadList[i].pos * gameHandler->gameScale + gameHandler->offset.x, 
            gameHandler->groundHight           * gameHandler->gameScale + gameHandler->offset.y - gameHandler->missilePadList[i].size.y * gameHandler->gameScale, 
            gameHandler->missilePadList[i].pos * gameHandler->gameScale + gameHandler->offset.x + gameHandler->missilePadList[i].size.x * gameHandler->gameScale, 
            gameHandler->groundHight           * gameHandler->gameScale + gameHandler->offset.y - gameHandler->missilePadList[i].size.y * gameHandler->gameScale);

        //the actual missile
       
    }
}