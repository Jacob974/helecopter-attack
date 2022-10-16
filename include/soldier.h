#pragma once
#include "datatypes.h"

void soldierCreate(GameHandler* gameHandler, int buildingToExit);
void soldierRemove(GameHandler* gameHandler, int element);

void soldierMove(MissilePad* missilePadList, int missilePadAmount, Vec2 heleCopterCoords);
void soldierFireGun(Vec2 helecopterDirection);