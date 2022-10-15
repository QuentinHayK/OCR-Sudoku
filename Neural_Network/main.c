#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdbool.h>
#include "usefull/matrix.h"
#include "data.h"
#include "usefull/user_inputs_functions.h"
#include "usefull/functions.h"


/* Constants */
#define INPUTS_R 784
#define INPUTS_C 1

#define HIDDENS_R 16
#define HIDDENS_C 1

#define OUTPUTS_R 10
#define OUTPUTS_C 1
/* --------- */


void Get_Layers_Outputs(double * inputs, double * hiddens, double * outputs, double * weights1, double * weights2, double * b1, double * b2)
{
    Reset_Matrix(HIDDENS_R, HIDDENS_C, hiddens);
    Reset_Matrix(OUTPUTS_R, OUTPUTS_C, outputs);

    /* Layer 1 */
    Matrix_Mult(weights1, inputs, HIDDENS_R, INPUTS_R, INPUTS_C, hiddens);
    Matrix_Add(hiddens, b1, HIDDENS_R, HIDDENS_C, hiddens);
    //Matrix_Sigmoid(hiddens);    

    /* Layer 2 */
    Matrix_Mult(weights2, hiddens, OUTPUTS_R, HIDDENS_R, HIDDENS_C, outputs);
    Matrix_Add(outputs, b2, OUTPUTS_R, OUTPUTS_C, outputs);
    //Matrix_Sigmoid(outputs);
}

double Calculate_Cost(struct DataSet data, int i, double * inputs, double * hiddens, double * outputs, double * weights1, double * weights2, double * b1, double * b2)
{
    /* Get ouputs from layers  */
    Get_Layers_Outputs(inputs, hiddens, outputs, weights1, weights2, b1, b2);
    
    /*
    Print_Matrix("Inputs", inputs, INPUTS_R, INPUTS_C);
    printf("\n");
    Print_Matrix("Hiddens", hiddens, HIDDENS_R, HIDDENS_C);
    printf("\n");
    Print_Matrix("Outputs", outputs, OUTPUTS_R, OUTPUTS_C);
    */
    
    /* Cost function */
    double cost = 0;
    for (int j = 0; j < 10; j++)
    {
        cost += Node_Cost(outputs[j], data.data_set[i].expected_output[j]);
    }
    return cost;
}

double Calculate_TotalCost(struct DataSet data, double * inputs, double * hiddens, double * outputs, double * weights1, double * weights2, double * b1, double * b2)
{
    double total_cost = 0;
    int len = data.length;
    for (int i = 0; i < len; i++)
    {
        inputs = data.data_set[i].input;
        total_cost += Calculate_Cost(data, i, inputs, hiddens, outputs, weights1, weights2, b1, b2);
    }

    return total_cost;
}


int main(void)
{
    struct DataSet data;
    data.length = 200;

    /* Get Dataset from a file */
    Get_CSV_Data_Image("data/TMNIST_Data.csv", &data);

    /*
    for (int i = 0; i < 20; i++)
        Display_Digit(data.data_set[i].input);
    */



    /* Hardcoded Neural Network */
    /* Layer 1 */
    double * inputs = data.data_set[0].input;
    double weights1[INPUTS_R * HIDDENS_R];
        
    New_Matrix(HIDDENS_R, INPUTS_R, weights1);

    double b1[HIDDENS_R];
        
    New_Matrix(HIDDENS_R, HIDDENS_C, b1);
    /* ------- */

    /* Layer 2 */
    double hiddens[HIDDENS_R * HIDDENS_C];
    double weights2[OUTPUTS_R * HIDDENS_R];
    
    New_Matrix(OUTPUTS_R, HIDDENS_R, weights2);
        
    double b2[OUTPUTS_R];
    
    New_Matrix(OUTPUTS_R, OUTPUTS_C, b2);
    /* ------  */
    
    double outputs[OUTPUTS_R * OUTPUTS_C];


    /* for each weights and biases, calcul cost derivative */
    double w1_derivative[INPUTS_R * HIDDENS_R];
    double b1_derivative[HIDDENS_R];
    double w2_derivative[OUTPUTS_R * HIDDENS_R];
    double b2_derivative[OUTPUTS_R];
  
    /*
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < INPUTS_R * HIDDENS_R; j++)
        {
            weights1[j] += 0.1;
            Get_Layers_Outputs(inputs, hiddens, outputs, weights1, weights2, b1, b2);
            double cost = 0;
            for (int k = 0; k < 10; k++)
                cost += Node_Cost_Derivative(outputs[k], data.data_set[i].expected_output[k]);
            w1_derivative[j] += cost;
            weights1[j] -= 0.1;
            printf("[%u] : %f\n", j, weights1[j]);
        }
    }
    */
    

    double total_cost = Calculate_TotalCost(data, inputs, hiddens, outputs, weights1, weights2, b1, b2);
    printf("total cost : %f\n", total_cost);
    
    Print_Matrix("w1", weights1, INPUTS_R, HIDDENS_R);
    
    return 0;
}

