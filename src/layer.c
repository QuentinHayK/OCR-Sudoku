#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "functions.h"


/* --------- LAYERS --------- */

struct Layer {
	int num_nodes_in;
    int num_nodes_out;

    double weights[64][64];
    double biases[64];

    double outputs[64];

    double cost_gradient_weights[64][64];
    double cost_gradient_biases[64];

    double weighted_inputs[64];
    double inputs[64];	
};

void Init_Layer(struct Layer *layer, int num_nodes_in, int num_nodes_out)
{
	layer->num_nodes_in = num_nodes_in;
	layer->num_nodes_out = num_nodes_out;
	
	//printf("%u\n", num_nodes_out);
	
	for (int i = 0; i < num_nodes_out; i++) {
		for (int j = 0; j < num_nodes_in; j++) {
			layer->weights[j][i] = (random_value()*2-1) / sqrt(num_nodes_in);
		}
		
		layer->biases[i] = 0;
	}
}

double *Calculate_Outputs_Layer(struct Layer *layer, double inputs[]) {
	for (int i = 0; i < layer->num_nodes_in; i++) {
		layer->inputs[i] = inputs[i];
	}
		
	for (int i = 0; i < layer->num_nodes_out; i++) {
		layer->weighted_inputs[i] = 0;
		layer->outputs[i] = 0;
		
		for (int j = 0; j < layer->num_nodes_in; j++) {
			layer->weighted_inputs[i] += layer->inputs[j] * layer->weights[j][i];
			layer->outputs[i] += layer->inputs[j] * layer->weights[j][i];
		}
		
		layer->outputs[i] += layer->biases[i];
		
		// Activation function...
		layer->outputs[i] = Sigmoid(layer->outputs[i]);
	}
	
	return layer->outputs;
}

void Apply_Gradients_Layer(struct Layer *layer, double learning_rate) {
	for (int i = 0; i < layer->num_nodes_out; i++) {
		layer->biases[i] -= layer->cost_gradient_biases[i] * learning_rate;
		
		for (int j = 0; j < layer->num_nodes_in; j++) {
			layer->weights[j][i] -= layer->cost_gradient_weights[j][i] * learning_rate;
		}
	}
}

// For Gradient Descent...
double *Calculate_Outputs_Layer_New_Node_Values_Layer(struct Layer *layer, double expected_output[]) {
	double *new_node_values = malloc(64 * sizeof(double));
	
	for (int i = 0; i < layer->num_nodes_out; i++) {
		double cost_derivative = Node_Cost_Derivative(layer->outputs[i], expected_output[i]);
		double activation_derivative = Sigmoid_Derivation(layer->weighted_inputs[i]);
		new_node_values[i] = cost_derivative * activation_derivative;
	}
	
	return new_node_values;
}

double *Calculate_Hidden_Layer_Node_Values_Layer(struct Layer *layer, struct Layer next_layer, double *next_node_values) {
	double *new_node_values = malloc(64 * sizeof(double));
	
	for (int i = 0; i < layer->num_nodes_out; i++) {
		double new_node_value = 0;
		
		for (int j = 0; j < next_layer.num_nodes_out; j++) {
			double weighted_input_derivative = next_layer.weights[i][j];
			new_node_value += weighted_input_derivative * next_node_values[j];
		}
		
		new_node_value *= Sigmoid_Derivation(layer->weighted_inputs[i]);
		new_node_values[i] = new_node_value;
	}
	
	return new_node_values;
}

void Update_Gradients_Layer(struct Layer *layer, double new_node_values[]) {
		for (int i = 0; i < layer->num_nodes_out; i++) {
			for (int j = 0; j < layer->num_nodes_in; j++) {
				double partial_derivative_cost_weight = layer->inputs[j] * new_node_values[i];
				layer->cost_gradient_weights[j][i] += partial_derivative_cost_weight;
			}
			
			double partial_derivative_cost_bias = 1 * new_node_values[i];
			layer->cost_gradient_biases[i] += partial_derivative_cost_bias;
		}
}

void Clear_Gradient_Layer(struct Layer *layer) {
	for (int i = 0; i < layer->num_nodes_out; i++) {
		for (int j = 0; j < layer->num_nodes_in; j++) {
			layer->cost_gradient_weights[j][i] = 0;
		}
		layer->cost_gradient_biases[i] = 0;
	}
}



