#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Loads an image in a surface.
// The format of the surface is SDL_PIXELFORMAT_RGB888.
//
// path: Path of the image.
SDL_Surface* load_image(const char* path)
{
    SDL_Surface* tmp = IMG_Load(path);
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
    IMG_SaveJPG(image, "test.png", 100);

    return 0;
}
