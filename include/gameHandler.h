#pragma once
#include "datatypes.h"

void createGameHandler(GameHandler* gameHandler, Helecopter* helecopter, Vec2 helecopterScreenCoords, int groundHight, double gameScale);
void gameHandlerUpdate(GameHandler* gameHandler, Vec2 windowSize);