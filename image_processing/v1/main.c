#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(void)
{
    double mmat[16] = {2, 1, 3, 0,
        1, 1, 0, 5,
        3, 3, 1, 0,
        2, 0, 0, 2};

    Matrix* mat = init1(mmat, 4, 4);
    print(mat);

    double nmat[16] = {0};
    Matrix* res = init1(nmat, 4, 4);
    
    double kmat[9] = {1, 0, 2,
        2, 1, 0,
        1, 0, 3};
    Matrix* kernel = init1(kmat, 3, 3);
    print(kernel);

    convolution(mat, kernel, res);
    print(res);
    
    freeMat(kernel);
    freeMat(mat);
    freeMat(res);
    return 0;
}
