#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "data.h"
#include "user_inputs_functions.h"
#include "functions.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>


/* Constants */
#define INPUTS_R 784 // 784
#define INPUTS_C 1

#define HIDDENS_R 12 // 12
#define HIDDENS_C 1

#define OUTPUTS_R 10 // 10
#define OUTPUTS_C 1

#define DATA_LENGTH 1000

#define DELTA 0.4

#define EPOCHS 5000

#define XOR_DATA "src/neural_network/XOR.csv"
#define DIGITS_DATA "src/neural_network/TMNIST_Data.csv"
#define SELECTED_DATA DIGITS_DATA

#define SAVE "src/neural_network/save"
#define DIGIT_PNG "src/neural_network/digits/nine.png"

/* Structs */
struct Neural_Network
{
    double inputs[INPUTS_R * INPUTS_C];

    double w1[INPUTS_R * HIDDENS_R];
    double w1_derivative[INPUTS_R * HIDDENS_R];
    double b1[HIDDENS_R];
    double b1_derivative[HIDDENS_R];
    double hiddens[HIDDENS_R * HIDDENS_C];

    double w2[OUTPUTS_R * HIDDENS_R];
    double w2_derivative[OUTPUTS_R * HIDDENS_R];
    double b2[OUTPUTS_R];
    double b2_derivative[OUTPUTS_R];
    double outputs[OUTPUTS_R * OUTPUTS_C];
};


/* Methods */
void draw(SDL_Renderer* renderer, SDL_Texture* texture);
void event_loop(SDL_Renderer* renderer, SDL_Texture* texture);
SDL_Surface* load_image (const char* path);
Uint8 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format);
void Export_NN(struct Neural_Network * NN, char file[]);
void Import_NN(struct Neural_Network * NN, char file[]);
int Max_label_from_doubles(double *output, int len);
double Node_Cost(double output, double desired_output);
double Node_Cost_Derivative(double output, double desired_output);
void Get_Layers_Outputs(struct Neural_Network * NN);
double Calculate_Cost(struct Neural_Network * NN, struct Data data);
double Calculate_Total_Cost(struct Neural_Network NN, struct DataSet data_set);
void Learning(struct Neural_Network * NN, struct DataSet data);
void red();
void green();
void reset_color();
int Neural_Network_Main(void);
