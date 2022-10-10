#pragma once
#include "datatypes.h"

void createGameHandler(GameHandler* gameHandler, Helecopter* helecopter, Vec2 helecopterScreenCoords, int groundHight, double gameScale);

void gameHandlerCreateSoldier(GameHandler* gameHandler, int buildingToExit);
void gameHandlerCreateBuilding(GameHandler* gameHandler, int pos, int stories);
void gameHandlerCreateMissilePad(GameHandler* gameHandler, int pos);

void gameHandlerRemoveSoldier(GameHandler* gameHandler, int element);
void gameHandlerRemoveBuilding(GameHandler* gameHandler, int element);
void gameHandlerRemoveMissilePad(GameHandler* gameHandler, int element);