#include "helecopter.h"
#include <stdlib.h>

void helecopterMove(Helecopter* helecopter, Vec2 direction)
{
    helecopter->helecopterPos.x += direction.x;
    helecopter->helecopterPos.y += direction.y;
}
void helecopterFireGun(Helecopter* helecopter, Vec2 direction, GameHandler* gameHandler)
{
    //takes it from screen space ant turns it into gamespace
    Vec2f realDirection;
    realDirection.x = ((double)(direction.x) * gameHandler->gameScale) + gameHandler->offset.x;
    realDirection.y = ((double)(direction.y) * gameHandler->gameScale) + gameHandler->offset.y;

    Vec2f lineOrigin = (Vec2f){.x = (double)(helecopter->helecopterPos.x + (helecopter->size.x / 2)), .y = helecopter->helecopterPos.y + helecopter->size.y};
    Vec2f lineEnd = (Vec2f){.x = (double)(realDirection.x), .y = (double)(realDirection.y)};
    
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
            gameHandler->buildingList->damage -= 0.1;
            if(gameHandler->buildingList->damage <= 0.0)
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
        Vec2f tilePos = (Vec2f){.x = gameHandler->missilePadList[i].pos, .y = gameHandler->groundHight - gameHandler->missilePadList[i].size.y};
        
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
    if(helecopter->droppedBomb)
    {
        helecopter->bombPos.y += 5;
        if(helecopter->bombPos.y + helecopter->bombsize.y >= gameHandler->groundHight)
        {
            //bomb has exploded
            helecopter->bombPos.y = gameHandler->groundHight - helecopter->bombsize.y; //puts the bomb on the ground
            Vec2 bombExplodePos = (Vec2){.x = helecopter->bombPos.x - 20, .y = gameHandler->groundHight - 100};
            Vec2 bombExplodeSize = (Vec2){.x = helecopter->bombsize.x + 40, .y = 150};

            for(int i = 0; i < gameHandler->soldierAmount; i++)
            {
                Vec2 soldierPos = (Vec2){.x = gameHandler->soldierList[i].pos, .y = gameHandler->groundHight - gameHandler->soldierList[i].size.y};
                if(rectIntersectRect(bombExplodePos, bombExplodeSize, soldierPos, gameHandler->soldierList[i].size))
                {
                    soldierRemove(gameHandler, i);
                    i--; //adjusts i since the soldier list was reallocated
                }
            }
            for(int i = 0; i < gameHandler->buildingAmount; i++)
            {
                Vec2 buildingPos = (Vec2){.x = gameHandler->buildingList[i].pos, .y = gameHandler->groundHight - gameHandler->buildingList[i].size.y};
                
                if(rectIntersectRect(helecopter->bombPos, helecopter->bombsize, buildingPos, gameHandler->buildingList[i].size))
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
                Vec2 missilePadPos = (Vec2){.x = gameHandler->missilePadList[i].pos, .y = gameHandler->groundHight - gameHandler->missilePadList[i].size.y};
                
                if(rectIntersectRect(helecopter->bombPos, helecopter->bombsize, missilePadPos, gameHandler->missilePadList[i].size))
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
}

void render()
{

}