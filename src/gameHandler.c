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


