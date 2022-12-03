#ifndef MATRIX
#define MATRIX

#include <stdlib.h>

typedef struct {
    int w, h;
    short** mat;
} Matrix;

void print(Matrix* mat);
Matrix* new_mat(int height, int width);
Matrix* init1(short* arr, int height, int width);
Matrix* init2(short** mat, int height, int width);
void freeMat(Matrix* mat);
Matrix* transpose(Matrix* mat);
void convolution(Matrix* mat, Matrix* kernel, int scale);

#endif
