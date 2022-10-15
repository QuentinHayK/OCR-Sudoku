#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../data.h"


/* Constants */
#define WINDOW_WIDTH 28
#define MAXCHAR 4096
/* --------- */


void Get_CSV_Data_Image(char *file_name, struct DataSet * data_set)
{
    FILE *fp;
    char row[MAXCHAR];
    char *token;

    fp = fopen(file_name,"r");

    int r = 0;
    while (feof(fp) != true && r <= data_set->length)
    {
        char label[2] = {0, 0};
        char * fgets_return = fgets(row, MAXCHAR, fp);
        if (fgets_return[0] == 0)
            printf("BUG\n");

        token = strtok(row, ",");

        int i = 0;
        int img_pixel_index = 0;
        while(token != NULL)
        {
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
        if (r >= 1)
            data_set->data_set[r-1].expected_output[label[0]-'0'] = 1;

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


void Get_Data_From_File(struct Data *data_i, char file[]) {	
	FILE *in=fopen(file,"r");
	
	char line[1000];
	char *rest;
	
	int i = 0;

	while (strcmp(line, "// OUTPUTS\n") != 0)
	{
		char * fgets_test1 = fgets(line, 1000, in);

        if (fgets_test1[0] == 0)
            printf("%s", fgets_test1);

		data_i->input[i] = strtod(line, &rest);
		printf("%s", line);
		i++;
	}
	
	i = 0;
	while (strcmp(line, "// LABEL\n") != 0)
	{
		char * fgets_test2 = fgets(line, 1000, in);
		
        if (fgets_test2[0] == 0)
            printf("%s", fgets_test2);
        
        data_i->expected_output[i] = strtod(line, &rest);
		i++;
	}
	
	char * fgets_test3 = fgets(line, 1000, in);
	data_i->label[0] = line[0];
	data_i->label[1] = line[1];

    if (fgets_test3[0] == 0)
        printf("%s", fgets_test3);
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
