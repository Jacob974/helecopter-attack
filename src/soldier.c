#include "soldier.h"

void soldierCreate(GameHandler* gameHandler, int buildingToExit)
{
    gameHandler->soldierAmount++;
    gameHandler->soldierList = realloc(gameHandler->soldierList, gameHandler->soldierAmount * sizeof(Soldier));

    gameHandler->soldierList[gameHandler->soldierAmount].pos = gameHandler->buildingList[buildingToExit].pos + gameHandler->buildingList[buildingToExit].size.x;

    gameHandler->soldierList[gameHandler->soldierAmount].size = (Vec2){.x = 10, .y = 20};
    gameHandler->soldierList[gameHandler->soldierAmount].agrovated = 0;
}
void soldierRemove(GameHandler* gameHandler, int element)
{
    gameHandler->soldierAmount--;
    for(int i = element; i < gameHandler->soldierAmount; i++) //moves the elements in the array over to the left 1
    {
        gameHandler->soldierList[i] = gameHandler->soldierList[i+1];
    }

    gameHandler->soldierList = realloc(gameHandler->soldierList, gameHandler->soldierAmount * sizeof(Soldier)); //gets rid of the empty slot at the end
}