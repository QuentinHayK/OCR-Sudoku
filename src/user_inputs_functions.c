#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "nn.h"
#include "data.h"


/* --------- EXPORT NN --------- */

void Export_NN(struct NeuralNetwork *NN, char file[]) {
	FILE *out=fopen(file,"w");
	
	for (int l = 0; l < NN->num_layers; l++)
	{
		for (int i = 0; i < NN->layers[l].num_nodes_in; i++)
		{
			for (int j = 0; j < NN->layers[l].num_nodes_out; j++)
			{
				fprintf(out, "%f\n", NN->layers[l].weights[i*NN->layers[l].num_nodes_out + j]);
			}
			
		}

        printf("\n");
	}
	
	fclose(out);
}



/* --------- IMPORT NN --------- */

void Import_NN(struct NeuralNetwork *NN, char file[]) {
	FILE *in=fopen(file,"r");
	
	char line[1000];
	char *rest;
		
	for (int l = 0; l < NN->num_layers; l++)
	{
		for (int i = 0; i < NN->layers[l].num_nodes_in; i++)
		{
			for (int j = 0; j < NN->layers[l].num_nodes_out; j++)
			{
				fgets(line, 1000, in);
				NN->layers[l].weights[i*NN->layers[l].num_nodes_out + j] = strtod(line, &rest);
			}
			
			fgets(line, 1000, in);
			NN->layers[l].biases[i] = strtod(line, &rest);
		}
	}
	
	fclose(in);
}



char * Get_Output_Label_NN(struct NeuralNetwork NN, double inputs[], char **labels) {
	int best_index = -1;
	double best_score = -1;
	
	for (int i = 0; i < NN.layers[NN.num_layers-2].num_nodes_out; i++) {
		if (best_score < NN.layers[NN.num_layers-2].outputs[i])
		{
			best_score = NN.layers[NN.num_layers-2].outputs[i];
			best_index = i;
		}
	}
	
	return labels[best_index];
}




void Get_Data_From_File(struct Data *data_i, char file[]) {	
	FILE *in=fopen(file,"r");
	
	char line[1000];
	char *rest;
	
	int i = 0;
	while (strcmp(line, "// OUTPUTS\n") != 0)
	{
		fgets(line, 1000, in);
		data_i->input[i] = strtod(line, &rest);
		printf("%s", line);
		i++;
	}
	
	i = 0;
	while (strcmp(line, "// LABEL\n") != 0)
	{
		fgets(line, 1000, in);
		data_i->expected_output[i] = strtod(line, &rest);
		i++;
	}
	
	fgets(line, 1000, in);
	data_i->label[0] = line[0];
	data_i->label[1] = line[1];

}



void GetLayersSize(char * input, int * num_layers, int * layers_size)
{
    int temp = 0;
    int acc = 0;
  
    for (int i = 0; input[i] != 0; i++) 
    {
        if (input[i] == ',') 
        {
            layers_size[acc] = temp;
            temp = 0;
            acc++;
            *num_layers += 1;
        }
        else if (input[i] != ' ') 
        {
            temp = 10*temp + input[i] - '0';
      	}
    }

    *num_layers += 1;
    layers_size[acc] = temp;
}
