#include "grayscale.h"

//For one pixel.
Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format, short* pixel)
{
    Uint8 r = 1, g = 1, b = 1;

    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    
    Uint8 average = (0.3 * r) + (0.59 * g) + (0.11 * b);
    
    *pixel = average;

    return SDL_MapRGB(format, average, average, average);
}

//For all pixels.
Matrix* surface_to_grayscale(SDL_Surface* surface)
{
    int height = surface->h;
    int width = surface->w;
    Matrix* mat = new_mat(height, width);
    Uint32* pixels = surface->pixels;

    SDL_LockSurface(surface);

    for (int i=0; i<height; i+=1)
    {
        for (int j=0; j<width; j+=1)
        {
            int pos = i*width + j;
            *(pixels+pos) = pixel_to_grayscale(pixels[pos], surface->format, mat->mat[i]+j);
        }
    }

    SDL_UnlockSurface(surface);

    return mat;
}
