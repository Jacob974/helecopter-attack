#include "helecopter.h"
#include "utils.h"
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
    if(abs(helecopter->velocity.x) > 10.0)
    {
        helecopter->velocity.x = 10 * helecopter->velocity.x / abs(helecopter->velocity.x);
    }
    if(abs(helecopter->velocity.y) > 10.0)
    {
        helecopter->velocity.y = 10 * helecopter->velocity.y / abs(helecopter->velocity.y);
    }
    
    
    helecopter->helecopterPos.x += helecopter->velocity.x;
    helecopter->helecopterPos.y += helecopter->velocity.y;
    
}
void helecopterFireGun(Helecopter* helecopter, Vec2 direction, GameHandler* gameHandler)
{
    /*const variables*/
    const int bulletXSpeed = 20;
    const int bulletYSpeed = 10;

    /*bullet update*/
    for(int i = 0; i < helecopter->bulletListSize; i++)
    {
        helecopter->bulletList[i].x += bulletXSpeed;
        helecopter->bulletList[i].y += bulletYSpeed;
    }

    /*adds another bullet*/
    if(helecopter->shootGun == 1)
    {
        helecopter->bulletListSize++;
        helecopter->bulletList = realloc(helecopter->bulletList, helecopter->bulletListSize * sizeof(Vec2f));
        helecopter->bulletList[helecopter->bulletListSize - 1] = helecopter->helecopterPos;
    }

    for(int i = 0; i < helecopter->bulletListSize; i++)
    {
        //detects if bullet hit soldier
        // for(int j = 0; j < gameHandler->soldierAmount; j++)
        // {
        //     //not important now
        // }

        //detects if it hits a building
        for(int j = 0; j < gameHandler->buildingAmount; j++)
        {
            if(helecopter->bulletList[i].x > gameHandler->buildingList[j].pos && 
               helecopter->bulletList[i].x < (gameHandler->buildingList[j].pos + gameHandler->buildingList[j].size.x) &&
               helecopter->bulletList[i].y > (gameHandler->groundHight - gameHandler->buildingList[j].size.y) && 
               helecopter->bulletList[i].y < gameHandler->groundHight)
            {
                gameHandler->buildingList[j].damage -= 0.01;
                if(gameHandler->buildingList[j].damage <= 0)
                {
                    buildingRemove(gameHandler, j);
                }
                deleteElement(helecopter->bulletList, i, helecopter->bulletListSize, Vec2f);
            }
        }
        //detects if it hits a missile pad
        for(int j = 0; j < gameHandler->missilePadAmount; j++) 
        {
            if(helecopter->bulletList[i].x > gameHandler->missilePadList[j].pos && 
            helecopter->bulletList[i].x < (gameHandler->missilePadList[j].pos + gameHandler->missilePadList[j].size.x) &&
            helecopter->bulletList[i].y > (gameHandler->groundHight - gameHandler->missilePadList[j].size.y) && 
            helecopter->bulletList[i].y < gameHandler->groundHight)
            {
                gameHandler->missilePadList[j].damage -= 0.01;
                if(gameHandler->missilePadList[j].damage <= 0)
                {
                    missilePadRemove(gameHandler, j);
                }
                deleteElement(helecopter->bulletList, i, helecopter->bulletListSize, Vec2f);
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