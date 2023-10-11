#pragma once
#include <stdlib.h> 
#include "datatypes.h"

#define deleteElement(list, element, listSize, type)\
listSize--;\
if(listSize <= 0)\
{\
    list = malloc(1);\
}\
else\
{\
    for(int i0 = element; i0 < listSize; i0++)\
    {\
        list[i0] = list[i0 + 1];\
    }\
    list = realloc(list, listSize * sizeof(type));\
}\

Int8 detectCollision(Vec2f tilePos, Vec2f tileSize, Vec2f lineOrigin, Vec2f lineEnd);
Int8 rectIntersectRect(Vec2f tile1Pos, Vec2 tile1Size, Vec2f tile2Pos, Vec2 tile2Size);

void createInit(List* list, int typeSize);
void addToList(List* list, int item);
void removeFromList(List* list, int element);
