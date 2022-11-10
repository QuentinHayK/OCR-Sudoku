//-------------------------------
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <math.h>
//--------------------------------


//initialisation des parametres de la window
const int INIT_WIDTH = 640;
const int INIT_HEIGHT = 400;





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
   
    //-----------------calcul_valeurs--------
    double radian = (M_PI*angle)/180;

    float cosine = (float)cos(radian);
    float sine = (float)sin(radian);

    float Point1x = (-(Start_surface->h)*sine);
    float Point1y = ((Start_surface->h)*cosine);
    float Point2x = ((Start_surface->w)*cosine-(Start_surface->h)*sine);
    float Point2y = ((Start_surface->h)*cosine+(Start_surface->w)*sine);
    float Point3x = ((Start_surface->w)*cosine);
    float Point3y = ((Start_surface->w)*sine);

    float minx = fminf(0,fminf(Point1x,fminf(Point2x,Point3x)));
    float miny = fminf(0,fminf(Point1y,fminf(Point2y,Point3y)));
    float maxx = fmaxf(Point1x,fmaxf(Point2x,Point3x));
    float maxy = fmaxf(Point1y,fmaxf(Point2y,Point3y));

    int Dest_Surf_w = (int)ceil(abs(maxx)-minx);
    int Dest_Surf_h = (int)ceil(abs(maxy)-miny);

    
    float center_x = Dest_Surf_w / 2;
    float center_y = Dest_Surf_h / 2;
    //---------------------------------------


    SDL_Surface* Dest_surface = SDL_CreateRGBSurface(0, Dest_Surf_w, Dest_Surf_h, 32, 0, 0, 0, 0);
    
    
    Uint32* Dpixels = Dest_surface->pixels;
    Uint32* Spixels = Start_surface->pixels;
    
    
    //---------check_lock-------------
    int Dlock = SDL_LockSurface(Dest_surface);
    if (Dlock!=0)
        errx(EXIT_FAILURE, "Erreur SDL_Lock2 : %s", SDL_GetError());

    
    int Slock = SDL_LockSurface(Start_surface);
    if (Slock!=0)
        errx(EXIT_FAILURE, "Erreur SDL_Lock start : %s", SDL_GetError());
    //--------------------------------

    
    //équivalence matrice double et simple:
    //Pixel[x][y]=Pixel[x * w + y]
    
    
    //-----------------rotation------------------------
    for (int x = 0; x<Dest_Surf_w; x++)
    {
        for (int y = 0; y<Dest_Surf_h; y++)
        {

            int new_x = (int)((x+minx)*cosine+(y+miny)*sine);
            int new_y = (int)((y+miny)*cosine-(x+minx)*sine);


            if (new_x>=0 && new_x<Start_surface->w && new_y>=0 && new_y<Start_surface->h)
            {
                    Dpixels[x * Start_surface->w + y] = Spixels[new_x * Start_surface->w + new_y];
            }
        }
    }
    //------------------------------------------------


    Dest_surface = SDL_CreateRGBSurfaceWithFormatFrom(Dpixels, Dest_Surf_w, Dest_Surf_h, 32, Start_surface->pitch, Start_surface->format->format);
    
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

