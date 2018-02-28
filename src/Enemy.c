#include "Enemy.h"

#include "stdlib.h"

struct Enemy* Enemy_create(enum enemytype _type, uint16_t _wave)
{
    struct Enemy *newenemy = malloc(sizeof (struct Enemy));
    
    newenemy->type = _type;
    newenemy->wave = _wave;

    newenemy->maxhealth = 100;
    newenemy->health = 100;
    newenemy->gold = 10;
    newenemy->speed = 1;
    newenemy->xpos = 2;
    newenemy->ypos = 3;
	
    return newenemy;
}

