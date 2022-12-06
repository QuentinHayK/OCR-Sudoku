#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "data.h"
#include "user_inputs_functions.h"
#include "functions.h"

    /* Constants */
#define INPUTS_R 784 // 784
#define INPUTS_C 1

#define HIDDENS_R 20 // 12
#define HIDDENS_C 1

#define OUTPUTS_R 10 // 10
#define OUTPUTS_C 1

#define EPOCHS 500
#define DATA_LENGTH 400

#define DELTA 0.02

#define XOR_DATA "XOR.csv"
#define DIGITS_DATA "TMNIST_Data.csv"
#define SELECTED_DATA DIGITS_DATA

#define SAVE "save"

    struct Neural_Network
    {
	    double inputs[INPUTS_R * INPUTS_C];

	    double w1[INPUTS_R * HIDDENS_R];
	    double w1_derivative[INPUTS_R * HIDDENS_R];
	    double b1[HIDDENS_R];
	    double b1_derivative[HIDDENS_R];
	    double hiddens[HIDDENS_R * HIDDENS_C];

	    double w2[OUTPUTS_R * HIDDENS_R];
	    double w2_derivative[OUTPUTS_R * HIDDENS_R];
	    double b2[OUTPUTS_R];
	    double b2_derivative[OUTPUTS_R];
	    double outputs[OUTPUTS_R * OUTPUTS_C];
    };

    /* Save Manager */

    void Export_NN(struct Neural_Network * NN, char file[])
    {
	    FILE *out = fopen(file, "w");

	    for (int i = 0; i < INPUTS_R * HIDDENS_R; i++)
		    fprintf(out, "%f\n", NN->w1[i]);

	    for (int i = 0; i < HIDDENS_R; i++)
		    fprintf(out, "%f\n", NN->b1[i]);

	    for (int i = 0; i < OUTPUTS_R * HIDDENS_R; i++)
		    fprintf(out, "%f\n", NN->w2[i]);

	    for (int i = 0; i < OUTPUTS_R; i++)
		    fprintf(out, "%f\n", NN->b2[i]);


	    fclose(out);
    }

    void Import_NN(struct Neural_Network * NN, char file[])
    {
	    FILE * in = fopen(file, "r");

	    char line[1000];
	    char *rest;

	    for (int i = 0; i < INPUTS_R * HIDDENS_R; i++)
	    {
		    fgets(line, 1000, in);
		    NN->w1[i] = strtod(line, &rest);
	    }

	    for (int i = 0; i < HIDDENS_R; i++)
	    {
		    fgets(line, 1000, in);
		    NN->b1[i] = strtod(line, &rest);
	    }

	    for (int i = 0; i < OUTPUTS_R * HIDDENS_R; i++)
	    {
		    fgets(line, 1000, in);
		    NN->w2[i] = strtod(line, &rest);
	    }

	    for (int i = 0; i < OUTPUTS_R; i++)
	    {
		    fgets(line, 1000, in);
		    NN->b2[i] = strtod(line, &rest);
	    }

	    fclose(in);
    }


    /* --------- FUNCTIONS --------- */

    int Max_label_from_doubles(double *output, int len)
    {
	    double max = output[0];
	    int max_i = 0;

	    for (int i = 1; i < len; i++)
	    {
		    if (output[i] > max)
		    {
			    max = output[i];
			    max_i = i;
		    }
	    }

	    return max_i;
    }

    double Node_Cost(double output, double desired_output) {
	    double error = output - desired_output;
	    return error * error;
    }

    double Node_Cost_Derivative(double output, double desired_output) {
	    return 2 * (output - desired_output);
    }

    void Get_Layers_Outputs(struct Neural_Network * NN)
    {
	    /* Layer 1 */
	    Mult_Matrix(NN->w1, NN->inputs, HIDDENS_R, INPUTS_R, INPUTS_C, NN->hiddens);
	    Add_Matrix(NN->hiddens, NN->b1, HIDDENS_R, HIDDENS_C, NN->hiddens);
	    Matrix_Sigmoid(NN->hiddens, HIDDENS_R, HIDDENS_C);

	    /* Layer 2 */
	    Mult_Matrix(NN->w2, NN->hiddens, OUTPUTS_R, HIDDENS_R, HIDDENS_C, NN->outputs);
	Add_Matrix(NN->outputs, NN->b2, OUTPUTS_R, OUTPUTS_C, NN->outputs);
	Matrix_Sigmoid(NN->outputs, OUTPUTS_R, OUTPUTS_C);
    }

    double Calculate_Cost(struct Neural_Network * NN, struct Data data)
    {
	    double cost = 0;
	    
	    for (int i = 0; i < INPUTS_R; i++)
	    {
		    NN->inputs[i] = data.input[i];
	    }

	    Get_Layers_Outputs(NN);

	    for (int i = 0; i < OUTPUTS_R; i++)
	    {
		    cost += Node_Cost(NN->outputs[i], data.expected_output[i]);
	    }

	    return cost;
    }

    double Calculate_Total_Cost(struct Neural_Network NN, struct DataSet data_set)
    {
	    double total_cost = 0;

	    for (int i = 0; i < data_set.length; i++)
	    {
		    total_cost += Calculate_Cost(&NN, data_set.data_set[i]);
	    }

	    return total_cost;
    }

    void Learning(struct Neural_Network * NN, struct DataSet data)
    {
	    for (int epoch = 1; epoch <= EPOCHS; epoch++)
	{
	    Reset_Matrix(INPUTS_R, HIDDENS_R, NN->w1_derivative);
	    Reset_Matrix(HIDDENS_R, 1, NN->b1_derivative);     
	    Reset_Matrix(OUTPUTS_R, HIDDENS_R, NN->w2_derivative);
	    Reset_Matrix(OUTPUTS_R, 1, NN->b2_derivative);

	    double delta = DELTA;
        double original_cost = Calculate_Cost(NN, data.data_set[epoch%data.length]); // Modified from Total_Cost

        for (int j = 0; j < INPUTS_R * HIDDENS_R; j++)
        {
            NN->w1[j] += delta;
            double cost = Calculate_Cost(NN, data.data_set[epoch%data.length]) - original_cost;
            NN->w1_derivative[j] += cost;
            NN->w1[j] -= delta;
        }

        for (int j = 0; j < HIDDENS_R; j++)
        {
            NN->b1[j] += delta;
            double cost = Calculate_Cost(NN, data.data_set[epoch%data.length]) - original_cost;
            NN->b1_derivative[j] += cost;
            NN->b1[j] -= delta;
        }

        for (int j = 0; j < OUTPUTS_R * HIDDENS_R; j++)
        {
            NN->w2[j] += delta;
            double cost = Calculate_Cost(NN, data.data_set[epoch%data.length]) - original_cost;
            NN->w2_derivative[j] += cost;
            NN->w2[j] -= delta;
        }

        for (int j = 0; j < OUTPUTS_R; j++)
        {
            NN->b2[j] += delta;
            double cost = Calculate_Cost(NN, data.data_set[epoch%data.length]) - original_cost;
            NN->b2_derivative[j] += cost;
            NN->b2[j] -= delta;
        }

        for (int j = 0; j < INPUTS_R * HIDDENS_R; j++)
           NN->w1[j] -= NN->w1_derivative[j];

        for (int j = 0; j < HIDDENS_R; j++)
            NN->b1[j] -= NN->b1_derivative[j];

        for (int j = 0; j < OUTPUTS_R * HIDDENS_R; j++)
            NN->w2[j] -= NN->w2_derivative[j];

        for (int j = 0; j < OUTPUTS_R; j++)
            NN->b2[j] -= NN->b2_derivative[j];
     	
		// Print current cost
		if ((epoch > 0 && epoch % 1 == 0) || epoch == 1)
		{
			//printf("\b\b\b\b\b\b\b\b");
			printf("\n[Epoch : %d] Cost : ", epoch);
		}
		else if (epoch > 0)
			printf("\b\b\b\b\b\b\b\b");
		else
			printf("\n[Epoch : %d] Cost : ", epoch);
		printf("%8f", Calculate_Total_Cost(*NN, data));	
	}
	printf("\n\n");
}

void red()
{
  printf("\033[0;31m");
}

void green()
{
  printf("\033[0;32m");
}

void reset_color()
{
  printf("\033[0m");
}

int main(void)
{
	struct DataSet data;
	data.length = DATA_LENGTH;

	data.data_set = malloc(sizeof(struct Data) * data.length);
	
	Get_CSV_Data_Image(SELECTED_DATA, &data);


	struct Neural_Network NN;
	
	New_Matrix(HIDDENS_R, INPUTS_R, (&NN)->w1);
	New_Matrix(OUTPUTS_R, HIDDENS_R, (&NN)->w2);


	int file_exists = Is_File_Exists(SAVE);
	if (file_exists == 1)
	{
		Import_NN(&NN, SAVE);
	}

	// Train our Neural Network :
	if (file_exists == 0)
	{
		Learning(&NN, data);
		Export_NN(&NN, SAVE);
	}

	// Print results
	printf("------------ Results ------------\n\n");

	int score = 0;

	for (int j = 0; j < data.length; j++)
	{
		for (int i = 0; i < INPUTS_R; i++)
		{
			(&NN)->inputs[i] = data.data_set[j].input[i];
			//printf("data : %f\n", data.data_set[j].input[i]);
		}
		
		Get_Layers_Outputs(&NN);

		//Print_Matrix("Input", NN.inputs, INPUTS_R, INPUTS_C);
		int output_label = Max_label_from_doubles(NN.outputs, OUTPUTS_R * OUTPUTS_C);
		int expected_output_label = data.data_set[j].label[0] - '0';

		if (output_label == expected_output_label)
		{
		    green();
		    score++;
		}
		else
			red();
		printf("Expected : %d => Output : %d\n", expected_output_label, output_label);
		reset_color();
		//Print_Matrix("Output", NN.outputs, OUTPUTS_R, OUTPUTS_C);
	}

	printf("\n%d/100\n", (int)((double)score / (double)data.length * 100));

	printf("\n---------------------------------\n");
	
	
	free(data.data_set);
	
	return 0;
}
