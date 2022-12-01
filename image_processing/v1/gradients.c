#include <math.h>

#include "matrix.h"

Matrix** grandient_magnitude(Matrix* mat)
{
    int row = 0,
        col = 0;

    while (row < mat->h)
    {
        Matrix** gradients = grad(mat);
        unsigned char gx = gradients[0]->mat[row][col];
        unsigned char gy = gradients[1]->mat[row][col]; 
        double d = sqrt(gx*gx + gy*gy );
        mat->mat[row][col] = d   ;

        col += 1;
        if (col == mat->w)
        {
            row += 1;
            col = 0;
        }
    }
    return gradients;
}

Matrix** grad(Matrix* mat)
{
    unsigned char* filter = { -1, 0, 1 };
    Matrix* gradx = new_mat(mat->h, mat->w),
        grady = new_mat(mat->h, mat->w);
    Matrix** gradients = {gradx, grady};

    Matrix* filter_x = init1(filter, 1, 3);
    Matrix* filter_y = init1(filter, 3, 1);

    convolution(mat, filter_x, gradx);
    convolution(mat, filter_y, grady);

    return gradients;
}
