#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grayscale.h"
#include "gaussian_blur.h"
#include "gradients.h"
#include "adaptative_threshold.h"


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

void save(Matrix* mat, SDL_Surface* surface, char str[], int i)
{
    char* path = calloc(50, sizeof(char));
    char dir[] = "./res/";
    char num[] = {'0'+i, '\0'};

    strcat(path, dir);
    strcat(path, num);
    strcat(path, str);

    to_surface(mat, surface);
    SDL_SaveBMP(surface, path);

    free(path);
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Need arg\n");
        return 0;
    }

    char option[] = "-all";
    if (strcmp(argv[1], option) == 0)
        for (int i=1; i<6; i+=1)
        {
            char* path = calloc(30, sizeof(char));
            char dir[] = "./img/image_0";
            char num[] = {'0'+i, '\0'};
            char ext[] = ".jpeg";

            strcat(path, dir);
            strcat(path, num);
            strcat(path, ext);
            
            SDL_Surface* s = load_image(path);

            Matrix* mat = surface_to_grayscale(s);
            save(mat, s, "0grayscale.bmp", i);

            gaussian_filter(mat);
            save(mat, s, "1gaussian_blur.bmp", i);

            Matrix* mag = grad(mat);
            save(mag, s, "2gradx.bmp", i);

            freeMat(mat);
            freeMat(mag);
            SDL_FreeSurface(s);

            printf("%s finished\n", path);
            free(path);
        }

    else
    {
        for (int i=1; i<argc; i+=1)
        {
            SDL_Surface* s = load_image(argv[i]);

            Matrix* mat = surface_to_grayscale(s);
            save(mat, s, "0grayscale.bmp", i);

            gaussian_filter(mat);
            save(mat, s, "1gaussian_blur.bmp", i);

//            Matrix* mag = grad(mat);
//            save(mag, s, "2mag.bmp", i);

	    adap_thresh(mat);
            save(mat, s, "3thresh.bmp", i);

            freeMat(mat);
            //freeMat(mag);
            SDL_FreeSurface(s);
            
            printf("%s finished\n", argv[i]);
        }
    }

    return 0;
}
