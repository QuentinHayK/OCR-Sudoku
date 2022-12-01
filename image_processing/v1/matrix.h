#ifndef MATRIX
#define MATRIX

typedef struct {
    int w, h;
    double** mat;
} Matrix;

void print(Matrix* mat);
Matrix* init1(double* mat, int height, int width);
Matrix* init2(double** mat, int height, int width);
void freeMat(Matrix* mat);
Matrix* transpose(Matrix* mat);
void convolution(Matrix* mat, Matrix* kernel, Matrix* res);

#endif
