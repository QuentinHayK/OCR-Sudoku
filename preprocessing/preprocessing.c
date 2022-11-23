#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL.h>

/*====================GRAYSCALE====================*/

void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void event_loop(SDL_Renderer* renderer, SDL_Texture* colored, SDL_Texture* grayscale)
{
    SDL_Event event;
    SDL_Texture* t = colored;
    int acc = 0;

    while (1)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                return;

            case SDL_KEYDOWN:
                if (acc % 2 == 0)
                { 
                    draw(renderer, grayscale);
                    acc ++;
                }
                else
                {
                    draw(renderer, colored);
                    acc ++;
                }
                break;

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    draw(renderer, t);
                break;
        }
    }
}

SDL_Surface* load_image(const char* path)
{
    SDL_Surface * surface = IMG_Load(path);
    if (surface == NULL)
    errx(EXIT_FAILURE, "%s", SDL_GetError());
    
    SDL_Surface * surface2 = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);
    SDL_FreeSurface(surface);
    return surface2;
}

//For one pixel.
Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    Uint8 average = (0.3 * r) + (0.59 * g) + (0.11 * b);
    r = average;
    g = average;
    b = average;
    Uint32 color = SDL_MapRGB(format, r, g, b);
    return color;
}

//For all pixels.
void surface_to_grayscale(SDL_Surface* surface)
{
    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    SDL_PixelFormat* format = surface->format;
    SDL_LockSurface(surface);

    for(int acc = 0; acc < len; acc ++)
    {
        pixels[acc] = pixel_to_grayscale(pixels[acc], format);
    }
    SDL_UnlockSurface(surface);
}


/*====================FILTRAGE====================*/
/*
#define X 30
#define Y 30
#define R 5

//Initialise une liste en mettant les valeurs de 0 à len
void Init_Matrix(int * list, int len)
{
	for (int i = 0; i < len; i++)
		list[i] = i;
}


//Fonction qui créer la liste de pixels, puis qui la copie dans list
void Init_list_pixels(SDL_Surface* surface, Uint32 list)
{
	Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    SDL_LockSurface(surface);

    for(int acc = 0; acc < len; acc++)
    	list[acc] = pixels[acc];
    									
    SDL_UnlockSurface(surface);
}



// Fonction pour printq la matrice

void Print_Mat(int * list, int size_x, int size_y)
{
	printf("\n");
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			printf("%3d ", list[i*size_x+j]);
		}
		printf("\n");
	}
	printf("\n");
}



void Init_List_with_Radius(Uint * list, int r, int x, int y, Uint * new_list, SDL_Surface* surface)
{
	int size = 2*r+1;

	int i_min = x - r < 0 ? 0 : x - r;
	int i_max = x + r >= size ? size - 1 : x + r;
	int j_min = y - r < 0 ? 0 : y - r;
	int j_max = y + r >= size ? size - 1 : y + r;

	int len = surface->w * surface->h;
    SDL_PixelFormat* format = surface->format;

	for(int i = i_min; i <= i_max*r; i++)
	{
		for (int j = j_min; j <= j_max*r; j++)
		{
			Uint8 r, g, b;
			SDL_GetRGB(list[i*Y+j], format, &r, &g, &b);
			Uint32 color = SDL_MapRGB(format, r, g, b);
			new_list[(i-i_min)*size+(j-j_min)] = color;
		}
	} 
}


void tri(Uint32* mat[], int len)
{
    int c = 0;
    for(int i = 0; i < len - 1; i ++)
        for(int j = i + 1; j < len; j ++)
            if ( [mati] > mat[j] )
        	{
                c = mat[i];
        		mat[i] = mat[j];
        		mat[j] = c;
        	}
}


Uint32* return_mediane(Uint32* new_list, int len)
{	
	tri(new_list, len);
	return new_list[len / 2];
}


void filtrage(Uint32* list, int len, Uint32* new_list)
{
	for(int acc = 0; acc < len; acc++)
	{
		
		list[acc] = return_mediane(new_list, len);
	}
}
*/


/*====================BINARISATION====================*/
/*
// Calcul du seuil de binarisation
Uint32 calcul_seuil(SDL_Surface* surface)
{
    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    SDL_PixelFormat* format = surface->format;
    SDL_LockSurface(surface);
    Uint32 sum = 0;
    Uint32 nb_pixels = 0;

    for(int acc = 0; acc < len; acc++)
    {
        nb_pixels ++;
        sum +=  pixel_to_grayscale(pixels[acc], format);
    }

    return sum / nb_pixels;
}

// Pour changer la couleur selon le seuil d'un pixel.
Uint32 pixel_to_binarisation(SDL_Surface* surface, Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint32 seuil = calcul_seuil(surface);
    Uint32 grayscale = pixel_to_grayscale(pixel_color, format);
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);

    if (grayscale > seuil)
    {
        Uint8 average = 255;
        r = average;
        g = average;
        b = average;
    }

    else
    {
        Uint8 average = 0;
        r = average;
        g = average;
        b = average;
    }

    Uint32 color = SDL_MapRGB(format, r, g, b);
    SDL_UnlockSurface(surface);
    return color;
}

void surface_to_binarisation(SDL_Surface* surface)
{
    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    SDL_PixelFormat* format = surface->format;
    SDL_LockSurface(surface);

    for(int acc = 0; acc < len; acc ++)
    {
        pixels[acc] = pixel_to_binarisation(surface, pixels[acc], format);
    }
    SDL_UnlockSurface(surface);
}
*/

int main(int argc, char** argv)
{
    //Checks the number of arguments.
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: image-file");

    // Initializes the SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // Creates a window.
    SDL_Window* window = SDL_CreateWindow("Display", 0, 0, 640, 400, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // Creates a renderer.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // - Create a surface from the colored image.
    SDL_Surface* surface = load_image(argv[1]);
    if (surface == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // - Resize the window according to the size of the image.
    int w = 640;
    int h = 400;
    SDL_SetWindowSize(window, surface->w, surface->h);

    // - Create a texture from the colored surface.
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    // - Convert the surface into grayscale.
 	surface_to_grayscale(surface);
 	//filtrage(surface);
    //binarisation(surface);

    // - Create a new texture from the grayscale surface.
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Texture * texture2 = SDL_CreateTextureFromSurface(renderer, surface);
 
    // - Free the surface.
    SDL_FreeSurface(surface);
    event_loop(renderer, texture, texture2);
    // - Dispatch the events.
    // - Destroy the objects.
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}