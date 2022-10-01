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
		layer->weighted_inputs[i] = 0;
		layer->outputs[i] = 0;

		for (int j = 0; j < layer->num_nodes_in; j++) {
			layer->weighted_inputs[i] += layer->inputs[j] * layer->weights[i * layer->num_nodes_in + j];
			layer->outputs[i] += layer->inputs[j] * layer->weights[i * layer->num_nodes_in + j];
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
			layer->weights[i * layer->num_nodes_in + j] -= layer->cost_gradient_weights[i * layer->num_nodes_in + j] * learning_rate;
        }

	}
}
