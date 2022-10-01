#pragma once

/* --------- LAYERS --------- */

struct Layer {
    int num_nodes_in;
    int num_nodes_out;

    double weights[10000];
    double biases[10000];

    double outputs[10000];

    double cost_gradient_weights[10000];
    double cost_gradient_biases[10000];

    double weighted_inputs[10000];
    double inputs[1000];	
};

void Init_Layer(struct Layer *layer, int num_nodes_in, int num_nodes_out);
double *Calculate_Outputs_Layer(struct Layer *layer, double inputs[]);
void Apply_Gradients_Layer(struct Layer *layer, double learning_rate);
