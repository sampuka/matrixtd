#include "MatrixTD.h"

#include <SDL.h>

#include <stdlib.h>
#include <stdio.h>

struct MatrixTD* MatrixTD_create()
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
    
    struct MatrixTD *newMatrixTD = malloc(sizeof (struct MatrixTD));

    newMatrixTD->status = StatusUnknown;
    
///*
    if(pthread_create(&newMatrixTD->mainloop_thread, NULL, MatrixTD_mainloop, newMatrixTD))
    {
	printf("Failed to create thread!\n");
    }
    else
    {
	printf("Thread created\n");
    }
//*/

//    MatrixTD_mainloop(newMatrixTD);

    while(newMatrixTD->status != StatusUnknown)
	;

    if (newMatrixTD->status == StatusFailed)
	return NULL;
    else
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
    struct MatrixTD *game = (struct MatrixTD*) _game;

    uint8_t succes = MatrixTD_init(game);
    
    if (succes == 1)
	game->status = StatusSucces;
    else
	game->status = StatusFailed;
    
    SDL_Event e;

    while (!game->quit)
    {
	MatrixTD_draw(game);
	while(SDL_PollEvent(&e) != 0 && (!game->quit))
	{
	    switch (e.type)
	    {
	    case SDL_QUIT:
		game->quit = 1;
		break;

	    case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
		    printf("ESC pressed\n");
		    game->quit = 1;
		}
		break;

	    case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT)
		{
		    printf("Mouse click at (%d, %d)\n", e.button.x, e.button.y);
		}
		break;

	    case SDL_MOUSEMOTION:
		game->mousex = e.motion.x;
		game->mousey = e.motion.y;
		//printf("Mouse at (%d, %d)\n", game->mousex, game->mousey);
		break;

	    default:
		printf(",");
		fflush(stdout);
	    }
	}
	SDL_Delay(100);
    }

    MatrixTD_destroy(game);

    return NULL;
}

uint8_t MatrixTD_init(struct MatrixTD *game)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	return 0;
    }
    else
	printf("SDL initialized\n");

    game->window = SDL_CreateWindow("Matrix TD 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);

    if (game->window == NULL)
    {
	printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	return 0;
    }
    else
    {
	printf("Window created\n");
    }

    if (SDL_SetWindowFullscreen(game->window, SDL_WINDOW_FULLSCREEN_DESKTOP))
    {
	printf("Could not go fullscreen!\n");
    }
    else
    {
	printf("Went fullscreen\n");
    }

    //Check for failure?
    game->renderer = SDL_CreateRenderer(game->window, -1, 0);

    game->quit = 0;

    game->map = MatrixTDMap_create("Test map");

    if (game->map == NULL)
    {
	printf("Could not create map. Fatal!\n");
	return 0;
    }

    return 1;
}

void MatrixTD_draw(struct MatrixTD *game)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    //SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
    //SDL_RenderDrawLine(game->renderer, 40, 40, 180, 300);

    SDL_Rect rect;
    struct MapEntity ent;
    int w;
    int h;
    SDL_GetRendererOutputSize(game->renderer, &w, &h);
    int tilesize; //If non-integer, integer round-down will cause rendering error. Looks like grid of background color

    if (w/game->map->xsize < h/game->map->ysize)
	tilesize = w/game->map->xsize; 
    else
	tilesize = h/game->map->ysize;

    //Draw Map
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
