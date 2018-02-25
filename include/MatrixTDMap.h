#ifndef MATRIX_TD_MAP
#define MATRIX_TD_MAP

#include "MapEntity.h"

#include <inttypes.h>

struct MatrixTDMap
{
    char mapName[100]; //Fuck your RAM I'll use all the memory I want
    struct MapEntity **grid; //2D grid of map entities, empty space, tower etc. Size dependent on map and is not predetermined.
    uint8_t xsize;
    uint8_t ysize;
};

struct MatrixTDMap* MatrixTDMap_create(char *mapName);

void MatrixTDMap_destroy(struct MatrixTDMap *map);

#endif
