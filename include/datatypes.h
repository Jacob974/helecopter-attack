//this is sorta the setup file I guess
#pragma once
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

typedef struct List
{
    int length;
    int typeSize;
    char* data;
} List;

typedef struct Explosion
{
    Vec2f pos;
    double size;
    int duration; //amount of frames left
} Explosion;

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

    Int8 stabalizeMode;
    Int8 displayMode;

    Vec2f bulletPos;
    Int8 firedGun;
    Int8 shootGun;
    Vec2f* bulletList;
    int bulletListSize;

    Int8 containsBomb;
    Int8 bombExists;
    Vec2f bombPos;
    Vec2f bombVelocity;
    Vec2 bombSize;

    double damage;
    
} Helecopter;

typedef struct Bullet
{
    int pos;
}Bullet;

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
    Helecopter* helecopter;
    Soldier* soldierList;
    Building* buildingList;
    MissilePad* missilePadList;
    Explosion* explosionList;

    int soldierAmount;
    int buildingAmount;
    int missilePadAmount;
    int explosionAmount;

    Vec2f offset;

    double gameScale;
    double alertAmount;
    double groundHight;
} GameHandler;