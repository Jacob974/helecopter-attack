#pragma once
#include "datatypes.h"

void missilePadCreate(GameHandler* gameHandler, int pos);
void missilePadRemove(GameHandler* gameHandler, int element);

void missilePadLaunch(Vec2 helecopterDirection);
