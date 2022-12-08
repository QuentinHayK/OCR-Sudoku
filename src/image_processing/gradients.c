#include <math.h>

#include "matrix.h"

#define PI 3.14159265
#define RATIO (180/PI)

// Determinate if a pixel is an edge using direction
int is_edge(Matrix* mag, short degree, int i, int j)
{
    short gmag = mag->mat[i][j];
    int edge = 0;

    if (degree <= 22.5 || degree >= 157.5)
    {
        if (j+1 < mag->w)
            edge = gmag > mag->mat[i][j+1];

        if (j-1 > 0)
            edge = gmag > mag->mat[i][j-1];
    }
    else if (degree <= 67.5)
    {
        if (i-1 > 0 && j-1 > 0)
            edge = gmag > mag->mat[i-1][j-1];

        if (i+1 < mag->h && j+1 < mag->w)
            edge = gmag > mag->mat[i+1][j+1];
    }
    else if (degree <= 112.5)
    {
        if (i-1 > 0)
            edge = gmag > mag->mat[i-1][j];

        if (i+1 < mag->h)
            edge = gmag > mag->mat[i+1][j];
    }
    else
    {
        if (i-1 > 0 && j+1 < mag->w)
            edge = gmag > mag->mat[i-1][j+1];

        if (i+1 < mag->h && j-1 > 0)
            edge = gmag > mag->mat[i+1][j-1];
    }

    return edge;
}

// Calculation of gradient in x and y
Matrix* grad(Matrix* mat)
{
    int height = mat->h,
        width = mat->w;

    // Sobel filter in axis y
    short filter_y[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    Matrix* sobel_y = init1(filter_y, 3, 3);
    
    // Sobel filter in axis x
    short filter_x[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    Matrix* sobel_x = init1(filter_x, 3, 3);

    // Matrix for save the result of convolution
    Matrix* gradx = init2(mat->mat, height, width);
    Matrix* grady = init2(mat->mat, height, width);

    convolution(gradx, sobel_x, 1);
    convolution(grady, sobel_y, 1);

    // Matrix for save the result of magnitude and degree
    Matrix* mag = new_mat(height, width);
    for (int i=0; i<height; i+=1)
        for (int j=0; j<width; j+=1)
	{
            short gx = gradx->mat[i][j];
            short gy = grady->mat[i][j];
            double g = sqrt(gx*gx + gy*gy);

            mag->mat[i][j] = g > 255 ? 255 : g;
	}

    Matrix* nm = new_mat(height, width);
    for (int i=0; i<height; i+=1)
        for (int j=0; j<width; j+=1)
        {
            short d = atan2(grady->mat[i][j], gradx->mat[i][j]) * 180/PI;
            if (!is_edge(mag, d < 0 ? d+180 : d, i, j))
		nm->mat[i][j] = mag->mat[i][j];
	    else
		nm->mat[i][j] = 0;

        }

    freeMat(gradx);
    freeMat(grady);

    return nm;
}
