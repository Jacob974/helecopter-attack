#include "utils.h"

Int8 detectCollision(Vec2f tilePos, Vec2f tileSize, Vec2f lineOrigin, Vec2f lineEnd)
{
    Vec2f tileNearSide;
    Vec2f tileFarSide;

    //creates nessesary variables for the ratios in the next step
    if(lineEnd.x > lineOrigin.x)
    {
        tileNearSide.x = tilePos.x;
        tileFarSide.x = tilePos.x + tileSize.x;
    }
    else
    {
        tileNearSide.x = tilePos.x + tileSize.x;
        tileFarSide.x = tilePos.x;
    }
    if(lineEnd.y > lineOrigin.y)
    {
        tileNearSide.y = tilePos.y;
        tileFarSide.y = tilePos.y + tileSize.y;
    }
    else
    {
        tileNearSide.y = tilePos.y + tileSize.y;
        tileFarSide.y = tilePos.y;
    }

    double nearXRatio = (tileNearSide.x - lineOrigin.x) / (lineEnd.x - lineOrigin.x);
    double farXRatio = (tileFarSide.x - lineOrigin.x) / (lineEnd.x - lineOrigin.x);
    double nearYRatio = (tileNearSide.y - lineOrigin.y) / (lineEnd.y - lineOrigin.y);
    double farYRatio = (tileFarSide.y - lineOrigin.y) / (lineEnd.y - lineOrigin.y);

    if((nearXRatio > nearYRatio)&&(nearXRatio < farYRatio)&&(nearXRatio < 1.0)&&(nearXRatio >= 0))
        return 1;
    if((nearYRatio < farXRatio)&&(nearYRatio < farXRatio)&&(nearYRatio < 1.0)&&(nearYRatio >= 0))
        return 1;
    return 0;
}
Int8 rectIntersectRect(Vec2f tile1Pos, Vec2 tile1Size, Vec2f tile2Pos, Vec2 tile2Size)
{
    if(
        ((tile1Pos.x + (double)(tile1Size.x)) < tile2Pos.x)||
        ((tile2Pos.x + (double)(tile2Size.x)) < tile1Pos.x)||
        ((tile1Pos.y + (double)(tile1Size.y)) < tile2Pos.y)||
        ((tile2Pos.y + (double)(tile2Size.y)) < tile1Pos.y)
    ) return 0;
    return 1;
}