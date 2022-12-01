#ifndef MATRIX
#define MATRIX

typedef struct {
    int w, h;
    unsigned char** mat;
} Matrix;

void print(Matrix* mat);
Matrix* new_mat(int height, int width);
Matrix* init1(unsigned char* mat, int height, int width);
Matrix* init2(unsigned char** mat, int height, int width);
void freeMat(Matrix* mat);
Matrix* transpose(Matrix* mat);
void convolution(Matrix* mat, Matrix* kernel, Matrix* res);

#endif
