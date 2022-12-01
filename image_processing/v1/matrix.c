#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

void print(Matrix* mat)
{
    int i = 0,
        j = 0;

    while (i < mat->h)
    {
        printf("%3.2f | ", mat->mat[i][j]);
        j += 1;

        if (j == mat->w)
        {
            i += 1;
            j = 0;
            printf("\n");
        }
    }
    printf("\n");
}

Matrix* init1(double* mat, int height, int width)
{
    Matrix* output = malloc(sizeof(Matrix));
    output->h = height;
    output->w = width;
    output->mat = malloc(height * sizeof(double*));
    
    int i = 0;
    for (; i<height; i+=1)
        output->mat[i] = malloc(width * sizeof(double));

    for (i=0; i<height*width; i+=1)
        output->mat[i/height][i%width] = mat[i];

    return output;
}

Matrix* init2(double** mat, int height, int width)
{
    Matrix* output = malloc(sizeof(Matrix));
    output->h = height;
    output->w = width;
    output->mat = malloc(height * sizeof(double*));
    
    int i = 0;
    for (; i<height; i+=1)
        output->mat[i] = malloc(width * sizeof(double));

    for (i=0; i<height*width; i+=1)
        output->mat[i/height][i%width] = mat[i/height][i%width];

    return output;
}

void freeMat(Matrix* mat)
{
    for (int i = 0; i<mat->h; i+=1)
        free(mat->mat[i]);
    
    free(mat->mat);
    free(mat);
}


Matrix* transpose(Matrix* mat)
{
    int i = 0,
        j = 0,
        height = mat->h,
        width = mat->w;
    Matrix* output = init2(mat->mat, height, width);

    while (i < height/2 || j < width/2)
    {
        output->mat[height-1-i][width-1-j] = mat->mat[i][j];
        output->mat[i][j] = mat->mat[height-1-i][width-1-j];
        
        j += 1;
        if (j == mat->w)
        {
            i += 1;
            j = 0;
        }
    }

    return output;
}

void convolution(Matrix* mat, Matrix* kernel, Matrix* res)
{
    int size_ker = kernel->w * kernel->h;
    for (int i=0, j=0; i<mat->h;)
    {
        printf("\n");
        double count = 0;
        for (int index=0; index<size_ker; index+=1)
        {
            int indx = index / kernel->h,
                indy = index % kernel->w;
            int x = i + indx - 1,
                y = j + indy - 1;
            
            printf("indx:%d // indy:%d // x:%d // y:%d\n", indx, indy, x, y);
            if ((x >= 0 && x < mat->h) && (y >= 0 && y < mat->w))
                count += kernel->mat[indx][indy] * mat->mat[x][y];

            printf("count:%d", count);
        }
        res->mat[i][j] = count;

        j += 1;
        if (j == mat->w)
        {
            i += 1;
            j = 0;
        }
    }
}
