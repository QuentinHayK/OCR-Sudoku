#include <stdio.h>
#include <stdlib.h>
#include "layer.h"
#include "nn.h"
#include "functions.h"


void Init_Neural_Network(struct NeuralNetwork * NN, int num_layers, int layers_size[]) 
{
	for (int i = 0; i < num_layers; i++) 
    {
		Init_Layer(&NN->layers[i], layers_size[i], layers_size[i+1]);
		NN->layers_size[i] = layers_size[i];
	}
	
	NN->num_layers = num_layers;
}


double Cost_Data_NN(struct NeuralNetwork * NN, struct Data data) 
{	
	double *res = Calculate_Outputs_NN(NN, data.input);
	
	double cost = 0;
	
	
	for (int i = 0; i < NN->layers_size[NN->num_layers-2]; i++) 
    {
		cost += Node_Cost(res[i], data.expected_output[i]);
	}
	
	//printf("%f | %f return %f | %f instead %f |%f\n", data.input[0], data.input[1], res[0], res[1], data.expected_output[0], data.expected_output[1]);
	
	return cost;
}


double *Calculate_Outputs_NN(struct NeuralNetwork * NN, double input[]) 
{
	Calculate_Outputs_Layer(&NN->layers[0], input);

	for (int i = 1; i < NN->num_layers-1; i++) 
    {
		Calculate_Outputs_Layer(&NN->layers[i], NN->layers[i-1].outputs);
	}

	return NN->layers[NN->num_layers-2].outputs;
}


double Cost_DataSet_NN(struct NeuralNetwork * NN, struct DataSet data) 
{
	double total_cost = 0;
	
	for (int i = 0; i < data.length; i++) 
    {
		total_cost += Cost_Data_NN(NN, data.data_set[i]);
	}
	
	return total_cost;
}


void Apply_All_Gradients_NN(struct NeuralNetwork *NN, double learning_rate) {
	for (int i = 0; i < NN->num_layers; i++) {
		Apply_Gradients_Layer(&NN->layers[i], learning_rate);
	}
}


void Gradient_Descent_NN(struct NeuralNetwork * NN, struct DataSet training_data, double learning_rate)
{
    double h = 0.01;
    double original_cost = Cost_DataSet_NN(NN, training_data);

    for (int l = 0; l < NN->num_layers; l++)
    {
        for (int i = 0; i < NN->layers_size[0]; i++)
        {
            for (int j = 0; j < NN->layers_size[NN->num_layers-1]; j++)
            {
                NN->layers[l].weights[i * NN->layers_size[NN->num_layers-1] + j] += h;
                double delta_cost = Cost_DataSet_NN(NN, training_data) - original_cost;
                NN->layers[l].weights[i * NN->layers_size[NN->num_layers-1] + j] -= h;
                NN->layers[l].cost_gradient_weights[i * NN->layers_size[NN->num_layers - 1] + j] = delta_cost / h;
            }

            NN->layers[l].biases[i] += h;
            double delta_cost = Cost_DataSet_NN(NN, training_data) - original_cost;
            NN->layers[l].biases[i] -= h;
            NN->layers[l].cost_gradient_biases[i] = delta_cost / h;
        }
    }

    Apply_All_Gradients_NN(NN, learning_rate);
}
