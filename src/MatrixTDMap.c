#include "MatrixTDMap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct MatrixTDMap* MatrixTDMap_create(char *_mapName)
{
    struct MatrixTDMap* newmap = malloc(sizeof (struct MatrixTDMap));

    strcpy(newmap->mapName, _mapName);

    if(!strcmp(newmap->mapName, "Test map"))
    {
	printf("Creating \"Test map\"\n");
	newmap->xsize = 15;
	newmap->ysize = 10;

	newmap->grid = malloc(sizeof (struct MatrixTDMap*) * newmap->xsize);
	
	for(uint8_t x = 0; x < newmap->xsize; x++)
	    newmap->grid[x] = malloc(sizeof (struct MatrixTDMap) * newmap->ysize);


	printf("mapsize %ux%u\n", newmap->xsize, newmap->ysize);

	//Setup map's tiles
	for(uint8_t x = 0; x < newmap->xsize; x++)
	    for(uint8_t y = 0; y < newmap->ysize; y++)
	    {
		//printf("(%u,%u)\n", x, y);
		if (x == 2 && y > 2 && y < 8)
		{
		    newmap->grid[x][y].type = RoadMapEntity;
		    newmap->grid[x][y].info.road.speed_mult = 1;
		}
		else if (x == 5 && y == 8)
		{
		    newmap->grid[x][y].type = TowerMapEntity;
		    newmap->grid[x][y].info.tower.type = SingleTower;
		    newmap->grid[x][y].info.tower.info.single.damage = 20;
		    newmap->grid[x][y].info.tower.info.single.range = 200;
		    newmap->grid[x][y].info.tower.info.single.cdtime = 0.5;
		}
		else
		{
		    newmap->grid[x][y].type = EmptyMapEntity;
		}
	    }

    }
    else
    {
	printf("Given mapname has no match!\n");
	return NULL;
    }

    return newmap;
};

void MatrixTDMap_destroy(struct MatrixTDMap* map)
{
    for(uint8_t x = 0; x < map->xsize; x++)
	free(map->grid[x]);
    free(map->grid);

    free(map);
}
