#pragma once
#include "datatypes.h"

void buildingCreate(GameHandler* gameHandler, int pos, int stories);
void buildingRemove(GameHandler* gameHandler, int element);

void buildingExitSoldier(); 
Int8 buildingDetectBulletHit(Vec2 bulletPos, Vec2 helecopterPos); //returns true if it has been hit

void RenderBuilding();