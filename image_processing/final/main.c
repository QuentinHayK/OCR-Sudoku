#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "canny_edge_detector.h"

// Loads an image in a surface.
// The format of the surface is SDL_PIXELFORMAT_RGB888.
//
// path: Path of the image.
SDL_Surface* load_image(const char* path)
{
    SDL_RWops *io = SDL_RWFromFile(path, "r");
    SDL_Surface* tmp = IMG_Load_RW(io, 1);
    if (tmp == NULL)
        errx(EXIT_FAILURE, "load_image -line 13-: %s", SDL_GetError());

    SDL_Surface* surface =
        SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGB888, 0);

    if (surface == NULL)
        errx(EXIT_FAILURE, "load_image -line 19-: %s", SDL_GetError());

    free(tmp);

    return surface;
}


int main(int argc, char **argv)
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: image-file");

    SDL_Surface *image = load_image(*(argv+1));
    if (image == NULL)
        errx(EXIT_FAILURE, "main: %s", SDL_GetError());

    SDL_Surface **hori_vert = gradient_image(image);
    IMG_SaveJPG(image, "test.png", 100);
    IMG_SaveJPG(*hori_vert, "test_hori_grad.png", 100);
    IMG_SaveJPG(*(hori_vert+1), "test_vert_grad.png", 100);
    free(image);
    free(*hori_vert);
    free(*(hori_vert+1));

    return 0;
}
