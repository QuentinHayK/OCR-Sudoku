#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nn.h"

/* --------- EXPORT NN --------- */

void Export_NN(struct NeuralNetwork *NN, char file[]) {
	FILE *out=fopen(file,"w");
	
	for (int l = 0; l < NN->num_layers; l++)
	{
		for (int i = 0; i < NN->layers[l].num_nodes_in; i++)
		{
			for (int j = 0; j < NN->layers[l].num_nodes_out; j++)
			{
				fprintf(out, "%f\n", NN->layers[l].weights[i][j]);
			}
			
			fprintf(out, "%f\n", NN->layers[l].biases[i]);
		}
	}
	
	fclose(out);
}



/* --------- IMPORT NN --------- */

void IMPORT_NN(struct NeuralNetwork *NN, char file[]) {
	FILE *in=fopen(file,"r");
	
	char line[1000];
	char *rest;
		
	/*
	while(fgets(line, 1000, in)) {
		printf("%f\n", strtod(line, &rest));
	}
	*/
	
	for (int l = 0; l < NN->num_layers; l++)
	{
		for (int i = 0; i < NN->layers[l].num_nodes_in; i++)
		{
			for (int j = 0; j < NN->layers[l].num_nodes_out; j++)
			{
				fgets(line, 1000, in);
				NN->layers[l].weights[i][j] = strtod(line, &rest);
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








/* --------- MAIN --------- */

int main(int argc, char **argv) 
{
	// Initialize random
	srand(time(NULL));


  // NN...
  struct NeuralNetwork NN;
  int layers_size[128]; // 2 inputs nodes, 1 hidden layer of 50 nodes and 2 outputs nodes

  int temp = 0;
  int acc = 0;
  
  for (int i = 0; argv[2][i] != 0; i++) 
  {
      if (argv[2][i] == ',') 
      {
          layers_size[acc] = temp;
          temp = 0;
          acc++;
      }
         else if (argv[2][i] != ' ') 
         {
             temp = 10*temp + argv[2][i] - '0';
      	 }
  }
  
  layers_size[acc] = temp;

	Init_Neural_Network(&NN, 3, layers_size);
	
	
	if (argc > 1) {
		if (strcmp(argv[1], "--train") == 0) {
			/* We need to train our Neural network on a dataset, so we need to make one */
			/*
			struct DataSet data = { 11, {
				{{0, 0}, {1, 0}, "Black"},
				{{1, 1}, {1, 0}, "Black"},
				{{1, 2}, {0, 1}, "Red"},
				{{1, 5}, {0, 1}, "Red"},
				{{2, 2}, {1, 0}, "Black"},
				{{3, 1}, {1, 0}, "Black"},
				{{3, 2.5}, {0, 1}, "Red"},
				{{4, 1}, {1, 0}, "Black"},
				{{5, 2}, {1, 0}, "Black"},
				{{5, 3}, {0, 1}, "Red"},
				{{5, 5}, {0, 1}, "Red"},
			} };
			*/
			
			
			// Get Dataset from a folder
			struct DataSet data;
			data.length = 4;
			
			for (int i = 0; i < data.length; i++) {
				char text[128];
				snprintf(text, 128, "data/%s/%u.txt", argv[3], i);
				Get_Data_From_File(&data.data_set[i], text);
			}
			
			
			// Compute the cost of our NN...
			double cost = Cost_DataSet_NN(&NN, data);
			//double inputsTest[2] = {0, 1};
			//printf("Original cost : %f\n", cost);
			
			// Visualize outputs before correct them...
			//Calculate_Outputs_NN(NN, inputsTest);
			// We realy use 2 layers because the output of the 2nd is the input of the 3rd...
			//printf("Outputs before gradient descent : [%f]\n", NN->layers[NN->num_layers-2].outputs[0]);
			
			// Learning time...
			double epochs = 500000;
			for (int i = 0; i < epochs; i++) {
				// Gradient descent...
				Gradient_Descent_NN(&NN, data, 0.1);
				cost = Cost_DataSet_NN(&NN, data);
				printf("Cost : %f\n", cost);
				//printf("Outputs after gradient descent (%u) : [%f, %f]\n", i, NN.layers[NN.num_layers-2].outputs[0], NN.layers[NN.num_layers-2].outputs[1]);
			}
			
			
			// Final outputs...
			//printf("Outputs after gradient descent (FINAL) : [%f, %f]\n", NN->layers[NN->num_layers-2].outputs[0], NN->layers[NN->num_layers-2].outputs[1]);
				
			//cost = Cost_DataSet_NN(NN, data);
			//printf("Cost after gradient descent : %f\n", cost);
			
			
			Export_NN(&NN, argv[4]);
      printf("NN has been exported.");
		}
		else if (strcmp(argv[1], "--test") == 0 ) {
			IMPORT_NN(&NN, argv[3]);
		}
	}
	
		
	printf("\n--------------------------------------------------------\n\n");
	
	
	double inputsTest1[2] = {0, 0};
	char *labels[2] = {"0", "1"};
	Calculate_Outputs_NN(&NN, inputsTest1);
	printf("[%f, %f] : [%f, %f] => %s\n", inputsTest1[0], inputsTest1[1], NN.layers[NN.num_layers-2].outputs[0], NN.layers[NN.num_layers-2].outputs[1], Get_Output_Label_NN(NN, inputsTest1, labels));
	
	
	printf("\n--------------------------------------------------------\n");
	

  return 0;
}
