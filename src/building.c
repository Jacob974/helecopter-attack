#include "building.h"

void buildingCreate(GameHandler* gameHandler, int pos, int stories)
{
    gameHandler->buildingAmount++;
    gameHandler->buildingList = realloc(gameHandler->buildingList, gameHandler->buildingAmount * sizeof(Building));

    gameHandler->buildingList[gameHandler->buildingAmount].size.y = 25 * stories;
    gameHandler->buildingList[gameHandler->buildingAmount].size.x = 75;
}
void buildingRemove(GameHandler* gameHandler, int element)
{
    gameHandler->buildingAmount--;
    for(int i = element; i < gameHandler->buildingAmount; i++) //moves the elements in the array over to the left 1
    {
        gameHandler->buildingList[i] = gameHandler->buildingList[i+1];
    }

    gameHandler->buildingList = realloc(gameHandler->buildingList, gameHandler->buildingAmount * sizeof(Building)); //gets rid of the empty slot at the end
}

void buildingExitSoldier(GameHandler* gameHandler, int element)
{

}
Int8 buildingDetectBulletHit(Vec2 bulletPos, Vec2 helecopterPos) //returns true if it has been hit
{

}

void RenderBuilding()
{

}