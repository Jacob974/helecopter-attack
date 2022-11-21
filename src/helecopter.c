#include "helecopter.h"
#include <stdlib.h>

void helecopterMove(Helecopter* helecopter)
{
    if(helecopter->stabalizeMode == 1)
    {
        if(helecopter->velocity.x >= 0.2)
        {
            helecopter->velocity.x -= 0.2;
        }
        else if(helecopter->velocity.x <= -0.2)
        {
            helecopter->velocity.x += 0.2;
        }
        else
        {
            helecopter->velocity.x = 0.0;
        }

        if(helecopter->velocity.y >= 0.2)
        {
            helecopter->velocity.y -= 0.2;
        }
        else if(helecopter->velocity.y <= -0.2)
        {
            helecopter->velocity.y += 0.2;
        }
        else
        {
            helecopter->velocity.y = 0.0;
        }
    }
    
    helecopter->helecopterPos.x += helecopter->velocity.x;
    helecopter->helecopterPos.y += helecopter->velocity.y;
    
}
void helecopterFireGun(Helecopter* helecopter, Vec2 direction, GameHandler* gameHandler)
{
    //takes it from screen space ant turns it into gamespace
    Vec2f lineOrigin = (Vec2f){.x = helecopter->helecopterPos.x, .y = helecopter->helecopterPos.y};

    Vec2f lineEnd;
    lineEnd.x = ((double)(direction.x) - gameHandler->offset.x) / gameHandler->gameScale;
    lineEnd.y = ((double)(direction.y) - gameHandler->gameScale - gameHandler->offset.y) / gameHandler->gameScale;

    //gives info to the helecopter
    helecopter->bulletPos.x = lineEnd.x;
    helecopter->bulletPos.y = lineEnd.y;

    //detects if it hits a soldier
    for(int i = 0; i < gameHandler->soldierAmount; i++)
    {
        Vec2f tileSize = (Vec2f){.x = (double)(gameHandler->soldierList[i].size.x), .y = (double)(gameHandler->soldierList[i].size.y)};
        Vec2f tilePos = (Vec2f){.x = gameHandler->soldierList[i].pos, .y = gameHandler->groundHight - gameHandler->soldierList[i].size.y};
        
        if(detectCollision(tilePos, tileSize, lineOrigin, lineEnd))
        {
            soldierRemove(gameHandler, i);
            i--; //makes it so the next turn of the loop will be the same element since the array has been realocated
        }
    }

    //detects if it hits a building
    for(int i = 0; i < gameHandler->buildingAmount; i++)
    {
        Vec2f tileSize = (Vec2f){.x = (double)(gameHandler->buildingList[i].size.x), .y = (double)(gameHandler->buildingList[i].size.y)};
        Vec2f tilePos = (Vec2f){.x = gameHandler->buildingList[i].pos, .y = gameHandler->groundHight - gameHandler->buildingList[i].size.y};
        
        if(detectCollision(tilePos, tileSize, lineOrigin, lineEnd))
        {
            gameHandler->buildingList[i].damage -= 0.01;
            if(gameHandler->buildingList[i].damage < 0.0)
            {
                buildingRemove(gameHandler, i);
                i--; //makes it so the next itteration of the loop will be the same element since the array has been realocated
            }
        }
    }
    //detects if it hits a missile pad
    for(int i = 0; i < gameHandler->missilePadAmount; i++)
    {
        Vec2f tileSize = (Vec2f){.x = (double)(gameHandler->missilePadList[i].size.x), .y = (double)(gameHandler->missilePadList[i].size.y)};
        Vec2f tilePos = (Vec2f){.x = gameHandler->missilePadList[i].pos, .y = (int)(gameHandler->groundHight) - gameHandler->missilePadList[i].size.y};
        
        if(detectCollision(tilePos, tileSize, lineOrigin, lineEnd))
        {
            gameHandler->missilePadList[i].damage -= 0.01;
            if(gameHandler->missilePadList[i].damage <= 0.0)
            {
                missilePadRemove(gameHandler, i);
                i--; //makes it so the next itteration of the loop will be the same element since the array has been realocated
            }
        }
    }
}
void helecopterDropBomb(Helecopter* helecopter, GameHandler* gameHandler)
{
    if(!helecopter->containsBomb)
    {
        helecopter->droppedBomb = 1;
        helecopter->bombPos.y += 5.0;
        if((int)(helecopter->bombPos.y) + helecopter->bombSize.y >= gameHandler->groundHight)
        {
            //bomb has exploded
            helecopter->bombPos.y = gameHandler->groundHight - helecopter->bombSize.y; //puts the bomb on the ground
            Vec2f bombExplodePos = (Vec2f){.x = helecopter->bombPos.x - 20.0, .y = (double)(gameHandler->groundHight - 100)};
            Vec2 bombExplodeSize = (Vec2){.x = helecopter->bombSize.x + 40, .y = 150};
            helecopter->droppedBomb = 0;

            for(int i = 0; i < gameHandler->soldierAmount; i++)
            {
                Vec2f soldierPos = (Vec2f){.x = gameHandler->soldierList[i].pos, .y = (double)(gameHandler->groundHight - gameHandler->soldierList[i].size.y)};
                if(rectIntersectRect(bombExplodePos, bombExplodeSize, soldierPos, gameHandler->soldierList[i].size))
                {
                    soldierRemove(gameHandler, i);
                    i--; //adjusts i since the soldier list was reallocated
                }
            }
            for(int i = 0; i < gameHandler->buildingAmount; i++)
            {
                Vec2f buildingPos = (Vec2f){.x = gameHandler->buildingList[i].pos, .y = (double)(gameHandler->groundHight - gameHandler->buildingList[i].size.y)};
                
                if(rectIntersectRect(helecopter->bombPos, helecopter->bombSize, buildingPos, gameHandler->buildingList[i].size))
                {
                    buildingRemove(gameHandler, i);
                    i--; //adjusts i since the building list was reallocated
                }
                else if(rectIntersectRect(bombExplodePos, bombExplodeSize, buildingPos, gameHandler->buildingList[i].size))
                {
                    gameHandler->buildingList[i].damage -= 0.5;
                    if(gameHandler->buildingList[i].damage <= 0.0)
                    {
                        buildingRemove(gameHandler, i);
                        i--; //adjusts i since the building list was reallocated
                    }
                } 
            }
            for(int i = 0; i < gameHandler->missilePadAmount; i++)
            {
                Vec2f missilePadPos = (Vec2f){.x = gameHandler->missilePadList[i].pos, .y = (double)(gameHandler->groundHight - gameHandler->missilePadList[i].size.y)};
                
                if(rectIntersectRect(helecopter->bombPos, helecopter->bombSize, missilePadPos, gameHandler->missilePadList[i].size))
                {
                    buildingRemove(gameHandler, i);
                    i--; //adjusts i since the building list was reallocated
                }
                else if(rectIntersectRect(bombExplodePos, bombExplodeSize, missilePadPos, gameHandler->missilePadList[i].size))
                {
                    gameHandler->missilePadList[i].damage -= 0.5;
                    if(gameHandler->missilePadList[i].damage <= 0.0)
                    {
                        missilePadRemove(gameHandler, i);
                        i--; //adjusts i since the building list was reallocated
                    }
                } 
            }
        }
    }
    else
    {
        helecopter->bombPos = helecopter->helecopterPos;
    }
}

void helecopterRender(SDL_Renderer* renderer, Helecopter* helecopter, GameHandler* gameHandler)
{
    //renders the helecopter
    SDL_SetRenderDrawColor(renderer, 0, 255, 100, 255);

    SDL_RenderDrawLine(renderer, 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x * gameHandler->gameScale), 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y * gameHandler->gameScale), 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x * gameHandler->gameScale) + helecopter->size.x * gameHandler->gameScale, 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y * gameHandler->gameScale));
    SDL_RenderDrawLine(renderer, 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x * gameHandler->gameScale), 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y * gameHandler->gameScale), 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x * gameHandler->gameScale), 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y * gameHandler->gameScale) + helecopter->size.y * gameHandler->gameScale);
    SDL_RenderDrawLine(renderer, 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x * gameHandler->gameScale), 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y * gameHandler->gameScale) + helecopter->size.y * gameHandler->gameScale, 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x * gameHandler->gameScale) + helecopter->size.x * gameHandler->gameScale, 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y * gameHandler->gameScale) + helecopter->size.y * gameHandler->gameScale);
    SDL_RenderDrawLine(renderer, 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x * gameHandler->gameScale) + helecopter->size.x * gameHandler->gameScale, 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y * gameHandler->gameScale), 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x * gameHandler->gameScale) + helecopter->size.x * gameHandler->gameScale, 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y * gameHandler->gameScale) + helecopter->size.y * gameHandler->gameScale);

    //renders the bomb
    if(helecopter->droppedBomb)
    {
        SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);

        SDL_RenderDrawLine(renderer, 
            gameHandler->offset.x + (int)(helecopter->bombPos.x * gameHandler->gameScale), 
            gameHandler->offset.y + (int)(helecopter->bombPos.y * gameHandler->gameScale), 
            gameHandler->offset.x + (int)(helecopter->bombPos.x * gameHandler->gameScale) + helecopter->bombSize.x * gameHandler->gameScale, 
            gameHandler->offset.y + (int)(helecopter->bombPos.y * gameHandler->gameScale));
        SDL_RenderDrawLine(renderer, 
            gameHandler->offset.x + (int)(helecopter->bombPos.x * gameHandler->gameScale), 
            gameHandler->offset.y + (int)(helecopter->bombPos.y * gameHandler->gameScale), 
            gameHandler->offset.x + (int)(helecopter->bombPos.x * gameHandler->gameScale), 
            gameHandler->offset.y + (int)(helecopter->bombPos.y * gameHandler->gameScale) + helecopter->bombSize.y * gameHandler->gameScale);
        SDL_RenderDrawLine(renderer, 
            gameHandler->offset.x + (int)(helecopter->bombPos.x * gameHandler->gameScale), 
            gameHandler->offset.y + (int)(helecopter->bombPos.y * gameHandler->gameScale) + helecopter->bombSize.y * gameHandler->gameScale, 
            gameHandler->offset.x + (int)(helecopter->bombPos.x * gameHandler->gameScale) + helecopter->bombSize.x * gameHandler->gameScale, 
            gameHandler->offset.y + (int)(helecopter->bombPos.y * gameHandler->gameScale) + helecopter->bombSize.y * gameHandler->gameScale);
        SDL_RenderDrawLine(renderer, 
            gameHandler->offset.x + (int)(helecopter->bombPos.x * gameHandler->gameScale) + helecopter->bombSize.x * gameHandler->gameScale, 
            gameHandler->offset.y + (int)(helecopter->bombPos.y * gameHandler->gameScale), 
            gameHandler->offset.x + (int)(helecopter->bombPos.x * gameHandler->gameScale) + helecopter->bombSize.x * gameHandler->gameScale, 
            gameHandler->offset.y + (int)(helecopter->bombPos.y * gameHandler->gameScale) + helecopter->bombSize.y * gameHandler->gameScale);
    }
    //renders the bullet
    if(helecopter->firedGun)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

        SDL_RenderDrawLine(renderer, 
            gameHandler->offset.x + helecopter->helecopterPos.x * gameHandler->gameScale, 
            gameHandler->offset.y + helecopter->helecopterPos.y * gameHandler->gameScale, 
            gameHandler->offset.x + helecopter->bulletPos.x * gameHandler->gameScale, 
            gameHandler->offset.y + helecopter->bulletPos.y * gameHandler->gameScale);
    }
}