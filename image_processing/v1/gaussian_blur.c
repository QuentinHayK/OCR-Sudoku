#include <math.h>

#include "matrix.h"

#define GAUSSIAN_SCALE 273

void gaussian_filter(Matrix* mat)
{
    short gauss_filter[25] = { 1, 4, 7, 4, 1,
        4, 16, 26, 16, 4,
        7, 26, 41, 26, 7,
        4, 16, 26, 16, 4,
        1, 4, 7, 4, 1};
    Matrix* kernel = init1(gauss_filter, 5, 5);
    convolution(mat, kernel, GAUSSIAN_SCALE);
}
