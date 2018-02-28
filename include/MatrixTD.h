#ifndef MATRIX_TD_H
#define MATRIX_TD_H

#include "MatrixTDMap.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <pthread.h>
#include <inttypes.h>

enum SuccesStatus
{
    StatusUnknown,
    StatusFailed,
    StatusSucces
};

struct MatrixTD
{
    SDL_Window* window;
    uint16_t mousex;
    uint16_t mousey;
    SDL_Renderer* renderer;
    uint32_t fps_cap;
    TTF_Font *font;
    uint8_t quit;
    struct MatrixTDMap* map;
    pthread_t mainloop_thread;
    enum SuccesStatus status;
};

struct MatrixTD* MatrixTD_create();

void MatrixTD_destroy(struct MatrixTD *game);

void* MatrixTD_mainloop(void *game);

uint8_t MatrixTD_init(struct MatrixTD *game);

void MatrixTD_draw(struct MatrixTD *game);

uint8_t MatrixTD_isOpen(struct MatrixTD *game);

#endif
