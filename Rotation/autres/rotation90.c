#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
//#include "test.c"
#include <err.h>


const int INIT_WIDTH = 640;
const int INIT_HEIGHT = 400;
/*---------------------------------------
void SDL_Quit(void)
const char* SDL_GetError(void)
SDL_Window* SDL_CreateWindow(const char* title, int x,  int y, int w, int h, Uint32 flags)
void SDL_Delay(Uint32 ms)
void SDL_DestroyWindow(SDL_Window* window)
---------------------------------------*/

/*--------parametres de la fenetre-------
const char* SDL_GetWindowTitle(SDL_Window* window)
void SDL_SetWindowTitle(SDL_Window* window, const char* title)
void SDL_GetWindowPosition(SDL_Window* window, int* x, int* y)
void SDL_SetWindowPosition(SDL_Window* window, int* x, int* y)
void SDL_GetWindowSize(SDL_Window* window, int* w, int* h)
void SDL_SetWindowSize(SDL_Window* window, int w, int h)
Uint32 SDL_GetWindowFlags(SDL_Window* window)
*/


/*----Agir sur la fenetre--------------
void SDL_MaximizeWindow(SDL_Window* window)
void SDL_MinimizeWindow(SDL_Window* window)
void SDL_RestoreWindow(SDL_Window* window)
void SDL_HideWindow(SDL_Window* window)
void SDL_ShowWindow(SDL_Window* window)
void SDL_RaiseWindow(SDL_Window* window)
*/


/*-------fullScreen--------
int SDL_SetWindowFullscreen(SDL_Window* window, Uint32 flags)

flags = 
_SDL_WINDOW_FULLSCREEN -> FullScreen
_SDL_WINDOW_FULLSCREEN_DESKTOP -> FullScreen avec bureau resolution
_ 0 -> en mode fenetre
-------------------------*/

//-------------------------


void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    int copy = SDL_RenderCopy(renderer, texture, NULL, NULL);
    if (copy != 0)         
	    errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_RenderPresent(renderer);
}





void event_loop(SDL_Renderer* renderer, SDL_Texture* texture)
{

    SDL_Event event;
    SDL_Texture* t = texture;

    while (1)
    {
	SDL_WaitEvent(&event);
        switch (event.type)
        {
	    // If the "quit" button is pushed, ends the event loop.             
            case SDL_QUIT:                                                      
		        return;                                                                                                                             
            // If the window is resized, updates and redraw the image           
            case SDL_WINDOWEVENT:                                               
	        {
		        if (event.window.event == SDL_WINDOWEVENT_RESIZED)              
                {                                                               
                     draw(renderer, t);                                    
                }                                                               
		        break;
	        }
		    break;
	    }

    } 
}





//SDL_Surface * IMG_Load(const char *file)
SDL_Surface* load_image (const char* path)
{
    SDL_Surface* surface_temp = IMG_Load(path);
    if (surface_temp == NULL)
        errx(EXIT_FAILURE, "failed loading image : %s", SDL_GetError());
    
    SDL_Surface* surface = SDL_ConvertSurfaceFormat(surface_temp, SDL_PIXELFORMAT_RGB888      , 0);
    SDL_FreeSurface (surface_temp);
    return surface;

    SDL_FreeSurface(surface_temp);
    return surface;
}

/*
uint16_t getPixelrotation (Image *img, int x, int y)
{
    return img->data[(img->height - x) * img->width + y];
}
*/

/*
SDL_Surface* rotation_main (SDL_Surface* surface, int degre)
{
    SDL_Surface* surfaceBis = rotozoomSurface (surface, degre, 1, 0);
    return surfaceBis;
}*/


SDL_Surface* rotation (SDL_Surface* Start_surface, int degre)
{
    
    SDL_Surface* Dest_surface = SDL_CreateRGBSurface(0, Start_surface->h, Start_surface->w, 32, 0, 0, 0, 0);

    Uint32* Spixels = Start_surface->pixels;
    Uint32* Dpixels = Dest_surface->pixels;
     
    int w1 = Start_surface->w;
    int h1 = Start_surface->h;
    int w2 = Dest_surface->w;
    int h2 = Dest_surface->h;

    int Slock = SDL_LockSurface(Start_surface);
    int Dlock = SDL_LockSurface(Dest_surface);

    if (Slock!=0)
        errx(EXIT_FAILURE, "Erreur SDL_Lock1 : %s", SDL_GetError());

    if (Dlock!=0)
        errx(EXIT_FAILURE, "Erreur SDL_Lock2 : %s", SDL_GetError());

    //Pixel[x][y]=Pixel[x * w + y]
    

    //trouver comment positionner les pixels pour avoir l'angle voulu
    for (int x = 0; x<w1; x++)
    {
        for (int y = 0; y<h1; y++)
        {
            Dpixels[y * w1 + (w1-1-x)]=Spixels[x * w1 + y];
            //printf("%d\n",Dpixels[y * Dest_surface->w + (Start_surface->w-1-x)]);
        }
    }

    Dest_surface = SDL_CreateRGBSurfaceWithFormatFrom(Dpixels, Start_surface->h, Start_surface->w, 32, Start_surface->pitch, Start_surface->format->format);
    
    if (Dest_surface == NULL)
    {
        errx(EXIT_FAILURE, "Erreur SDL_CreateRGBSurface : %s", SDL_GetError());
    }
    

    SDL_UnlockSurface(Start_surface);
    SDL_UnlockSurface(Dest_surface);

    return Dest_surface;
}


int main(int argc, char** argv)
{
    int statut = EXIT_SUCCESS;   

    if (argc != 3)
        errx(EXIT_FAILURE, "not enough argument.");

    
    // - Initialize the SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

     // - Create a window.
     SDL_Window* window = SDL_CreateWindow("Rotation_OCR", 0, 0, INIT_WIDTH, INIT_HEIGHT,
              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
     if (window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

     // - Create a renderer
     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
     if (renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

     // - Cree la surface depuis l'image
     SDL_Texture* StartText = IMG_LoadTexture(renderer, argv[1]);
     if (StartText==NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

     int w = INIT_WIDTH;
     int h = INIT_HEIGHT;
     if (SDL_QueryTexture(StartText, NULL, NULL, &w, &h) != 0)
         errx(EXIT_FAILURE, "%s", SDL_GetError());
    

     int degree = argv[2]-'0';
     //printf("%s\n",degree);

    //EXEC
    SDL_Surface* Start_surface = load_image(argv[1]);


    SDL_SetWindowSize(window, w, h);   

    //Je crée une nouvelle surface avec rotation de l'ancienne surface
    
    SDL_Surface* Dest_surface = rotation(Start_surface,degree);


    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, Dest_surface);
    if (texture==NULL)
	    errx(EXIT_FAILURE, "%s", SDL_GetError());
    

    SDL_FreeSurface(Start_surface);
    SDL_FreeSurface(Dest_surface);

    event_loop(renderer, texture);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

