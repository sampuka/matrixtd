#include "MatrixTD.h"

#include <SDL.h>

#include <stdlib.h>
#include <stdio.h>

struct MatrixTD* MatrixTD_create()
{
///*
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	return NULL;
    }
    else
	printf("SDL initialized\n");
//*/
    
    struct MatrixTD *newMatrixTD = malloc(sizeof (struct MatrixTD));

    newMatrixTD->window = SDL_CreateWindow("Matrix TD 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);

    if (newMatrixTD->window == NULL)
    {
	printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	return NULL;
    }
    else
    {
	printf("Window created\n");
    }

    //This produces a side-effect that makes rendering with the SDL_Renderer not work
    //newMatrixTD->screenSurface = SDL_GetWindowSurface(newMatrixTD->window);

    newMatrixTD->renderer = SDL_CreateRenderer(newMatrixTD->window, -1, 0);

    newMatrixTD->quit = 0;

    newMatrixTD->map = MatrixTDMap_create("Test map");

    if (newMatrixTD->map == NULL)
    {
	printf("Could not create map. Fatal!\n");
	return NULL;
    }
    
/*
    if(pthread_create(&newMatrixTD->mainloop_thread, NULL, MatrixTD_mainloop, newMatrixTD))
    {
	printf("Failed to create thread!\n");
    }
    else
    {
	printf("Thread created\n");
    }
//*/

    MatrixTD_mainloop(newMatrixTD);

    return newMatrixTD;
}

void MatrixTD_destroy(struct MatrixTD *game)
{
    MatrixTDMap_destroy(game->map);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);

    free(game);

    SDL_Quit();
}

void* MatrixTD_mainloop(void *_game)
{
/*
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	return NULL;
    }
    else
	printf("SDL initialized\n");
//*/

    struct MatrixTD *game = (struct MatrixTD*) _game;
    //printf("Test\n");

    //printf("Test2\n");
    
    MatrixTD_draw(game);

    //printf("Test3\n");

    //printf("Test4\n");

    //SDL_UpdateWindowSurface(game->window); // This segfaults if in another thread // And is not needed I guess

    SDL_Delay(2000);

    game->quit = 1;

    return NULL;
}

void MatrixTD_draw(struct MatrixTD *game)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    //SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
    //SDL_RenderDrawLine(game->renderer, 40, 40, 180, 300);

    SDL_Rect rect;
    struct MapEntity ent;

    //Draw Map
    float tilesize = 30; //If non-integer, integer round-down will cause rendering error. Looks like grid of background color
    for (uint8_t x = 0; x < game->map->xsize; x++)
	for (uint8_t y = 0; y < game->map->ysize; y++)
	{
	    ent = game->map->grid[x][y];
	    rect.x = tilesize * x;
	    rect.y = tilesize * y;
	    rect.h = tilesize;
	    rect.w = tilesize;
	    switch(ent.type)
	    {
	    case EmptyMapEntity:
		SDL_SetRenderDrawColor(game->renderer, 200, 200, 200, 255);
		break;
		
	    case RoadMapEntity:
		SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 255);
		break;

	    case TowerMapEntity:
		SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
		break;
		
	    default:
		SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	    }

	    SDL_RenderFillRect(game->renderer, &rect);
	}

    SDL_RenderPresent(game->renderer);
}

uint8_t MatrixTD_isOpen(struct MatrixTD* game)
{
    return !game->quit;
}
