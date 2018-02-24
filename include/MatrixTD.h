#ifndef MATRIX_TD_H
#define MATRIX_TD_H

#include <SDL.h>

#include <inttypes.h>

struct MatrixTD
{
    SDL_Window* window;
    uint8_t quit;
};

struct MatrixTD* MatrixTD_create();

void MatrixTD_mainloop(struct MatrixTD *game);

uint8_t MatrixTD_isOpen(struct MatrixTD *game);

#endif
