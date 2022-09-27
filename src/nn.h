#pragma once

#include "layer.h"

/* --------- DATA --------- */

struct Data {
	double input[2];
	double expected_output[64]; // Output nodes wanted
	char label[64];
};

/* --------- DATA SET --------- */

struct DataSet {
	int length;
	struct Data data_set[1024];
};

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
void Clear_All_Gradients_NN(struct NeuralNetwork *NN);
void Apply_All_Gradients_NN(struct NeuralNetwork *NN, double learning_rate);
void Update_All_Gradients_NN(struct NeuralNetwork *NN, struct Data data);
void Gradient_Descent_NN(struct NeuralNetwork *NN, struct DataSet training_data, double learning_rate);
