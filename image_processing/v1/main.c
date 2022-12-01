#include <stdio.h>
#include <stdlib.h>

#include "grayscale.h"
#include "gradients.h"

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

    for (int i=0, j=0; i<matrix->h; i+=1)
    {
        Uint8 r, g, b;
        SDL_GetRGB(pixels[i*matrix->w + j], format, &r, &g, &b);
        matrix->mat[i][j] = r;

        j += 1;
        if (j == matrix->w)
        {
            i += 1;
            j = 0;
        }
    }

    return matrix;
}

void to_surface(Matrix* mat, SDL_Surface* surface)
{
    Uint32* pixels = surface->pixels;
    SDL_PixelFormat* format = surface->format;
    int i = 0,
        j = 0,
        width = mat->w;

    while (i < mat->h)
    {
        Uint8 r, g, b;
        unsigned char pixel = mat->mat[i][j];
        r = pixel;
        g = pixel;
        b = pixel;
        pixels[i*width + j] = SDL_MapRGB(format, r, g, b);

        j += 1;
        if (j == mat->w)
        {
            i += 1;
            j = 0;
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
    save(mat, s, "test.bmp");
    /*
    Matrix** gradients = gradient_magnitude(mat);

    save(gradients[0], s, "gradx.bmp");
    save(gradients[0], s, "gradx.bmp");
*/

    return 0;
}
