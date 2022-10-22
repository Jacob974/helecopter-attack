#pragma once
#include "datatypes.h"
#include <SDL2/SDL.h>

void buildingCreate(GameHandler* gameHandler, int pos, int stories);
void buildingRemove(GameHandler* gameHandler, int element);

void buildingExitSoldier();

void buildingRender(SDL_Renderer* renderer, GameHandler* gameHandler);