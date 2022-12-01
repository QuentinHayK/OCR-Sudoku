#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

// Print the Matrix mat in the terminal
void print(Matrix* mat)
{
    int i = 0,
        j = 0;

    while (i < mat->h)
    {
        printf("%3u | ", mat->mat[i][j]);
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

// Create Matrix of size of height by width, full of 0
Matrix* new_mat(int height, int width)
{
    Matrix* new = malloc(sizeof(Matrix));
    new->h = height;
    new->w = width;
    new->mat = malloc(height * sizeof(unsigned char*));
    
    for (int i = 0; i<height; i+=1)
        new->mat[i] = calloc(width, sizeof(unsigned char));

    return new; 
}

// Initialize a Matrix of height on width, with an array
Matrix* init1(unsigned char* mat, int height, int width)
{
    Matrix* output = malloc(sizeof(Matrix));
    output->h = height;
    output->w = width;
    output->mat = malloc(height * sizeof(unsigned char*));
    
    int i = 0;
    for (; i<height; i+=1)
        output->mat[i] = malloc(width * sizeof(unsigned char));

    for (i=0; i<height*width; i+=1)
        output->mat[i/height][i%width] = mat[i];

    return output;
}

// Initialize a Matrix of height on width, with a matrix
Matrix* init2(unsigned char** mat, int height, int width)
{
    Matrix* output = malloc(sizeof(Matrix));
    output->h = height;
    output->w = width;
    output->mat = malloc(height * sizeof(unsigned char*));
    
    int i = 0;
    for (; i<height; i+=1)
        output->mat[i] = malloc(width * sizeof(unsigned char));

    for (i=0; i<height*width; i+=1)
        output->mat[i/height][i%width] = mat[i/height][i%width];

    return output;
}

// Free the Matrix mat
void freeMat(Matrix* mat)
{
    for (int i = 0; i<mat->h; i+=1)
        free(mat->mat[i]);
    
    free(mat->mat);
    free(mat);
}

// Returns the transposition of the Matrix mat
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

// Do the convolution operation mat * kernel in the Natrix res
void convolution(Matrix* mat, Matrix* kernel, Matrix* res)
{
    Matrix* k = transpose(kernel);
    int size_ker = kernel->w * kernel->h;
    for (int i=0, j=0; i<mat->h;)
    {
        int count = 0;
        for (int index=0; index<size_ker; index+=1)
        {
            int indx = index / kernel->h,
                indy = index % kernel->w;
            int x = i + indx - kernel->h/2,
                y = j + indy - kernel->w/2;
            
            if ((x >= 0 && x < mat->h) && (y >= 0 && y < mat->w))
                count += (k->mat[indx][indy] * mat->mat[x][y]);

        }
        res->mat[i][j] = count;

        j += 1;
        if (j == mat->w)
        {
            i += 1;
            j = 0;
        }
    }
    freeMat(k);
}
