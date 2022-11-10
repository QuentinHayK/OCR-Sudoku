#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Calculate the horizontal gradient of the image
Uint32 hori_pixel_gradient(Uint32 pixel1, Uint32 pixel2,
        SDL_PixelFormat *format)
{
    Uint8 r1, g1, b1,
          r2, g2, b2;

    SDL_GetRGB(pixel1, format, &r1, &g1, &b1);
    SDL_GetRGB(pixel2, format, &r2, &g2, &b2);

    if (r1 < r2)
        r1 = 0;
    else
        r1 -= r2;

    return SDL_MapRGB(format, r1-r2, g1-g2, b1-b2);
}


//Calculate the vertical gradient of the image
Uint32 vert_pixel_gradient(Uint32 pixel1, Uint32 pixel2,
        SDL_PixelFormat *format)
{
    Uint8 r1, g1, b1,
          r2, g2, b2;
    SDL_GetRGB(pixel1, format, &r1, &g1, &b1);
    SDL_GetRGB(pixel2, format, &r2, &g2, &b2);

    if (r1 < r2)
        r1 = 0;
    else
        r1 -= r2;
    return SDL_MapRGB(format, r1, r1, r1);
}

SDL_Surface **gradient_image(SDL_Surface *image)
{
    SDL_Surface *hori = SDL_CreateRGBSurfaceFrom(image->pixels, image->w,
            image->h, 32, image->pitch, image->format->Rmask,
            image->format->Gmask, image->format->Bmask, image->format->Amask);
    if (hori == NULL)
        errx(EXIT_FAILURE, "gradient_image -line 34-:%s", SDL_GetError());

    SDL_Surface *vert = SDL_CreateRGBSurfaceFrom(image->pixels, image->w,
            image->h, 32, image->pitch, image->format->Rmask,
            image->format->Gmask, image->format->Bmask, image->format->Amask);
    if (vert == NULL)
        errx(EXIT_FAILURE, "gradient_image -line 38-:%s", SDL_GetError());

    Uint32 *pixels = image->pixels,
           *pixels_hori = hori->pixels,
           *pixels_vert = vert->pixels;
    unsigned h = image->h,
             w = image->w;

    SDL_LockSurface(image);
    SDL_LockSurface(hori);
    SDL_LockSurface(vert);
    for (unsigned int height=0; height<h; height+=1)
    {
        for (unsigned int width=0; width<w; width+=1)
        {
            if (width == w-1)
                pixels_hori[height*w + width] =
                    SDL_MapRGB(hori->format, 125, 125, 125);
            else
                *(pixels_hori+height*w + width) =
                    hori_pixel_gradient(pixels[height*w + width+1],
                            pixels[height*w + width], image->format);

            if (height == h-1)
                pixels_vert[height*w + width] =
                    SDL_MapRGB(hori->format, 125, 125, 125);
            else
                pixels_vert[height*w + width] =
                    vert_pixel_gradient(pixels[(height+1)*w + width],
                            pixels[height*w + width], image->format);
        }
    }

    SDL_UnlockSurface(image);
    SDL_UnlockSurface(hori);
    SDL_UnlockSurface(vert);

    SDL_Surface **hori_vert = malloc(2*sizeof(SDL_Surface));
    *hori_vert = hori;
    *(hori_vert+1) = vert;
    return hori_vert;
}
