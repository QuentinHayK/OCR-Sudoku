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


void Get_CSV_Data_Image(char *file_name, struct DataSet * data_set)
{
    FILE *fp;
    char row[MAXCHAR];
    char *token;

    fp = fopen("TMNIST_Data.csv","r");

    int r = 0;
    while (feof(fp) != true && r < data_set->length)
    {
        char label[2];
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

            if (r >= 1 && i == 1)
            {
                label[0] = token[0];
                data_set->data_set[r-1].label[0] = token[0];
            }
            if (r >= 1 && i >= 2)
            {
               
                if (((float)strtol(token, (char **)NULL, 10) / 255) >= 0.25)
                {
                    data_set->data_set[r-1].input[img_pixel_index] = 1;
                }
                img_pixel_index++;
            }
            token = strtok(NULL, ",");
            i++;
        }
        if (r >= 1) {
            data_set->data_set[r-1].expected_output[label[0]-'0'] = 1;
            //printf("%c", label[0]);
            // Print...
            //printf("Label : %s\n", label);
            for (int j = 0; j < 786; j++) {
                //printf("%f ", data_set->data_set[r-1].input[j]);
            }
            //printf("\n");
        }
        r++;

    }

}

void Display_Digit(double *img)
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
            //printf("%f\n", img[im]);
            int c = (int)(img[im]*(double)255);
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

    struct DataSet data;
    data.length = 300;

    if (argc > 1)
    {
        // Get Dataset from a folder
        for (int i = 0; i < data.length; i++)
        {
            Get_CSV_Data_Image("TMNIST_Data.csv", &data);
        }

        if (strcmp(argv[1], "--train") == 0) // TRAINING
        {
            

            // Compute the cost of our NN...
            double cost = Cost_DataSet_NN(&NN, data);
            printf("Original cost : %f\n", cost);


            // Lerning time...
            double epochs = 1000;
            for (int i = 0; i < epochs; i++) {
				// Gradient descent...
				Better_Gradient_Descent_NN(&NN, data, 0.2);
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
	
    double p = 0;

	for (int my_i = 0; my_i < 200; my_i++)
    {
    	char *labels[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	    Calculate_Outputs_NN(&NN, data.data_set[my_i].input);
        
        if (data.data_set[my_i].label[0] == Get_Output_Label_NN(NN, data.data_set[my_i].input, labels)[0])
        {
            p++;
        }
        else
        {
            printf("\033[0;31m");
        }
        
        printf("[%f] [%f] [%f] [%f] [%f] [%f] [%f] [%f] [%f] [%f]", 
                Calculate_Outputs_NN(&NN, data.data_set[my_i].input)[0],
                Calculate_Outputs_NN(&NN, data.data_set[my_i].input)[1],
                Calculate_Outputs_NN(&NN, data.data_set[my_i].input)[2],
                Calculate_Outputs_NN(&NN, data.data_set[my_i].input)[3],
                Calculate_Outputs_NN(&NN, data.data_set[my_i].input)[4],
                Calculate_Outputs_NN(&NN, data.data_set[my_i].input)[5],
                Calculate_Outputs_NN(&NN, data.data_set[my_i].input)[6],
                Calculate_Outputs_NN(&NN, data.data_set[my_i].input)[7],
                Calculate_Outputs_NN(&NN, data.data_set[my_i].input)[8],
                Calculate_Outputs_NN(&NN, data.data_set[my_i].input)[9]);
	    printf(" | [%s] Output => %s\n", data.data_set[my_i].label, Get_Output_Label_NN(NN, data.data_set[my_i].input, labels));
    
        printf("\033[0m");

        //Display_Digit(data.data_set[my_i].input);
    }

    printf("%f\n", p*100/200);
	
	printf("\n--------------------------------------------------------\n");

    
    // Import csv... 
    //int img[786];
    //char label_[2];
    //Get_CSV_Data_Image("TMNIST_Data.csv", 2, label_);

    
       
   

    return 0;
}
