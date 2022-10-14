#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdbool.h>
#include "usefull/matrix.h"
#include "data.h"
#include "usefull/user_inputs_functions.h"


/* Constants */
#define INPUTS_R 784
#define INPUTS_C 1

#define HIDDENS_R 16
#define HIDDENS_C 1

#define OUTPUTS_R 10
#define OUTPUTS_C 1
/* --------- */


int main(void)
{
    struct DataSet data;
    data.length = 2;

    /* Get Dataset from a folder */
    for (int i = 0; i < data.length; i++)
    {
        Get_CSV_Data_Image("data/TMNIST_Data.csv", &data);
    }

    Display_Digit(data.data_set[0].input);

    /* Handwrited Neural Network */
    /* Layer 1 */
    double inputs[INPUTS_C * INPUTS_R];
    
    double weights1[INPUTS_R * HIDDENS_R];
    New_Matrix(HIDDENS_R, INPUTS_R, weights1);
    double b1[HIDDENS_R];
    New_Matrix(HIDDENS_R, HIDDENS_C, b1);
    /* ------- */

    /* Layer 2 */
    double hiddens[HIDDENS_R * HIDDENS_C] = {0, 0, 0, 0};
    double weights2[OUTPUTS_R * HIDDENS_R];
    New_Matrix(OUTPUTS_R, HIDDENS_R, weights2);
    double b2[OUTPUTS_R];
    New_Matrix(OUTPUTS_R, OUTPUTS_C, b2);
    
    double outputs[OUTPUTS_R * OUTPUTS_C] = {0, 0, 0};
    /* ------- */
    
    /* Get ouputs from layers  */
    /* Layer 1 */
    Matrix_Mult(weights1, inputs, HIDDENS_R, INPUTS_R, INPUTS_C, hiddens);
    Matrix_Add(hiddens, b1, HIDDENS_R, HIDDENS_C, hiddens);
    
    /* Layer 2 */
    Matrix_Mult(weights2, hiddens, OUTPUTS_R, HIDDENS_R, HIDDENS_C, outputs);
    Matrix_Add(outputs, b2, OUTPUTS_R, OUTPUTS_C, outputs);


    Print_Matrix("Inputs", inputs, INPUTS_R, INPUTS_C);
    printf("\n");
    Print_Matrix("Hiddens", hiddens, HIDDENS_R, HIDDENS_C);
    printf("\n");
    Print_Matrix("Outputs", outputs, OUTPUTS_R, OUTPUTS_C);
    /* --------------------------- */

    return 0;
}

