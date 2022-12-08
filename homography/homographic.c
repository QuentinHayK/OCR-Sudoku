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

//----------------------------------
void mult_mat(float **mat1, float **mat2, float **res);
//----------------------------------



void Mat_Free(float **mat, size_t NbLines)
{
    printf("size of mat : %ld\n", sizeof(mat));
    for(size_t i=0; i<NbLines; i++)
    {
        free(mat[i]);
    }
    free(mat);
}



SDL_Surface* homography (SDL_Surface* Start_surface, float **H)
{
   
    //-----------------calcul_valeurs--------
    int Dest_Surf_w = Start_surface->w;
    int Dest_Surf_h = Start_surface->h;
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
    
    
    //-----------------homography------------------------
    
    //initialisation des matrices de coordonnees:
    float **old_coor = malloc(3*sizeof(float*));
    float **new_coor = malloc(3*sizeof(float*));

    for(int i=0; i<3; i++)
    {
        old_coor[i] = malloc(sizeof(float));
        new_coor[i] = malloc(sizeof(float));
    }


    for (int x = 0; x<Dest_Surf_w; x++)
    {
        for (int y = 0; y<Dest_Surf_h; y++)
        {

            int new_x = 0;
            int new_y = 0;

            old_coor[0][0]=x;
            old_coor[1][0]=y;
            old_coor[2][0]=1;
            
            mult_mat(H,old_coor,new_coor);

            new_x = (int)(new_coor[0][0]/new_coor[2][0]);
            new_y = (int)(new_coor[1][0]/new_coor[2][0]);

            printf("new_x = %d\n", new_x);
            printf("new_y = %d\n", new_y);

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
    

    Mat_Free(old_coor,3);
    Mat_Free(new_coor,3);
    
    return Dest_surface;
}




void mult_mat(float **mat1, float **mat2, float **res)
{
    //tailles de la matrice 1:
    size_t lines1 = sizeof(mat1)/sizeof(mat1[0][0]);
    size_t cols1 = sizeof(mat1[0])/sizeof(mat1[0][0]);

    //tailles de la matrice 2:
    size_t lines2 = sizeof(mat2)/sizeof(mat2[0][0]);
    size_t cols2 = sizeof(mat2[0])/sizeof(mat2[0][0]);

    //check si multiplication possible:
    if(cols1 != lines2)
        errx(1, "multiplication impossible, wrong size");
    
    //multiplication des matrices:
    for(size_t i=0; i<lines1; i++)
    {
        for(size_t j=0; j<cols2; j++)
        {
            res[i][j]=0;
            for(size_t k=0; k<cols1; k++)
            {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

}



void pi_mat(float x_src, float y_src, float x_dst, float y_dst, float **res)
{

    //ligne 1 de res:
    res[0][0] = x_src * (-1);
    res[0][1] = y_src * (-1);
    res[0][2] = -1;
    res[0][3] = 0;
    res[0][4] = 0;
    res[0][5] = 0;
    res[0][6] = x_src * x_dst;
    res[0][7] = y_src * x_dst;
    res[0][8] = x_dst;

    
    //ligne 2 de res:
    res[1][0] = 0;
    res[1][1] = 0;
    res[1][2] = 0;
    res[1][3] = x_src * (-1);
    res[1][4] = y_src * (-1);
    res[1][5] = -1;
    res[1][6] = x_src * y_dst;
    res[1][7] = y_src * y_dst;
    res[1][8] = y_dst;

}



void P_mat(float **p1_mat, float **p2_mat, float **p3_mat, float **p4_mat, float **p_mat)
{
 
    for(size_t i=0; i<8; i++)
    {
        for(size_t j=0; j<9; j++)
        {
            if(i>=0 && i<2)
                p_mat[i][j] = p1_mat[i%2][j];

            else if(i>=2 && i<4)
                p_mat[i][j] = p2_mat[i%2][j];

            else if(i>=4 && i<6)
                p_mat[i][j]= p3_mat[i%2][j];

            else if(i>=6 && i<8)
                p_mat[i][j] = p4_mat[i%2][j];
        }
    }

    for(size_t i = 0; i<8; i++)
    {
        p_mat[8][i] = 0;
    }
    p_mat[8][8]=1;

}



//pour inverser P
void mat_inv(size_t NbElement, float **mat)
{
    //on crée une matrice temporaire qui servira pour le pivot
	float **temp = malloc(NbElement*sizeof(float*));

    for(int i=0; i<NbElement; i++)
    {
        temp[i] = malloc(NbElement*sizeof(float));
    }


	for(size_t i=0; i<NbElement; i++)
    {	 	
	 	for(size_t j=0; j<NbElement; j++)
		{
		 	temp[i][i] = 1/mat[i][i];
		 	
            if(j!=i)
				temp[i][j] = (-mat[i][j])/mat[i][i];
	 		
            for(size_t k=0; k<NbElement; k++)
            {		    
				if(k!=i)
	 		 		temp[k][i] = mat[k][i]/mat[i][i];

				if(j!=i && k!=i)
			 		temp[k][j] = mat[k][j]-mat[i][j]*mat[k][i]/mat[i][i];
			}	
		}

        //on modifie la matrice finale avec la matrice temporaire:
		for(int i=0;i<NbElement;i++)
    	{
            for(int j=0;j<NbElement;j++)
            {
                mat[i][j]=temp[i][j];
            }
       }
	}

    //On free la matrice temporaire:
    Mat_Free(temp,NbElement);
}



void H_convert(float **H, float **res)
{
    
    res[0][0] = H[0][0];
    res[0][1] = H[1][0];
    res[0][2] = H[2][0];

    res[1][0] = H[3][0];
    res[1][1] = H[4][0];
    res[1][2] = H[5][0];

    res[2][0] = H[6][0];
    res[2][1] = H[7][0];
    res[2][2] = H[8][0];

}



int main(int argc, char** argv)
{
    int statut = EXIT_SUCCESS;   

    //if (argc != 6)
        //errx(EXIT_FAILURE, "not enough argument.");

    
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

    //argv[0]=./#executable
    //argv[1]="path file"

    //les coordonnées que Pierre me donne
    float *x_src = malloc(4*sizeof(float));
    x_src[0] = atoi(argv[0]);
    x_src[1] = atoi(argv[2]);
    x_src[2] = atoi(argv[4]);
    x_src[3] = atoi(argv[6]);

    float *y_src = malloc(4*sizeof(float));
    y_src[0] = atoi(argv[1]);
    y_src[1] = atoi(argv[3]);
    y_src[2] = atoi(argv[5]);
    y_src[3] = atoi(argv[7]);

    //les coordonnées destinations de la grille
    float *x_dst = malloc(4*sizeof(float));
    x_dst[0] = atoi(argv[8]);
    x_dst[1] = atoi(argv[10]);
    x_dst[2] = atoi(argv[12]);
    x_dst[3] = atoi(argv[14]);
    
    float *y_dst = malloc(4*sizeof(float));
    y_dst[0] = atoi(argv[9]);
    y_dst[1] = atoi(argv[11]);
    y_dst[2] = atoi(argv[13]);
    y_dst[3] = atoi(argv[15]);

    //on crée les matrices temporaires pi
    float **p1_mat = malloc(2*sizeof(float*));
    float **p2_mat = malloc(2*sizeof(float*));
    float **p3_mat = malloc(2*sizeof(float*));
    float **p4_mat = malloc(2*sizeof(float*));

    
    for(int i=0; i<2; i++) 
    {
        p1_mat[i] = malloc(9*sizeof(float));
        p2_mat[i] = malloc(9*sizeof(float));
        p3_mat[i] = malloc(9*sizeof(float));
        p4_mat[i] = malloc(9*sizeof(float));
    }
    
    //on crée les matrices temporaires p1, p2, p3, p4
    pi_mat(x_src[0], y_src[0], x_dst[0], y_dst[0], p1_mat);
    pi_mat(x_src[1], y_src[1], x_dst[1], y_dst[1], p2_mat);
    pi_mat(x_src[2], y_src[2], x_dst[2], y_dst[2], p3_mat);
    pi_mat(x_src[3], y_src[3], x_dst[3], y_dst[3], p4_mat);

    
    //On crée la matrice P finale
    float **p_mat = malloc(9*sizeof(float*));
    for(int i=0; i<9; i++)
    {
        p_mat[i] = malloc(9*sizeof(float));
    }

    
    //on la remplie avec p1, p2, p3 et p4
    P_mat(p1_mat, p2_mat, p3_mat, p4_mat, p_mat);
    

    //On free les 4 matrices p1, p2, p3, p4:
    Mat_Free(p1_mat,2);
    Mat_Free(p2_mat,2);
    Mat_Free(p3_mat,2);
    Mat_Free(p4_mat,2);


    //on calcule son inverse
    mat_inv(9, p_mat);

    
    //on la matrice de passage temporaire pour trouver H
    float **temp_mat = malloc(9*sizeof(float*));
    for(size_t i=0; i<9; i++)
    {
        temp_mat[i] = malloc(sizeof(float));
    }
    
    for(size_t i=0; i<8; i++)
    {
        temp_mat[i][0]=0;
    }
    temp_mat[8][0]=1;


    
    //on crée et calcule la matrice H
    float **H_mat = malloc(9*sizeof(float*));
    for(int i=0; i<9; i++)
    {
        H_mat[i] = malloc(sizeof(float));
    }
    mult_mat(p_mat, temp_mat, H_mat);
    

    
    //On Free p_mat et temp_mat:
    Mat_Free(p_mat,9);
    Mat_Free(temp_mat,9);

    
    //On converti H[9][1] en H[3][3]
    float **H = malloc(3*sizeof(float*));
    for(int i=0; i<3; i++)
    {
        H[i]=malloc(3*sizeof(float));
    }
    H_convert(H_mat,H);

    //On Free H_mat:
    Mat_Free(H_mat,9);


    //on calcule les nouveaux w et h pour l'homographie:
    w = (int)(x_dst[1] - x_dst[0]);
    h = (int)(y_dst[2] - y_dst[1]);

    //Je crée une nouvelle surface avec homography sur l'ancienne surface    
    SDL_Surface* Dest_surface = homography(Start_surface,H);

    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, Dest_surface);
    if (texture==NULL)
	    errx(EXIT_FAILURE, "%s", SDL_GetError());
    

    SDL_FreeSurface(Start_surface);
    SDL_FreeSurface(Dest_surface);

    event_loop(renderer, texture);

    Mat_Free(H,3);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

