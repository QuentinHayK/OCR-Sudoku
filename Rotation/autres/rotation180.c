void rotation (SDL_Surface* Start_surface, SDL_Surface* Dest_surface, int degre)          
{
    Uint32* Spixels = Start_surface->pixels;
    Uint32* Dpixels = Dest_surface->pixels;

    Dest_surface->w = Start_surface->h;
    Dest_surface->h = Start_surface->w;
    
    
    int Slock = SDL_LockSurface(Start_surface);
    int Dlock = SDL_LockSurface(Dest_surface);

    if (Slock!=0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
     
    if (Dlock!=0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
 
    //Pixel[x][y]=Pixel[x * w + y]

    //trouver comment positionner les pixels pour avoir l'angle voulu
    for (int x = 0; x<Start_surface->w; x++)
    {
        for (int y = 0; y<Start_surface->h; y++)
        {
            Dpixels[x * w + (Start_surface->h-1-y)] = Spixels[x * Start_surface->w + y];
        }
    }
    //pixels = surface->pixels;

    SDL_UnlockSurface(Start_surface);
    SDL_UnlockSurface(Dest_surface);
}



