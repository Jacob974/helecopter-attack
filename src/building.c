#include "building.h"
#include "stdlib.h"
#include "utils.h"

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
    //deleteElement(gameHandler->buildingList, element, gameHandler->buildingAmount, Building);
    gameHandler->buildingAmount--;
    for(int i = element; i < gameHandler->buildingAmount; i++) // moves the elements in the array over to the left 1
    {
        gameHandler->buildingList[i] = gameHandler->buildingList[i + 1];
    }

    gameHandler->buildingList = realloc(gameHandler->buildingList, gameHandler->buildingAmount * sizeof(Building)); // gets rid of the empty slot at the end
}
void buildingExitSoldier(GameHandler *gameHandler, int element)
{
    if (gameHandler->buildingList[element].playerCount >= 0)
    {
        gameHandler->buildingList[element].playerCount--;

        gameHandler->soldierAmount++;
        gameHandler->soldierList = realloc(gameHandler->soldierList, gameHandler->soldierAmount); // reallocates soldier list to add new soldier

        int soldierPos = gameHandler->buildingList[element].pos + (gameHandler->buildingList[element].size.x / 2);
        gameHandler->soldierList[gameHandler->soldierAmount - 1].pos = soldierPos; // puts the soldier infront of the building
    }
}