#include "helecopter.h"
#include <stdlib.h>

void helecopterMove(Helecopter* helecopter, Vec2f direction)
{
    helecopter->helecopterPos.x += direction.x;
    helecopter->helecopterPos.y += direction.y;
}
void helecopterFireGun(Helecopter* helecopter, Vec2 direction, GameHandler* gameHandler)
{
    //takes it from screen space ant turns it into gamespace
    Vec2f realDirection;
    realDirection.x = ((double)(direction.x) * gameHandler->gameScale) - gameHandler->offset.x;
    realDirection.y = ((double)(direction.y) * gameHandler->gameScale) - gameHandler->offset.y;

    Vec2f lineOrigin = (Vec2f){.x = helecopter->helecopterPos.x, .y = helecopter->helecopterPos.y};
    Vec2f lineEnd = (Vec2f){.x = realDirection.x, .y = realDirection.y};
    
    //gives info to the helecopter
    helecopter->bulletPos.x = realDirection.x;
    helecopter->bulletPos.y = realDirection.y;

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
            gameHandler->buildingList[i].damage -= 1.0;
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
            gameHandler->missilePadList[i].damage -= 0.05;
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
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x), 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y), 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x) + helecopter->size.x, 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y));
    SDL_RenderDrawLine(renderer, 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x), 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y), 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x), 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y) + helecopter->size.y);
    SDL_RenderDrawLine(renderer, 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x), 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y) + helecopter->size.y, 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x) + helecopter->size.x, 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y) + helecopter->size.y);
    SDL_RenderDrawLine(renderer, 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x) + helecopter->size.x, 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y), 
        gameHandler->offset.x + (int)(helecopter->helecopterPos.x) + helecopter->size.x, 
        gameHandler->offset.y + (int)(helecopter->helecopterPos.y) + helecopter->size.y);

    //renders the bomb
    if(helecopter->droppedBomb)
    {
        SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);

        SDL_RenderDrawLine(renderer, 
            gameHandler->offset.x + (int)(helecopter->bombPos.x), 
            gameHandler->offset.y + (int)(helecopter->bombPos.y), 
            gameHandler->offset.x + (int)(helecopter->bombPos.x) + helecopter->bombSize.x, 
            gameHandler->offset.y + (int)(helecopter->bombPos.y));
        SDL_RenderDrawLine(renderer, 
            gameHandler->offset.x + (int)(helecopter->bombPos.x), 
            gameHandler->offset.y + (int)(helecopter->bombPos.y), 
            gameHandler->offset.x + (int)(helecopter->bombPos.x), 
            gameHandler->offset.y + (int)(helecopter->bombPos.y) + helecopter->bombSize.y);
        SDL_RenderDrawLine(renderer, 
            gameHandler->offset.x + (int)(helecopter->bombPos.x), 
            gameHandler->offset.y + (int)(helecopter->bombPos.y) + helecopter->bombSize.y, 
            gameHandler->offset.x + (int)(helecopter->bombPos.x) + helecopter->bombSize.x, 
            gameHandler->offset.y + (int)(helecopter->bombPos.y) + helecopter->bombSize.y);
        SDL_RenderDrawLine(renderer, 
            gameHandler->offset.x + (int)(helecopter->bombPos.x) + helecopter->bombSize.x, 
            gameHandler->offset.y + (int)(helecopter->bombPos.y), 
            gameHandler->offset.x + (int)(helecopter->bombPos.x) + helecopter->bombSize.x, 
            gameHandler->offset.y + (int)(helecopter->bombPos.y) + helecopter->bombSize.y);
    }
    //renders the bullet
    if(helecopter->firedGun)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

        SDL_RenderDrawLine(renderer, 
            gameHandler->offset.x + helecopter->helecopterPos.x, 
            gameHandler->offset.y + helecopter->helecopterPos.y, 
            helecopter->bulletPos.x + gameHandler->offset.x, 
            helecopter->bulletPos.y + gameHandler->offset.y);
    }
}