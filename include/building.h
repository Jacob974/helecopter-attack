#pragma once
#include "datatypes.h"
#include <SDL2/SDL.h>

void buildingCreate(GameHandler* gameHandler, double pos, int stories);
void buildingRemove(GameHandler* gameHandler, int element);

void buildingExitSoldier();