#ifndef MATRIX_TD_MAP
#define MATRIX_TD_MAP

#include "MapEntity.h"
#include "mlist.h"

#include <SDL.h>

#include <inttypes.h>

struct MatrixTDMap
{
    char mapName[100]; //Fuck your RAM I'll use all the memory I want // I just discovered strdup. use instead at some point
    //The following type-autism is argueably in contrary to above statement
    uint8_t xsize; //Size of map in tiles
    uint8_t ysize;
    struct MapEntity **grid; //2D grid of map entities, empty space, tower etc. Size dependent on map and is not predetermined.
    uint16_t wavecounter; //The lastest wave that has begun spawning
    mlist enemylist; //Linked list of the enemies that are spawned and alive
    uint16_t enemies_to_spawn; //Amount of enemies to spawn this wave still
    uint32_t ticks; //The amount of unpaused ticks passed
    uint8_t paused; //bool value indicating if ticks get increased
    uint32_t next_wave_time; //The tick-value for next wave to spawn
};

struct MatrixTDMap* MatrixTDMap_create(char *mapName);

void MatrixTDMap_destroy(struct MatrixTDMap *map);

void MatrixTDMap_event(struct MatrixTDMap *map, union SDL_Event e);

void MatrixTDMap_update(struct MatrixTDMap *map, uint32_t ticks);

#endif
