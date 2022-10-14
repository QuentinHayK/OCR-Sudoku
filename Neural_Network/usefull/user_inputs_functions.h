#pragma once
#include "../data.h"

void Get_CSV_Data_Image(char *file_name, struct DataSet * data_set);
void Display_Digit(double *img);
void Get_Data_From_File(struct Data *data_i, char file[]);
void * GetLayersSize(char * input, int * num_layers, int * layers_size);
