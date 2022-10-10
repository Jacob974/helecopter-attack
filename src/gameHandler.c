#include "gameHandler.h"
#include <stdlib.h>

void createGameHandler(GameHandler* gameHandler, Helecopter* helecopter, Vec2 helecopterScreenCoords, int groundHight, double gameScale)
{
    gameHandler->helecopter = helecopter;

    gameHandler->offset.x = helecopterScreenCoords.x - helecopter->helecopterPos.x;
    gameHandler->offset.y = helecopterScreenCoords.y - helecopter->helecopterPos.y; 

    gameHandler->buildingAmount = 0;
    gameHandler->missilePadAmount = 0;
    gameHandler->soldierAmount = 0;

    gameHandler->buildingList = malloc(1);
    gameHandler->missilePadList = malloc(1);
    gameHandler->soldierList = malloc(1);

    gameHandler->gameScale = gameScale;
    gameHandler->groundHight = groundHight;

    gameHandler->alertAmount = 0;
}
void gameHandlerCreateSoldier(GameHandler* gameHandler, int buildingToExit)
{
    gameHandler->soldierAmount++;
    gameHandler->soldierList = realloc(gameHandler->soldierList, gameHandler->soldierAmount * sizeof(Soldier));

    gameHandler->soldierList[gameHandler->soldierAmount].pos = gameHandler->buildingList[buildingToExit].pos + gameHandler->buildingList[buildingToExit].size.x;

    gameHandler->soldierList[gameHandler->soldierAmount].size = (Vec2){.x = 10, .y = 20};
    gameHandler->soldierList[gameHandler->soldierAmount].agrovated = 0;
}
void gameHandlerCreateBuilding(GameHandler* gameHandler, int pos, int stories)
{
    gameHandler->buildingAmount++;
    gameHandler->buildingList = realloc(gameHandler->buildingList, gameHandler->buildingAmount * sizeof(Building));

    gameHandler->buildingList[gameHandler->buildingAmount].size.y = 25 * stories;
    gameHandler->buildingList[gameHandler->buildingAmount].size.x = 75;
}
void gameHandlerCreateMissilePad(GameHandler* gameHandler, int pos)
{
    gameHandler->missilePadAmount++;
    gameHandler->missilePadList = realloc(gameHandler->missilePadList, gameHandler->missilePadAmount * sizeof(MissilePad));

    gameHandler->missilePadList[gameHandler->missilePadAmount].size.y = 20;
    gameHandler->missilePadList[gameHandler->missilePadAmount].size.x = 55;
}

void gameHandlerRemoveSoldier(GameHandler* gameHandler, int element)
{
    gameHandler->soldierAmount--;
    for(int i = element; i < gameHandler->soldierAmount; i++) //moves the elements in the array over to the left 1
    {
        gameHandler->soldierList[i] = gameHandler->soldierList[i+1];
    }

    gameHandler->soldierList = realloc(gameHandler->soldierList, gameHandler->soldierAmount * sizeof(Soldier)); //gets rid of the empty slot at the end
}
void gameHandlerRemoveBuilding(GameHandler* gameHandler, int element)
{
    gameHandler->buildingAmount--;
    for(int i = element; i < gameHandler->buildingAmount; i++) //moves the elements in the array over to the left 1
    {
        gameHandler->buildingList[i] = gameHandler->buildingList[i+1];
    }

    gameHandler->buildingList = realloc(gameHandler->buildingList, gameHandler->buildingAmount * sizeof(Building)); //gets rid of the empty slot at the end
}
void gameHandlerRemoveMissilePad(GameHandler* gameHandler, int element)
{
    gameHandler->missilePadAmount--;
    for(int i = element; i < gameHandler->missilePadAmount; i++) //moves the elements in the array over to the left 1
    {
        gameHandler->missilePadList[i] = gameHandler->missilePadList[i+1];
    }

    gameHandler->missilePadList = realloc(gameHandler->missilePadList, gameHandler->missilePadAmount * sizeof(MissilePad)); //gets rid of the empty slot at the end
}