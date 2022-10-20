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
void gameHandlerUpdate(GameHandler* gameHandler, Vec2 windowSize)
{
    //updates the offset
    gameHandler->offset.x = -gameHandler->helecopter->helecopterPos.x + (windowSize.x / 2) - (gameHandler->helecopter->size.x / 2);
    gameHandler->offset.y = -gameHandler->helecopter->helecopterPos.y + (windowSize.y / 2) - (gameHandler->helecopter->size.y / 2);
}