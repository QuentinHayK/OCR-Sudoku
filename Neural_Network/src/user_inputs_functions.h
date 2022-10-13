#pragma once
#include "data.h"

void Export_NN(struct NeuralNetwork *NN, char file[]);
void Import_NN(struct NeuralNetwork *NN, char file[]);
char * Get_Output_Label_NN(struct NeuralNetwork NN, double inputs[], char **labels);
void Get_Data_From_File(struct Data *data_i, char file[]);
void * GetLayersSize(char * input, int * num_layers, int * layers_size);
