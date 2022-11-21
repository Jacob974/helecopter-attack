#include "gameHandler.h"
#include <stdlib.h>

void createGameHandler(GameHandler* gameHandler, Helecopter* helecopter, Vec2 helecopterScreenCoords, int groundHight, double gameScale)
{
    gameHandler->helecopter = helecopter;
    gameHandler->helecopter->velocity = (Vec2f){.x = 0.0, .y = 0.0};

    gameHandler->offset.x = helecopterScreenCoords.x - (int)(helecopter->helecopterPos.x);
    gameHandler->offset.y = helecopterScreenCoords.y - (int)(helecopter->helecopterPos.y); 

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
    gameHandler->offset.x = (int)(-gameHandler->helecopter->helecopterPos.x * gameHandler->gameScale) + (windowSize.x / 2) - (gameHandler->helecopter->size.x * gameHandler->gameScale / 2) + (gameHandler->helecopter->velocity.x * 2);
    gameHandler->offset.y = (int)(-gameHandler->helecopter->helecopterPos.y * gameHandler->gameScale) + (windowSize.y / 2) - (gameHandler->helecopter->size.y * gameHandler->gameScale / 2) + (gameHandler->helecopter->velocity.y * 2);
}