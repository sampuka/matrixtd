#include "MatrixTD.h"

#include <SDL.h>

#include <stdlib.h>

struct MatrixTD* MatrixTD_create()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	return NULL;
    }
    
    struct MatrixTD *newMatrixTD = malloc(sizeof (struct MatrixTD));

    newMatrixTD->window = SDL_CreateWindow("Matrix TD 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);

    if (newMatrixTD->window == NULL)
    {
	printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	return NULL;
    }

    newMatrixTD->quit = 0;
    
    return newMatrixTD;
}

uint8_t MatrixTD_isOpen(struct MatrixTD* game)
{
    return !game->quit;
}
