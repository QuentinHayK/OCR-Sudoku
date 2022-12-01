#ifndef GRAYSCALE
#define GRAYSCALE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

#include "matrix.h"

Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format, unsigned char* pixel);
Matrix* surface_to_grayscale(SDL_Surface* surface);

#endif
