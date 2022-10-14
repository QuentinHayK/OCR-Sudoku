#include <stdio.h>
#include "usefull/matrix.h"


#define INPUTS_R 4
#define INPUTS_C 1

#define HIDDENS_R 4
#define HIDDENS_C 1

#define OUTPUTS_R 3
#define OUTPUTS_C 1


int main()
{
    double inputs[INPUTS_C * INPUTS_R] = {0.1, 0.5, 0.8, 0.2};
    
    double weights1[INPUTS_R * HIDDENS_R];
    New_Matrix(4, 4, weights1);
    double b1[4];
    New_Matrix(4, 1, b1);

    double hiddens[HIDDENS_R * HIDDENS_C] = {0, 0, 0, 0};
    Matrix_Mult(weights1, inputs, HIDDENS_R, INPUTS_R, INPUTS_C, hiddens);
    Matrix_Add(hiddens, b1, HIDDENS_R, HIDDENS_C, hiddens);

    double weights2[OUTPUTS_R * HIDDENS_R];
    New_Matrix(OUTPUTS_R, HIDDENS_R, weights2);
    double b2[OUTPUTS_R];
    New_Matrix(OUTPUTS_R, OUTPUTS_C, b2);
    
    double outputs[OUTPUTS_R * OUTPUTS_C] = {0, 0, 0};
    Matrix_Mult(weights2, hiddens, OUTPUTS_R, HIDDENS_R, HIDDENS_C, outputs);
    Matrix_Add(outputs, b2, OUTPUTS_R, OUTPUTS_C, outputs);



    Print_Matrix("Inputs", inputs, INPUTS_R, INPUTS_C);
    Print_Matrix("Hiddens", hiddens, HIDDENS_R, HIDDENS_C);
    Print_Matrix("Outputs", outputs, OUTPUTS_R, OUTPUTS_C);

    return 0;
}

