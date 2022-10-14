#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "layer.h"
#include "functions.h"

void Init_Layer(struct Layer *layer, int num_nodes_in, int num_nodes_out)
{
	layer->num_nodes_in = num_nodes_in;
	layer->num_nodes_out = num_nodes_out;

	//printf("%u\n", num_nodes_out);

	for (int i = 0; i < num_nodes_out; i++) {
		for (int j = 0; j < num_nodes_in; j++) {
			layer->weights[i*num_nodes_in + j] = (random_value()*2-1) / sqrt(num_nodes_in);
		}

		layer->biases[i] = 0;
	}
}


double *Calculate_Outputs_Layer(struct Layer *layer, double inputs[]) {
	for (int i = 0; i < layer->num_nodes_in; i++) {
		layer->inputs[i] = inputs[i];
	}

	for (int i = 0; i < layer->num_nodes_out; i++) {
		layer->weighted_inputs[i] = layer->biases[i];
		//layer->outputs[i] = 0;

		for (int j = 0; j < layer->num_nodes_in; j++) {
			layer->weighted_inputs[i] += layer->inputs[j] * layer->weights[i * layer->num_nodes_in + j];
			//layer->outputs[i] += layer->inputs[j] * layer->weights[i * layer->num_nodes_in + j];
		}

		layer->weighted_inputs[i] += layer->biases[i];
        layer->outputs[i] = Sigmoid(layer->weighted_inputs[i]);

    }

    for (int i = 0; i < layer->num_nodes_out; i++)
    {
        //layer->outputs[i] = Softmax(layer->weighted_inputs, i, layer->num_nodes_out);
        //printf("[%u] : %f\n", i, layer->outputs[i]);
    }

	return layer->outputs;
}


void Apply_Gradients_Layer(struct Layer *layer, double learning_rate) {
	for (int i = 0; i < layer->num_nodes_out; i++) {
		layer->biases[i] -= layer->cost_gradient_biases[i] * learning_rate;

		for (int j = 0; j < layer->num_nodes_in; j++) {
			layer->weights[i * layer->num_nodes_in + j] -= layer->cost_gradient_weights[i * layer->num_nodes_in + j] * learning_rate;
        }

	}
}


// For Gradient Descent...
double *Calculate_Outputs_Layer_New_Node_Values_Layer(struct Layer *layer, double expected_output[]) {
	double *new_node_values = malloc(1000 * sizeof(double));

	for (int i = 0; i < layer->num_nodes_out; i++) {
		double cost_derivative = Node_Cost_Derivative(layer->outputs[i], expected_output[i]);

        // Activation
		double activation_derivative = Sigmoid_Derivation(layer->weighted_inputs[i]);
		//double activation_derivative = Softmax_Derivation(layer->weighted_inputs, i, layer->num_nodes_out);
        new_node_values[i] = cost_derivative * activation_derivative;
        //printf("[%u] : %f\n", i, new_node_values[i]);
	}

	return new_node_values;
}

double *Calculate_Hidden_Layer_Node_Values_Layer(struct Layer *layer, struct Layer next_layer, double *next_node_values) {
	double *new_node_values = malloc(1000 * sizeof(double));

	for (int i = 0; i < next_layer.num_nodes_out; i++) {
		double new_node_value = 0;

		for (int j = 0; j < layer->num_nodes_out; j++) {
			double weighted_input_derivative = next_layer.weights[j*layer->num_nodes_out+i];
            //printf("%u\n", i*next_layer.num_nodes_out+j);
			new_node_value += weighted_input_derivative * next_node_values[j];
		}

        // Activation
		new_node_value *= Sigmoid_Derivation(layer->weighted_inputs[i]);
		//new_node_value *= Softmax_Derivation(layer->weighted_inputs, i, layer->num_nodes_out);
        new_node_values[i] = new_node_value;
	}

	return new_node_values;
}

void Update_Gradients_Layer(struct Layer *layer, double new_node_values[]) {
		for (int i = 0; i < layer->num_nodes_out; i++) {
			for (int j = 0; j < layer->num_nodes_in; j++) {
				double partial_derivative_cost_weight = layer->inputs[j] * new_node_values[i];
				layer->cost_gradient_weights[i*layer->num_nodes_in+j] += partial_derivative_cost_weight;
			}

			double partial_derivative_cost_bias = 1 * new_node_values[i];
			layer->cost_gradient_biases[i] += partial_derivative_cost_bias;
		}
}

void Clear_Gradient_Layer(struct Layer *layer) {
	for (int i = 0; i < layer->num_nodes_out; i++) {
		for (int j = 0; j < layer->num_nodes_in; j++) {
			layer->cost_gradient_weights[i*layer->num_nodes_in+j] = 0;
		}
		layer->cost_gradient_biases[i] = 0;
	}
}
