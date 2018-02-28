#include "MatrixTD.h"

#include <stdlib.h>
#include <stdio.h>

struct MatrixTD* MatrixTD_create()
{   
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
    
    if (succes == 1) //The thread that created this is reading on game->status // Maybe should also be set in _init
	game->status = StatusSucces;
    else
	game->status = StatusFailed;
    
    SDL_Event e;
    uint32_t last_frame_timestamp = SDL_GetTicks();
    uint32_t current_timestamp;
    int32_t time_to_next_frame;

    while (!game->quit)
    {
	current_timestamp = SDL_GetTicks();
	time_to_next_frame = (last_frame_timestamp + 1000/game->fps_cap) - current_timestamp; 
	//printf("Current timestamp = %u\nLast timestamp = %u\nTime for next frame %d.\n", current_timestamp, last_frame_timestamp, time_to_next_frame);
	if (time_to_next_frame > 0)
	{
	    SDL_Delay(time_to_next_frame);
	current_timestamp = SDL_GetTicks(); //Inclusion of this makes time calculations work but feels hacky
	}
	
	//Handle input
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
	    }
	}
	fflush(stdout);

	//Update state
	MatrixTDMap_update(game->map, current_timestamp - last_frame_timestamp);

	//Draw to screen
	MatrixTD_draw(game);

	last_frame_timestamp = current_timestamp;
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

    //Initialize TTF
    if (TTF_Init() == -1)
    {
	printf("SDL_ttf could not initialize! SDL_ttf error: %s\n", TTF_GetError());
	return 0;
    }

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

    game->fps_cap = 100;

    game->font = TTF_OpenFont("Cabin-Regular.ttf", 40);
    if (game->font == NULL)
    {
	printf("Failed to load font! SDL_ttf error: %s\n", TTF_GetError());
    }

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

    //Draw ticks in corner
    SDL_Color textcolor = {255, 255, 255, 0};
    char ticks_str[50];
    sprintf(ticks_str, "ticks = %u", game->map->ticks);
    SDL_Surface *ticks_surface = TTF_RenderText_Solid(game->font, ticks_str, textcolor);
    SDL_Texture *ticks_texture = SDL_CreateTextureFromSurface(game->renderer, ticks_surface);

    SDL_Rect ticks_rect;
    ticks_rect.x = 5;
    ticks_rect.y = 5;
    TTF_SizeText(game->font, ticks_str, &ticks_rect.w, &ticks_rect.h);
    //ticks_rect.w = 50;
    //ticks_rect.h = 10;

    SDL_RenderCopy(game->renderer, ticks_texture, NULL, &ticks_rect);

    SDL_RenderPresent(game->renderer);
}

uint8_t MatrixTD_isOpen(struct MatrixTD* game)
{
    return !game->quit;
}
