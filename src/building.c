#include "building.h"
#include "stdlib.h"

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
    if(gameHandler->buildingList[element].playerCount <= 0)
    {
        gameHandler->buildingList[element].playerCount--;

        gameHandler->soldierAmount++;
        gameHandler->soldierList = realloc(gameHandler->soldierList, gameHandler->soldierAmount); //reallocates soldier list to add new soldier

        int soldierPos = gameHandler->buildingList[element].pos + (gameHandler->buildingList[element].size.x / 2);
        gameHandler->soldierList[gameHandler->soldierAmount-1].pos = soldierPos; //puts the soldier infront of the building
    }
}

void RenderBuilding()
{

}