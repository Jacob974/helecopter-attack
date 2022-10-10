#pragma once
#include "datatypes.h"
#include "utils.h"
#include "gameHandler.h"

void helecopterMove(Helecopter* helecopter, Vec2 direction);
void helecopterFireGun(Helecopter* helecopter, Vec2 direction, GameHandler* gameHandler);
void helecopterDropBomb(Helecopter* helecopter, GameHandler* gameHandler);

void render();