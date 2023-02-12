#pragma once
#include "datatypes.h"
#include <SDL2/SDL.h>

void missilePadCreate(GameHandler* gameHandler, double pos);
void missilePadRemove(GameHandler* gameHandler, int element);

void missilePadLaunch(Vec2 helecopterDirection);