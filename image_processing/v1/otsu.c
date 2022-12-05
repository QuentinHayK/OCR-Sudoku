#include "matrxi.h"

int* hist(Matrix* img)
{
    int height = img->h,
        width = img->w;
    int histo[256] = {0};
    
    for (int i=0; i<height; i+=1)
        for (int j=0; i<width; j+=1)
            histo[img->mat[i][j]] += 1;

    return histo;
}


