#pragma once

/* --------- LAYERS --------- */

struct Layer {
    int num_nodes_in;
    int num_nodes_out;

    double outputs[64];

    double cost_gradient_weights[15000];
    double cost_gradient_biases[64];

    double weighted_inputs[786];
    double inputs[786];	

    double biases[64];
    double weights[15000];
};

void Init_Layer(struct Layer *layer, int num_nodes_in, int num_nodes_out);
double *Calculate_Outputs_Layer(struct Layer *layer, double inputs[]);
void Apply_Gradients_Layer(struct Layer *layer, double learning_rate);

double *Calculate_Outputs_Layer_New_Node_Values_Layer(struct Layer *layer, double expected_output[]);
double *Calculate_Hidden_Layer_Node_Values_Layer(struct Layer *layer, struct Layer next_layer, double *next_node_values);
void Update_Gradients_Layer(struct Layer *layer, double new_node_values[]);
void Clear_Gradient_Layer(struct Layer *layer);
