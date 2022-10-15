#include <stdio.h>
#include "functions.h"


void New_Matrix(int rows, int cols, double * res)
{
    int size = rows*cols;

    for (int i = 0; i < size; i++)
        res[i] = random_value()*2-1;
}

void Reset_Matrix(int rows, int cols, double * res)
{
    int size = rows*cols;

    for (int i = 0; i < size; i++)
        res[i] = 0;
}

void Print_Matrix(char s[], double m[], int rows, int cols)
{
    printf("%s = \n", s);
    for (int i = 0; i < rows; i++)
    {
	    for (int j = 0; j < cols; j++)
	    {
	        printf("%4g", m[i*cols+j]);
	    }
	    printf("\n");
    }
}

void Matrix_T(double m[], int rows, int cols, double * res)
{
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
           res[c*rows+r] = m[r*cols+c];
}

void Matrix_Add(double m1[], double m2[], int rows, int cols, double * res)
{
    for (int i = 0; i < rows*cols; i++)
        res[i] = m1[i] + m2[i];
}

void Matrix_Mult(double m1[], double m2[], int r1, int c1, int c2, double * res)
{
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            double acc = 0;
            for (int z = 0; z < c1; z++)
                acc += m1[i*c1+z] * m2[z*c2+j];
            res[i*c2+j] = acc;
        }
    }
}

void Matrix_Sigmoid(double m[], int rows, int cols)
{
    int size = rows*cols;

    int i = 0;
    while (i < size)
    {
        m[i] = Sigmoid(m[i]);
        i++;
    }
}
