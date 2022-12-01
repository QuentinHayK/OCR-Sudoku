#include "grayscale.h"

//For one pixel.
Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format, unsigned char* pixel)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    Uint8 average = (0.3 * r) + (0.59 * g) + (0.11 * b);
    *pixel = average;
    r = average;
    g = average;
    b = average;
    Uint32 color = SDL_MapRGB(format, r, g, b);
    
    return color;
}

//For all pixels.
Matrix* surface_to_grayscale(SDL_Surface* surface)
{
    Matrix* mat = new_mat(surface->h, surface->w);

    Uint32* pixels = surface->pixels;
    SDL_PixelFormat* format = surface->format;
    SDL_LockSurface(surface);

    for (int i=0, j=0; i<mat->h;)
    {
        int pos = i*mat->w+j;
        pixels[pos] = pixel_to_grayscale(pixels[pos], format, mat->mat[i]+j);

        j += 1;
        if (j == mat->w)
        {
            i += 1;
            j = 0;
        }
    }
    
    SDL_UnlockSurface(surface);

    return mat;
}
