#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nn.h"
#include "user_inputs_functions.h"
#include "data.h"


int main(int argc, char **argv)
{
    // Init random
    srand(time(NULL));

    int layers_size[128];
    char * test = argv[2];
    int num_layers = 0;
    GetLayersSize(test, &num_layers, layers_size);

    struct NeuralNetwork NN;
    Init_Neural_Network(&NN, num_layers, layers_size);

    if (argc > 1)
    {
        if (strcmp(argv[1], "--train") == 0) // TRAINING
        {
            // Get Dataset from a folder
            struct DataSet data;
            data.length = 10;

            for (int i = 0; i < data.length; i++)
            {
                char text[128];
                snprintf(text, 128, "data/%s/%u.txt", argv[3], i);
                Get_Data_From_File(&data.data_set[i], text);
            }

            // Compute the cost of our NN...
            double cost = Cost_DataSet_NN(&NN, data);
            printf("Original cost : %f\n", cost);


            // Lerning time...
            double epochs = 10000;
            for (int i = 0; i < epochs; i++) {
				// Gradient descent...
				Gradient_Descent_NN(&NN, data, 0.1);
				cost = Cost_DataSet_NN(&NN, data);
				printf("Cost : %f\n", cost);
			}

            // Export our Neural Network in the desired file
            Export_NN(&NN, argv[4]);
            printf("NN has been exported.");
        }
        else if (strcmp(argv[1], "--test") == 0)
        {
            Import_NN(&NN, argv[3]);
        }
    }

    printf("\n--------------------------------------------------------\n\n");
	
	
	double inputsTest1[2] = {5, 2};
	char *labels[2] = {"black", "red"};
	Calculate_Outputs_NN(&NN, inputsTest1);
	printf("[%f, %f] : [%f, %f] => %s\n", inputsTest1[0], inputsTest1[1], NN.layers[NN.num_layers-2].outputs[0], NN.layers[NN.num_layers-2].outputs[1], Get_Output_Label_NN(NN, inputsTest1, labels));
	
	
	printf("\n--------------------------------------------------------\n");

    return 0;
}
