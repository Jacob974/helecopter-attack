#include "utils.h"

Int8 detectCollision(Vec2f tilePos, Vec2f tileSize, Vec2f lineOrigin, Vec2f lineEnd)
{

    double nearXSide = tilePos.x;
    double nearYSide = tilePos.y;
    double farXSide = tilePos.x;
    double farYSide = tilePos.y;

    //creates nessesary variables for the ratios in the next step
    if(lineOrigin.x - lineEnd.x < 0)
        farXSide += tileSize.x;
    else
        nearXSide += tileSize.x;
    if(lineOrigin.y - lineEnd.y < 0)
        farYSide += tileSize.y;
    else
        nearYSide += tileSize.y;

    //creates ratios that will be compared to each other in the next step
    double nearXRatio = (nearXSide - lineOrigin.x) / (lineOrigin.x - lineEnd.x);
    double nearYRatio = (nearYSide - lineOrigin.y) / (lineOrigin.y - lineEnd.y);
    double farXRatio = (farXSide - lineOrigin.x) / (lineOrigin.x - lineEnd.x);
    double farYRatio = (farYSide - lineOrigin.y) / (lineOrigin.y - lineEnd.y);

    //compares ratios
    if((nearXRatio >= nearYRatio) && (nearXRatio < farYRatio) && (nearXRatio >= 0)) return 1;
    if((nearYRatio >= nearXRatio) && (nearYRatio < farXRatio) && (nearYRatio >= 0)) return 1;

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