#pragma once
#include "datatypes.h"
#include <SDL2/SDL.h>

void createGameHandler(GameHandler* gameHandler, Helecopter* helecopter, Vec2 helecopterScreenCoords, int groundHight, double gameScale);
void gameHandlerUpdate(GameHandler* gameHandler, Vec2 windowSize);
void addexplosion(GameHandler* gameHandler, Vec2f coords, double size);
void destroyExplosion(GameHandler* gameHandler, int element);
void gameRender(SDL_Renderer* renderer, GameHandler* gameHandler);