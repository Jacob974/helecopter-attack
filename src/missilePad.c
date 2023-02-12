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