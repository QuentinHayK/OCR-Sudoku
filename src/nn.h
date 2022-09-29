#pragma once
#include "layer.h"
#include "nn.h"
#include "data.h"


/* --------- NEURAL NETWORK --------- */

struct NeuralNetwork {
	struct Layer layers[8];
	int num_layers;
	int layers_size[8];
};

void Init_Neural_Network(struct NeuralNetwork *NN, int num_layers, int layers_size[]);
double *Calculate_Outputs_NN(struct NeuralNetwork *NN, double input[]);

double Cost_Data_NN(struct NeuralNetwork *NN, struct Data data);
double Cost_DataSet_NN(struct NeuralNetwork *NN, struct DataSet data);

void Apply_All_Gradients_NN(struct NeuralNetwork *NN, double learning_rate);
void Gradient_Descent_NN(struct NeuralNetwork * NN, struct DataSet training_data, double learning_rate);

