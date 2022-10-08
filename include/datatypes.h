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

typedef struct Soldier
{
    int pos;
    Int8 agrovated;
} Soldier;

typedef struct Helecopter
{
    int helecopterPos;

    Vec2 bulletPos;

    Int8 containsBomb;
    Int8 droppedBomb;
    Vec2 bombPos;

    double damage;
    
} Helecopter;

typedef struct MissilePad
{
    int Pos;
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
