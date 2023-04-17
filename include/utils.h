#pragma once
#include <stdlib.h>
#include "datatypes.h"

Int8 detectCollision(Vec2f tilePos, Vec2f tileSize, Vec2f lineOrigin, Vec2f lineEnd);
Int8 rectIntersectRect(Vec2f tile1Pos, Vec2 tile1Size, Vec2f tile2Pos, Vec2 tile2Size);

void* addItemToList(void* list, short dataSize, int arrayLenfth);
void* removeItemFromList(void* list, short dataSize, int arrayLenfth, int elementInArray);