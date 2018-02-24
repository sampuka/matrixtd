#ifndef MAP_ENTITY_H
#define MAP_ENTITY_H

//This is a mess because I have an idealist vision about data structures. Fuck you
//Also I am undecided about capitalizing first letter
//Hopefully this file will fuck me in the ass so I will learn to not do this
//It compiles

enum MapEntityType
{
    EmptyMapEntity,
    TowerMapEntity,
    RoadMapEntity
};

enum TowerType
{
    SingleTower,
    SplashTower,
    SniperTower
};

struct SingleTower
{
    float damage;
    float range;
    float cdtime;
};

struct SplashTower
{
    float damage;
    float range;
    float cdtime;
    float splashrange;
    float splashdamage;
};

struct SniperTower
{
    float damage;
    float range;
    float cdtime;
};

union TowerInfo
{
    struct SingleTower single;
    struct SplashTower splash;
    struct SniperTower sniper;
};

struct Tower
{
    enum TowerType type;
    union TowerInfo info;
};

struct Road
{
    float speed_mult;
};

union MapEntityInfo
{
    struct Tower tower;
    struct Road road;
};

struct MapEntity
{
    enum MapEntityType type;
    union MapEntityInfo info;
};

#endif
