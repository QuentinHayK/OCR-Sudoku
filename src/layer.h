#pragma once

/* --------- LAYERS --------- */

struct Layer {
    int num_nodes_in;
    int num_nodes_out;

    double weights[4096];
    double biases[64];

    double outputs[64];

    double cost_gradient_weights[4096];
    double cost_gradient_biases[64];

    double weighted_inputs[64];
    double inputs[64];	
};

void Init_Layer(struct Layer *layer, int num_nodes_in, int num_nodes_out);
double *Calculate_Outputs_Layer(struct Layer *layer, double inputs[]);
void Apply_Gradients_Layer(struct Layer *layer, double learning_rate);
