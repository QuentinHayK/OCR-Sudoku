#include <math.h>
#include <stdio.h>

#include "matrix.h"

void grad(Matrix* mat, Matrix** gradients)
{
    short filter_y[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    short filter_x[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    Matrix* gradx = init2(mat->mat, mat->h, mat->w);
    Matrix* grady = init2(mat->mat, mat->h, mat->w);
    gradients[0] = gradx;
    gradients[1] = grady;

    Matrix* sobel_x = init1(filter_x, 3, 3);
    print(sobel_x);
    Matrix* sobel_y = init1(filter_y, 3, 3);
    print(sobel_y);

    convolution(gradients[0], sobel_x, 1);
    convolution(gradients[1], sobel_y, 1);
}

Matrix** gradient_magnitude(Matrix* mat)
{
    int height = mat->h;
    int width = mat->w;
    Matrix** gradients = malloc(2 * sizeof(Matrix*));
    grad(mat, gradients);

    for (int i=0; i<height; i+=1)
    {
        for (int j=0; j<width; j+=1)
        {
            short gx = gradients[0]->mat[i][j];
            short gy = gradients[1]->mat[i][j];
            int g = gx*gx + gy*gy;
            double d = sqrt(g);
            mat->mat[i][j] = d;
        }
    }

    return gradients;
}

Matrix* compare_neighbours(Matrix* mat, Matrix** gradi)
{
}
