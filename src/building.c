#include "building.h"
#include "stdlib.h"

void buildingCreate(GameHandler *gameHandler, double pos, int stories)
{
    gameHandler->buildingList = realloc(gameHandler->buildingList, (gameHandler->buildingAmount + 1) * sizeof(Building));

    gameHandler->buildingList[gameHandler->buildingAmount].size.y = 25 * stories;
    gameHandler->buildingList[gameHandler->buildingAmount].size.x = 75;

    gameHandler->buildingList[gameHandler->buildingAmount].pos = pos;
    gameHandler->buildingList[gameHandler->buildingAmount].damage = 1.0;
    gameHandler->buildingAmount++;
}
void buildingRemove(GameHandler *gameHandler, int element)
{
    gameHandler->buildingAmount--;
    for(int i = element; i < gameHandler->buildingAmount; i++) // moves the elements in the array over to the left 1
    {
        gameHandler->buildingList[i] = gameHandler->buildingList[i + 1];
    }

    gameHandler->buildingList = realloc(gameHandler->buildingList, gameHandler->buildingAmount * sizeof(Building)); // gets rid of the empty slot at the end
}
void buildingExitSoldier(GameHandler *gameHandler, int element)
{
    if (gameHandler->buildingList[element].playerCount <= 0)
    {
        gameHandler->buildingList[element].playerCount--;

        gameHandler->soldierAmount++;
        gameHandler->soldierList = realloc(gameHandler->soldierList, gameHandler->soldierAmount); // reallocates soldier list to add new soldier

        int soldierPos = gameHandler->buildingList[element].pos + (gameHandler->buildingList[element].size.x / 2);
        gameHandler->soldierList[gameHandler->soldierAmount - 1].pos = soldierPos; // puts the soldier infront of the building
    }
}
void buildingRender(SDL_Renderer *renderer, GameHandler *gameHandler)
{
    for (int i = 0; i < gameHandler->buildingAmount; i++)
    {

        int drawColor = (int)(gameHandler->buildingList[i].damage * 255.0);

        SDL_SetRenderDrawColor(renderer, 255, drawColor, drawColor, 255);

        SDL_RenderDrawLine(renderer, 
            gameHandler->buildingList[i].pos * gameHandler->gameScale + gameHandler->offset.x, 
            gameHandler->groundHight         * gameHandler->gameScale + gameHandler->offset.y, 
            gameHandler->buildingList[i].pos * gameHandler->gameScale + gameHandler->offset.x, 
            gameHandler->groundHight         * gameHandler->gameScale + gameHandler->offset.y - gameHandler->buildingList[i].size.y * gameHandler->gameScale);
        SDL_RenderDrawLine(renderer, 
            gameHandler->buildingList[i].pos * gameHandler->gameScale + gameHandler->offset.x, 
            gameHandler->groundHight         * gameHandler->gameScale + gameHandler->offset.y, 
            gameHandler->buildingList[i].pos * gameHandler->gameScale + gameHandler->offset.x + gameHandler->buildingList[i].size.x * gameHandler->gameScale, 
            gameHandler->groundHight         * gameHandler->gameScale + gameHandler->offset.y);
        SDL_RenderDrawLine(renderer, 
            gameHandler->buildingList[i].pos * gameHandler->gameScale + gameHandler->offset.x + gameHandler->buildingList[i].size.x * gameHandler->gameScale, 
            gameHandler->groundHight         * gameHandler->gameScale + gameHandler->offset.y, 
            gameHandler->buildingList[i].pos * gameHandler->gameScale + gameHandler->offset.x + gameHandler->buildingList[i].size.x * gameHandler->gameScale, 
            gameHandler->groundHight         * gameHandler->gameScale + gameHandler->offset.y - gameHandler->buildingList[i].size.y * gameHandler->gameScale);
        SDL_RenderDrawLine(renderer, 
            gameHandler->buildingList[i].pos * gameHandler->gameScale + gameHandler->offset.x, 
            gameHandler->groundHight         * gameHandler->gameScale + gameHandler->offset.y - gameHandler->buildingList[i].size.y * gameHandler->gameScale, 
            gameHandler->buildingList[i].pos * gameHandler->gameScale + gameHandler->offset.x + gameHandler->buildingList[i].size.x * gameHandler->gameScale, 
            gameHandler->groundHight         * gameHandler->gameScale + gameHandler->offset.y - gameHandler->buildingList[i].size.y * gameHandler->gameScale);
    }
}