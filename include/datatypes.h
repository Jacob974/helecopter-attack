#pragma once

typedef char Int8;
typedef short Int16;
typedef long Int32;
typedef long long Int64;

typedef struct Vec2
{
    int x;
    int y;
} Vec2;

typedef struct Vec2f
{
    double x;
    double y;
} Vec2f;

typedef struct Soldier
{
    Vec2 size;
    double pos;
    Int8 agrovated;
} Soldier;

typedef struct Helecopter
{
    Vec2 size;
    Vec2f helecopterPos;

    Vec2f velocity;

    Vec2f bulletPos;
    Int8 firedGun;

    Int8 containsBomb;
    Int8 droppedBomb;
    Vec2f bombPos;
    Vec2 bombSize;

    double damage;
    
} Helecopter;

typedef struct MissilePad
{
    double pos;
    Vec2 size;

    Int8 missileFired;
    Vec2f missilePos;
    double missileAngle; //in degrees where 90 degrees is up

    double damage;
} MissilePad;

typedef struct Building
{
    double pos;
    Vec2 size;

    int playerCount;

    double damage;
} Building;
typedef struct GameHandler
{
    Soldier* soldierList;
    int soldierAmount;

    Helecopter* helecopter;

    Building* buildingList;
    int buildingAmount;

    MissilePad* missilePadList;
    int missilePadAmount;

    Vec2f offset;

    double gameScale;
    double alertAmount;
    int groundHight;
} GameHandler;