//-------------------------------
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <math.h>
//--------------------------------


//initialisation des parametres de la window
const int WIDTH = 1000;
const int HEIGHT = 1000;





void draw_a(SDL_Renderer* renderer, SDL_Texture* texture)
{
    int copy = SDL_RenderCopy(renderer, texture, NULL, NULL);
    if (copy != 0)         
	    errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_RenderPresent(renderer);
}





void event_loop_a(SDL_Renderer* renderer, SDL_Texture* texture)
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
                     draw_a(renderer, t);                                    
                }                                                               
		        break;
	        }
		    break;
	    }

    } 
}





SDL_Surface* load_image_a (const char* path)
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


void Mat_Free(int **mat, size_t NbLines)
{
    for(size_t i=0; i<NbLines; i++)
    {
        free(mat[i]);
    }
    free(mat);
}



SDL_Surface* number(int x)
{
    SDL_Surface* number;

    if(x==-1)
        number = load_image_a("src/affichage/images/none.jpg");
    if(x==0)
        number = load_image_a("src/affichage/images/zero.jpg");
    if(x==1)
        number = load_image_a("src/affichage/images/un.jpg");
    if(x==2)
        number = load_image_a("src/affichage/images/deux.jpg");
    if(x==3)
        number = load_image_a("src/affichage/images/trois.jpg");
    if(x==4)
        number = load_image_a("src/affichage/images/quatre.jpg");
    if(x==5)
        number = load_image_a("src/affichage/images/cinq.jpg");
    if(x==6)
        number = load_image_a("src/affichage/images/six.jpg");
    if(x==7)
        number = load_image_a("src/affichage/images/sept.jpg");
    if(x==8)
        number = load_image_a("src/affichage/images/huit.jpg");
    if(x==9)
        number = load_image_a("src/affichage/images/neuf.jpg");

    return number;

}



void affichage (SDL_Surface* Start_surface, int **H)
{
    SDL_Surface* nb;

    //dimensions start_surface:
    int width = Start_surface->w;
    int height = Start_surface->h;


    int x1 = (width/9)/2;
    int y1 = (width/9)/2;

    //on initialise le SDL_Rect:
    SDL_Rect dim;
    dim.x = x1;
    dim.y = y1;

    for(int x=0; x<9; x++)
    {
        for(int y=0; y<9; y++)
        {
            nb = number(H[x][y]);

            dim.x = x1*x + x*((width/9)/2)+18;
            dim.y = y1*y + y*((width/9)/2)+10-y;

            SDL_BlitSurface(nb, NULL, Start_surface, &dim);
        }
    }
}


int Affichage_Main()
{
    int statut = EXIT_SUCCESS;

    //if (argc != 6)
        //errx(EXIT_FAILURE, "not enough argument.");


    // - Initialize the SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

     // - Create a window.
     SDL_Window* window = SDL_CreateWindow("affichage_OCR", 0, 0, WIDTH, HEIGHT,
              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
     if (window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

     // - Create a renderer
     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
     if (renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

     // - Cree la surface depuis l'image
     SDL_Texture* StartText = IMG_LoadTexture(renderer, "src/affichage/images/Grille.png");
     if (StartText==NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

     int w = WIDTH;
     int h = HEIGHT;
     if (SDL_QueryTexture(StartText, NULL, NULL, &w, &h) != 0)
         errx(EXIT_FAILURE, "%s", SDL_GetError());


    //EXEC
    SDL_Surface* Start_surface = load_image_a("src/affichage/images/Grille.png");

    SDL_SetWindowSize(window, w, h);

    //argv[0]=./#executable
    //argv[1]="path file"
    
    //test de la fonction:
    int **H_mat = malloc(9*sizeof(int*));
    for(int i=0; i<9; i++)
    {
        H_mat[i] = malloc(9*sizeof(int));
    }

    //-------------------test--------------------
    
    /*
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            H_mat[i][j]=i;
        }
    }*/

    
    H_mat[0][0]=1;
    H_mat[0][1]=2;
    H_mat[0][2]=3;
    H_mat[0][3]=-1;
    H_mat[0][4]=-1;
    H_mat[0][5]=9;
    H_mat[0][6]=9;
    H_mat[0][7]=-1;
    H_mat[0][8]=4;

    H_mat[1][0]=2;
    H_mat[1][1]=8;
    H_mat[1][2]=1;
    H_mat[1][3]=1;
    H_mat[1][4]=-1;
    H_mat[1][5]=-1;
    H_mat[1][6]=5;
    H_mat[1][7]=6;
    H_mat[1][8]=6;

    H_mat[2][0]=1;
    H_mat[2][1]=3;
    H_mat[2][2]=-1;
    H_mat[2][3]=9;
    H_mat[2][4]=9;
    H_mat[2][5]=8;
    H_mat[2][6]=7;
    H_mat[2][7]=8;
    H_mat[2][8]=4;

    H_mat[3][0]=9;
    H_mat[3][1]=4;
    H_mat[3][2]=3;
    H_mat[3][3]=-1;
    H_mat[3][4]=4;
    H_mat[3][5]=7;
    H_mat[3][6]=8;
    H_mat[3][7]=1;
    H_mat[3][8]=3;

    H_mat[4][0]=2;
    H_mat[4][1]=5;
    H_mat[4][2]=4;
    H_mat[4][3]=7;
    H_mat[4][4]=3;
    H_mat[4][5]=9;
    H_mat[4][6]=8;
    H_mat[4][7]=1;
    H_mat[4][8]=5;

    H_mat[5][0]=4;
    H_mat[5][1]=6;
    H_mat[5][2]=7;
    H_mat[5][3]=8;
    H_mat[5][4]=4;
    H_mat[5][5]=4;
    H_mat[5][6]=5;
    H_mat[5][7]=6;
    H_mat[5][8]=-1;

    H_mat[6][0]=4;
    H_mat[6][1]=3;
    H_mat[6][2]=9;
    H_mat[6][3]=2;
    H_mat[6][4]=1;
    H_mat[6][5]=3;
    H_mat[6][6]=-1;
    H_mat[6][7]=8;
    H_mat[6][8]=1;

    H_mat[7][0]=6;
    H_mat[7][1]=5;
    H_mat[7][2]=4;
    H_mat[7][3]=5;
    H_mat[7][4]=4;
    H_mat[7][5]=3;
    H_mat[7][6]=2;
    H_mat[7][7]=3;
    H_mat[7][8]=1;

    H_mat[8][0]=5;
    H_mat[8][1]=1;
    H_mat[8][2]=2;
    H_mat[8][3]=-1;
    H_mat[8][4]=5;
    H_mat[8][5]=6;
    H_mat[8][6]=2;
    H_mat[8][7]=6;
    H_mat[8][8]=-1;


    SDL_Surface* fond = SDL_GetWindowSurface(window);

    
    //copie faite:
    SDL_Surface* fond_init = SDL_CreateRGBSurface(0, fond->w, fond->h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(Start_surface,NULL,Start_surface,NULL);
    SDL_SetSurfaceBlendMode(Start_surface, SDL_BLENDMODE_NONE);
   

    //on affiche chaque numéro de la matrice sur la grille
    affichage(Start_surface,H_mat);


    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, Start_surface);
    if (texture==NULL)
	    errx(EXIT_FAILURE, "%s", SDL_GetError());


    SDL_FreeSurface(Start_surface);

    event_loop_a(renderer, texture);

    Mat_Free(H_mat,9);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
