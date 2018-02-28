#ifndef ENEMY_H
#define ENEMY_H

#include "inttypes.h"

enum enemytype
{
    SimpleEnemy,
    FastEnemy,
    ArmorEnemy,
    BossEnemy
};

struct Enemy
{
    enum enemytype type;
    uint16_t wave;
    int32_t maxhealth;
    int32_t health;
    int16_t gold;
    float speed;
    float xpos;
    float ypos;
};

struct Enemy* Enemy_create(enum enemytype type, uint16_t wave);

#endif
