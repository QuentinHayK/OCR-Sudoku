#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdbool.h>
#include "usefull/matrix.h"
#include "data.h"
#include "usefull/user_inputs_functions.h"


/* Constants */
#define WINDOW_WIDTH 28

#define INPUTS_R 784
#define INPUTS_C 1

#define HIDDENS_R 16
#define HIDDENS_C 1

#define OUTPUTS_R 10
#define OUTPUTS_C 1
/* ---------- */


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


int main(void)
{
    struct DataSet data;
    data.length = 2;

    // Get Dataset from a folder
    for (int i = 0; i < data.length; i++)
    {
        Get_CSV_Data_Image("data/TMNIST_Data.csv", &data);
    }

    Display_Digit(data.data_set[0].input);

    /* Handwrited Neural Network */
    double inputs[INPUTS_C * INPUTS_R];
    
    double weights1[INPUTS_R * HIDDENS_R];
    New_Matrix(HIDDENS_R, INPUTS_R, weights1);
    double b1[HIDDENS_R];
    New_Matrix(HIDDENS_R, HIDDENS_C, b1);

    double hiddens[HIDDENS_R * HIDDENS_C] = {0, 0, 0, 0};
    Matrix_Mult(weights1, inputs, HIDDENS_R, INPUTS_R, INPUTS_C, hiddens);
    Matrix_Add(hiddens, b1, HIDDENS_R, HIDDENS_C, hiddens);

    double weights2[OUTPUTS_R * HIDDENS_R];
    New_Matrix(OUTPUTS_R, HIDDENS_R, weights2);
    double b2[OUTPUTS_R];
    New_Matrix(OUTPUTS_R, OUTPUTS_C, b2);
    
    double outputs[OUTPUTS_R * OUTPUTS_C] = {0, 0, 0};
    Matrix_Mult(weights2, hiddens, OUTPUTS_R, HIDDENS_R, HIDDENS_C, outputs);
    Matrix_Add(outputs, b2, OUTPUTS_R, OUTPUTS_C, outputs);


    Print_Matrix("Inputs", inputs, INPUTS_R, INPUTS_C);
    printf("\n");
    Print_Matrix("Hiddens", hiddens, HIDDENS_R, HIDDENS_C);
    printf("\n");
    Print_Matrix("Outputs", outputs, OUTPUTS_R, OUTPUTS_C);
    /* --------------------------- */

    return 0;
}

