#pragma once

void New_Matrix(int rows, int cols, double * res);
void Reset_Matrix(int rows, int cols, double * res);
void Print_Matrix(char s[], double m[], int rows, int cols); 
void Matrix_T(double m[], int rows, int cols, double * res);
void Matrix_Add(double m1[], double m2[], int rows, int cols, double * res);
void Matrix_Mult(double m1[], double m2[], int r1, int c1, int c2, double * res);
void Matrix_Sigmoid(double m[]);

