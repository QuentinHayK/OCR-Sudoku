#include <stdio.h>

#include "matrix.h"

// Print the Matrix mat in the terminal
void print(Matrix* mat)
{
    int i = 0,
        j = 0;

    while (i < mat->h)
    {
        printf("%3d | ", mat->mat[i][j]);
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
    new->mat = malloc(height * sizeof(short*));
    
    for (int i = 0; i<height; i+=1)
        new->mat[i] = calloc(width, sizeof(short));

    return new; 
}

// Initialize a Matrix of height on width, with an array
Matrix* init1(short* arr, int height, int width)
{
    Matrix* output = malloc(sizeof(Matrix));
    output->h = height;
    output->w = width;
    output->mat = malloc(height * sizeof(short*));

    int i = 0;
    for (; i<height; i+=1)
        output->mat[i] = malloc(width * sizeof(short));

    for (i=0; i<height; i+=1)
        for (int j=0; j<width; j+=1)
            *(output->mat[i]+j) = arr[i*width +j];
    return output;
}

// Initialize a Matrix of height on width, with a matrix
Matrix* init2(short** mat, int height, int width)
{
    Matrix* output = malloc(sizeof(Matrix));
    output->h = height;
    output->w = width;
    output->mat = malloc(height * sizeof(short*));
    
    for (int i = 0; i<height; i+=1)
        output->mat[i] = malloc(width * sizeof(short));

    for (int i = 0; i<height; i+=1)
        for (int j = 0; j<width; j+=1)
            *(output->mat[i]+j) = mat[i][j];

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
void convolution(Matrix* mat, Matrix* kernel, int scale)
{
    Matrix* k = transpose(kernel);
    Matrix* tmp = init2(mat->mat, mat->h, mat->w);
    int size_ker = kernel->w * kernel->h;
    int pad_x = k->h / 2;
    int pad_y = k->w / 2;
    
    for (int i=0; i<mat->h; i+=1)
    {
        for (int j=0; j<mat->w; j+=1)
        {
            int count = 0;
            for (int index=0; index<size_ker; index+=1)
            {
                int indx = index / kernel->h,
                    indy = index % kernel->w;
                int x = i + indx - pad_x,
                    y = j + indy - pad_y;

                if ((x >= 0 && x < mat->h) && (y >= 0 && y < mat->w))
                    count += (k->mat[indx][indy] * tmp->mat[x][y]);

            }
            mat->mat[i][j] = count / scale;
        }
    }
    freeMat(tmp);
    freeMat(k);
}
