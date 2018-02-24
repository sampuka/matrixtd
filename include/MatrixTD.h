#ifndef MATRIX_TD_H
#define MATRIX_TD_H

#include "MatrixTDMap.h"

#include <SDL.h>

#include <pthread.h>
#include <inttypes.h>

struct MatrixTD
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    uint8_t quit;
    struct MatrixTDMap* map;
    //pthread_t mainloop_thread;
};

struct MatrixTD* MatrixTD_create();

void MatrixTD_destroy(struct MatrixTD *game);

void* MatrixTD_mainloop(void *game);

uint8_t MatrixTD_isOpen(struct MatrixTD *game);

#endif
