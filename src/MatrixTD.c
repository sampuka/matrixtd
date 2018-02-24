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

    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);

    //printf("Test2\n");

    SDL_RenderClear(game->renderer);

    //printf("Test3\n");

    SDL_RenderPresent(game->renderer);

    //printf("Test4\n");

    //SDL_UpdateWindowSurface(game->window); // This segfaults if in another thread // And is not needed I guess

    SDL_Delay(2000);

    game->quit = 1;

    return NULL;
}

uint8_t MatrixTD_isOpen(struct MatrixTD* game)
{
    return !game->quit;
}
