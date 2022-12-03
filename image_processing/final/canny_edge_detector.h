#ifndef CANNY_EDGE_DETECTOR
#define CANNY_EDGE_DETECTOR

#include <SDL2/SDL.h>

Uint32 hori_pixel_gradient(Uint32 pixel1, Uint32 pixel2,
        SDL_PixelFormat *format);
Uint32 vert_pixel_gradient(Uint32 pixel1, Uint32 pixel2,
        SDL_PixelFormat *format);
SDL_Surface **gradient_image(SDL_Surface *image);

#endif
