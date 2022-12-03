#include <stdio.h>
#include <stdlib.h>

#include "grayscale.h"
#include "gradients.h"
#include "gaussian_blur.h"

SDL_Surface* load_image(char* path)
{
    SDL_Surface * surface = IMG_Load(path);
    if (surface == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    
    SDL_Surface * surface2 = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);
    SDL_FreeSurface(surface);
    return surface2;
}

Matrix* to_matrix(SDL_Surface* surface)
{
    Matrix* matrix = new_mat(surface->h, surface->w);
    SDL_PixelFormat* format = surface->format;
    Uint32* pixels = surface->pixels;
    int height = matrix->h;
    int width = matrix->w;

    for (int i=0; i<height; i+=1)
    {
        for (int j=0; j<width; j+=1)
        {
            Uint8 r, g, b;
            SDL_GetRGB(pixels[i*width + j], format, &r, &g, &b);
            matrix->mat[i][j] = r;
        }
    }

    return matrix;
}

void to_surface(Matrix* mat, SDL_Surface* surface)
{
    Uint32* pixels = surface->pixels;
    SDL_PixelFormat* format = surface->format;
    int height = mat->h;
    int width = mat->w;

    for (int i=0; i<height; i+=1)
    {
        for (int j=0; j<width; j+=1)
        {
            Uint8 r, g, b;
            unsigned char pixel = mat->mat[i][j];
            r = pixel;
            g = pixel;
            b = pixel;

            Uint32 color = SDL_MapRGB(format, r, g, b);
            pixels[i*width +j] = color;
        }
    }
}

void save(Matrix* mat, SDL_Surface* surface, char* path)
{
    to_surface(mat, surface);
    SDL_SaveBMP(surface, path);
}

int main(int argc, char** argv)
{
    if (argc != 2)
        return 0;

    SDL_Surface* s = load_image(argv[1]);
    
    Matrix* mat = surface_to_grayscale(s);
    save(mat, s, "img/0grayscale.bmp");

    gaussian_filter(mat);
    save(mat, s, "img/1gaussian_blur.bmp");

    Matrix** grads = gradient_magnitude(mat);

    save(grads[0], s, "img/2gradx.bmp");
    save(grads[1], s, "img/3grady.bmp");

    save(mat, s, "img/4grad.bmp");

    freeMat(mat);
    free(grads[0]);
    free(grads[1]);
    free(grads);

    return 0;
}
