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
        helecopter->bombVelocity.y += 0.5;
        if(helecopter->bombVelocity.y > 5)
        {
            helecopter->bombVelocity.y = 10;
        }

        helecopter->bombPos.y += helecopter->bombVelocity.y;
        helecopter->bombPos.x += helecopter->bombVelocity.x;

        if(((int)(helecopter->bombPos.y) + helecopter->bombSize.y >= gameHandler->groundHight) && (helecopter->bombExists == 1))
        {
            //bomb has exploded
            helecopter->bombPos.y = gameHandler->groundHight - helecopter->bombSize.y; //puts the bomb on the ground
            Vec2f bombExplodePos = (Vec2f){.x = helecopter->bombPos.x, .y = (double)(gameHandler->groundHight)};
            Vec2 bombExplodeSize = (Vec2){.x = helecopter->bombSize.x + 40, .y = 150};
            helecopter->bombExists = 0;

            addexplosion(gameHandler, bombExplodePos, 3.0);

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
        helecopter->bombVelocity = helecopter->velocity;
    }
}