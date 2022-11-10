#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <math.h>


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





SDL_Surface* rotation (SDL_Surface* Start_surface, int angle)
{
    
    int w = Start_surface->w;
    int h = Start_surface->h;
    
    double radian = (M_PI*angle/180);
    int center_x = w / 2;
    int center_y = h / 2;
   

    //int new_w = (int)(w * cos(radian) + h * sin(radian));
    //int new_h = (int)(w * sin(radian) + h * cos(radian));
    float point1x = ((w/2) - (w*cos(radian)*cos(radian)));
    float point1y = (-(h/2) - (w*sin(radian)*cos(radian)));
    float point2x = ((w/2) + (h*sin(radian)*cos(radian)));
    float point2y = (-(h/2) + (h*sin(radian)*sin(radian)));
    float point3x = (-(w/2) + (w*cos(radian)*cos(radian)));
    float point3y = ((h/2) + (w*sin(radian)*cos(radian)));
    float point4x = (-(w/2) - (h*sin(radian)*cos(radian)));
    float point4y = (-(h/2) + (h*cos(radian)*cos(radian)));


    float minx = fminf(0,fminf(point2x,fminf(point3x,point4x)));
    float miny = fminf(0,fminf(point2y,fminf(point3y,point4y)));


    int new_w = (int)sqrt(((point1x-point2x)*(point1x-point2x)) + ((point1y-point2y)*(point1y-point2y)));
    int new_h = (int)sqrt(((point3x-point4x)*(point3x-point4x)) + ((point3y-point4y)*(point3y-point4y)));
 


    SDL_Surface* Dest_surface = SDL_CreateRGBSurface(0, new_w, new_h, 32, 0, 0, 0, 0);
    
    
    Uint32* Dpixels = Dest_surface->pixels;
    Uint32* Spixels = Start_surface->pixels;

    
    int Dlock = SDL_LockSurface(Dest_surface);
    if (Dlock!=0)
        errx(EXIT_FAILURE, "Erreur SDL_Lock2 : %s", SDL_GetError());

    
    int Slock = SDL_LockSurface(Start_surface);
    if (Slock!=0)
        errx(EXIT_FAILURE, "Erreur SDL_Lock start : %s", SDL_GetError());


    //Pixel[x][y]=Pixel[x * w + y]
    
    
    //trouver comment positionner les pixels pour avoir l'angle voulu
    for (int x = 0; x<w; x++)
    {
        for (int y = 0; y<h; y++)
        {
            
            /*
            int new_x = (int)((x - center_x) * cos(radian) - (y - center_y) * sin(radian) + center_x);
            int new_y = (int)((x - center_x) * sin(radian) + (y - center_y) * cos(radian) + center_y);
               */

            int new_x = (int)((x+minx)*cos(radian)+(y+miny)*sin(radian));
            int new_y = (int)((y+miny)*cos(radian)-(x+minx)*sin(radian));

            if (new_x>=0 && new_x<w && new_y>=0 && new_y<h)
            {
                Dpixels[x * w + y] = Spixels[new_x * w + new_y];
            }
        }
    }

    Dest_surface = SDL_CreateRGBSurfaceWithFormatFrom(Dpixels, Start_surface->w, Start_surface->h, 32, Start_surface->pitch, Start_surface->format->format);
    
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
    

    //EXEC
    SDL_Surface* Start_surface = load_image(argv[1]);


    SDL_SetWindowSize(window, w, h);   

    //Je crée une nouvelle surface avec rotation de l'ancienne surface
    
    SDL_Surface* Dest_surface = rotation(Start_surface,atoi(argv[2]));


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

