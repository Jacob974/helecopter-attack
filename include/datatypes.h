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
    int pos;
    Int8 agrovated;
} Soldier;

typedef struct Helecopter
{
    Vec2 size;
    Vec2 helecopterPos;

    Vec2 bulletPos;

    Int8 containsBomb;
    Int8 droppedBomb;
    Vec2 bombPos;
    Vec2 bombsize;

    double damage;
    
} Helecopter;

typedef struct MissilePad
{
    int pos;
    Vec2 size;
    Int8 missileFired;

    double damage;
} MissilePad;

typedef struct Building
{
    int pos;
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
