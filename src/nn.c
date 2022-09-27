#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "functions.h"
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

void Init_Neural_Network(struct NeuralNetwork *NN, int num_layers, int layers_size[]) {
	for (int i = 0; i < num_layers-1; i++) {
		Init_Layer(&NN->layers[i], layers_size[i], layers_size[i+1]);
		NN->layers_size[i] = layers_size[i];
	}
	
	NN->num_layers = num_layers;
}

double *Calculate_Outputs_NN(struct NeuralNetwork *NN, double input[]) {
	Calculate_Outputs_Layer(&NN->layers[0], input);
	
	for (int i = 1; i < NN->num_layers-1; i++) {
		Calculate_Outputs_Layer(&NN->layers[i], NN->layers[i-1].outputs);
	}
	
	return NN->layers[NN->num_layers-2].outputs;
}

double Cost_Data_NN(struct NeuralNetwork *NN, struct Data data) {	
	double *res = Calculate_Outputs_NN(NN, data.input);
	
	double cost = 0;
	
	
	for (int i = 0; i < NN->layers_size[NN->num_layers-2]; i++) {
		cost += Node_Cost(res[i], data.expected_output[i]);
	}
	
	printf("%f | %f return %f | %f instead %f |%f\n", data.input[0], data.input[1], res[0], res[1], data.expected_output[0], data.expected_output[1]);
	
	return cost;
}

double Cost_DataSet_NN(struct NeuralNetwork *NN, struct DataSet data) {
	double total_cost = 0;
	
	for (int i = 0; i < data.length; i++) {
		total_cost += Cost_Data_NN(NN, data.data_set[i]);
	}
	
	return total_cost;
}

void Clear_All_Gradients_NN(struct NeuralNetwork *NN) {
	for (int i = 0; i < NN->num_layers-1; i++) {
		Clear_Gradient_Layer(&NN->layers[i]);
	}
}

void Apply_All_Gradients_NN(struct NeuralNetwork *NN, double learning_rate) {
	for (int i = 0; i < NN->num_layers-1; i++) {
		Apply_Gradients_Layer(&NN->layers[i], learning_rate);
	}
}

void Update_All_Gradients_NN(struct NeuralNetwork *NN, struct Data data) {
	Calculate_Outputs_NN(NN, data.input);
	
	// Backpropagation...
	// Output layer is the 2nd last layer
	double *new_node_values = Calculate_Outputs_Layer_New_Node_Values_Layer(&NN->layers[NN->num_layers-2], data.expected_output);
	Update_Gradients_Layer(&NN->layers[NN->num_layers-2], new_node_values);
	
	// We propage values from back layers to front layers...
	for (int i = NN->num_layers-2; i >= 0; i--) {
		new_node_values = Calculate_Hidden_Layer_Node_Values_Layer(&NN->layers[i], NN->layers[i+1], new_node_values);
		Update_Gradients_Layer(&NN->layers[i], new_node_values);
	}
}

void Gradient_Descent_NN(struct NeuralNetwork *NN, struct DataSet training_data, double learning_rate) {	
	for (int i = 0; i < training_data.length; i++) {
		Update_All_Gradients_NN(NN, training_data.data_set[i]);
	}
	
	Apply_All_Gradients_NN(NN, learning_rate / training_data.length);
	
	Clear_All_Gradients_NN(NN);
}
