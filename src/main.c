#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "nn.h"
#include "user_inputs_functions.h"
#include "data.h"

#define WINDOW_WIDTH 28
#define MAXCHAR 4096


void Get_CSV_Data_Image(int *data, char *file_name, int index, char *label)
{
    FILE *fp;
    char row[MAXCHAR];
    char *token;

    fp = fopen("TMNIST_Data.csv","r");

    int r = 0;
    while (feof(fp) != true)
    {
        fgets(row, MAXCHAR, fp);
        //printf("[%u] Row: %s", r, row);

        token = strtok(row, ",");

        int i = 0;
        int img_pixel_index = 0;
        while(token != NULL)
        {
            /*
            if (i >= 1 && r == 1)
                printf("Token: %s\n", token);
            */
            if (r == index && i == 1)
                for (int j = 0; j < 2; j++)
                    if (token[j] >= '0' && token[j] <= '9')
                        label[j] = token[j];
            if (r == index && i >= 2){
                data[img_pixel_index] = (int)strtol(token, (char **)NULL, 10);
                //printf("%u\n", img[img_pixel_index]);
                img_pixel_index++;
            }
            token = strtok(NULL, ",");
            i++;
        }
        r++;

    }

}

void Display_Digit(int *img)
{
    // Display the digit...
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    int im = 0;
    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            int c = img[im];
            im++;
            SDL_SetRenderDrawColor(renderer, c, c, c, 255);
            SDL_RenderDrawPoint(renderer, j, i);
        }
    }
    SDL_RenderPresent(renderer);
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
}

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
                /*
                char text[128];
                snprintf(text, 128, "data/%s/%u.txt", argv[3], i);
                Get_Data_From_File(&data.data_set[i], text);
                */

                
                int img_[786];
                char label[2];
                Get_CSV_Data_Image(img_, "TMNIST_Data.csv", i+1, label);
                printf("Label : %s\n", label);
                for (int j = 0; j < 786; j++) {
                    data.data_set[i].input[j] = (double)img_[j] / 255; // To simplify
                    printf("%f ", data.data_set[i].input[j]);
                }
                printf("\n");
                

                //Get_CSV_Data_Image("TMNIST_Data.csv", &data);
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
	
	
	double inputsTest1[2] = {1, 5};
	char *labels[2] = {"black", "red"};
	Calculate_Outputs_NN(&NN, inputsTest1);
	printf("[%f, %f] : [%f, %f] => %s\n", inputsTest1[0], inputsTest1[1], NN.layers[NN.num_layers-2].outputs[0], NN.layers[NN.num_layers-2].outputs[1], Get_Output_Label_NN(NN, inputsTest1, labels));
	
	
	printf("\n--------------------------------------------------------\n");



    
    // Import csv... 
    int img[786];
    char label_[2];
    Get_CSV_Data_Image(img, "TMNIST_Data.csv", 2, label_);

    
    Display_Digit(img);
    
   

    return 0;
}
