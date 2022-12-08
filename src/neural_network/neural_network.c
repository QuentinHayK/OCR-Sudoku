#include "neural_network.h"


const int INIT_WIDTH = 28;
const int INIT_HEIGHT = 28;


void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    int copy = SDL_RenderCopy(renderer, texture, NULL, NULL);
    if (copy != 0)         
	    errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_RenderPresent(renderer);
}

void event_loop(SDL_Renderer* renderer, SDL_Texture* texture)
{

    SDL_Event event;
    SDL_Texture* t = texture;

    while (1)
    {
	SDL_WaitEvent(&event);
        switch (event.type)
        {
	    // If the "quit" button is pushed, ends the event loop.             
            case SDL_QUIT:                                                      
		        return;                                                                                                                             
            // If the window is resized, updates and redraw the image           
            case SDL_WINDOWEVENT:                                               
	        {
		        if (event.window.event == SDL_WINDOWEVENT_RESIZED)              
                {                                                               
                     draw(renderer, t);                                    
                }                                                               
		        break;
	        }
		    break;
	    }

    } 
}



SDL_Surface* load_image (const char* path)
{
	SDL_Surface* surface_temp = IMG_Load(path);
	if (surface_temp == NULL)
		errx(EXIT_FAILURE, "failed loading image : %s", SDL_GetError());

	SDL_Surface* surface = SDL_ConvertSurfaceFormat(surface_temp, SDL_PIXELFORMAT_RGB888, 0);
	SDL_FreeSurface (surface_temp);
	return surface;
}

Uint8 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    Uint8 average = (0.3 * r) + (0.59 * g) + (0.11 * b);
    
    //printf("%d %d %d : %d\n", r, g, b, average);
    
    r = average;
    g = average;
    b = average;
    Uint32 color = SDL_MapRGB(format, r, g, b);
    return color;
}

/* Save Manager */

void Export_NN(struct Neural_Network * NN, char file[])
{
	FILE *out = fopen(file, "w");

	for (int i = 0; i < INPUTS_R * HIDDENS_R; i++)
	    fprintf(out, "%f\n", NN->w1[i]);

    for (int i = 0; i < HIDDENS_R; i++)
	    fprintf(out, "%f\n", NN->b1[i]);

    for (int i = 0; i < OUTPUTS_R * HIDDENS_R; i++)
	    fprintf(out, "%f\n", NN->w2[i]);

    for (int i = 0; i < OUTPUTS_R; i++)
	    fprintf(out, "%f\n", NN->b2[i]);


    fclose(out);
}

void Import_NN(struct Neural_Network * NN, char file[])
{
	FILE * in = fopen(file, "r");

    char line[1000];
    char *rest;

    for (int i = 0; i < INPUTS_R * HIDDENS_R; i++)
    {
	    fgets(line, 1000, in);
	    NN->w1[i] = strtod(line, &rest);
    }

    for (int i = 0; i < HIDDENS_R; i++)
    {
	    fgets(line, 1000, in);
	    NN->b1[i] = strtod(line, &rest);
    }

    for (int i = 0; i < OUTPUTS_R * HIDDENS_R; i++)
    {
	    fgets(line, 1000, in);
	    NN->w2[i] = strtod(line, &rest);
    }

    for (int i = 0; i < OUTPUTS_R; i++)
    {
	    fgets(line, 1000, in);
	    NN->b2[i] = strtod(line, &rest);
    }

    fclose(in);
}


/* --------- FUNCTIONS --------- */

int Max_label_from_doubles(double *output, int len)
{
    double max = output[0];
    int max_i = 0;

    for (int i = 1; i < len; i++)
    {
	    if (output[i] > max)
	    {
		    max = output[i];
		    max_i = i;
	    }
    }

    return max_i;
}

double Node_Cost(double output, double desired_output) {
    double error = output - desired_output;
    return error * error;
}

double Node_Cost_Derivative(double output, double desired_output) {
    return 2 * (output - desired_output);
}

void Get_Layers_Outputs(struct Neural_Network * NN)
{
    /* Layer 1 */
	Mult_Matrix(NN->w1, NN->inputs, HIDDENS_R, INPUTS_R, INPUTS_C, NN->hiddens);
	Add_Matrix(NN->hiddens, NN->b1, HIDDENS_R, HIDDENS_C, NN->hiddens);
	Matrix_Sigmoid(NN->hiddens, HIDDENS_R, HIDDENS_C);

    /* Layer 2 */
    Mult_Matrix(NN->w2, NN->hiddens, OUTPUTS_R, HIDDENS_R, HIDDENS_C, NN->outputs);
	Add_Matrix(NN->outputs, NN->b2, OUTPUTS_R, OUTPUTS_C, NN->outputs);
	Matrix_Sigmoid(NN->outputs, OUTPUTS_R, OUTPUTS_C);
}

double Calculate_Cost(struct Neural_Network * NN, struct Data data)
{
	double cost = 0;

    for (int i = 0; i < INPUTS_R; i++)
	{
		NN->inputs[i] = data.input[i];
	}

	Get_Layers_Outputs(NN);

	for (int i = 0; i < OUTPUTS_R; i++)
	{
		cost += Node_Cost(NN->outputs[i], data.expected_output[i]);
	}

	return cost;
}

double Calculate_Total_Cost(struct Neural_Network NN, struct DataSet data_set)
{
	double total_cost = 0;

	for (int i = 0; i < data_set.length; i++)
    {
	    total_cost += Calculate_Cost(&NN, data_set.data_set[i]);
	}

	return total_cost;
}

void Learning(struct Neural_Network * NN, struct DataSet data)
{
	for (int epoch = 1; epoch <= EPOCHS; epoch++)
    {
	    Reset_Matrix(INPUTS_R, HIDDENS_R, NN->w1_derivative);
	    Reset_Matrix(HIDDENS_R, 1, NN->b1_derivative);     
	    Reset_Matrix(OUTPUTS_R, HIDDENS_R, NN->w2_derivative);
	    Reset_Matrix(OUTPUTS_R, 1, NN->b2_derivative);

	    double delta = DELTA;
        double original_cost = Calculate_Cost(NN, data.data_set[epoch%data.length]); // Modified from Total_Cost

        for (int j = 0; j < INPUTS_R * HIDDENS_R; j++)
        {
            NN->w1[j] += delta;
            double cost = Calculate_Cost(NN, data.data_set[epoch%data.length]) - original_cost;
            NN->w1_derivative[j] += cost;
            NN->w1[j] -= delta;
        }

        for (int j = 0; j < HIDDENS_R; j++)
        {
            NN->b1[j] += delta;
            double cost = Calculate_Cost(NN, data.data_set[epoch%data.length]) - original_cost;
            NN->b1_derivative[j] += cost;
            NN->b1[j] -= delta;
        }

        for (int j = 0; j < OUTPUTS_R * HIDDENS_R; j++)
        {
            NN->w2[j] += delta;
            double cost = Calculate_Cost(NN, data.data_set[epoch%data.length]) - original_cost;
            NN->w2_derivative[j] += cost;
            NN->w2[j] -= delta;
        }

        for (int j = 0; j < OUTPUTS_R; j++)
        {
            NN->b2[j] += delta;
            double cost = Calculate_Cost(NN, data.data_set[epoch%data.length]) - original_cost;
            NN->b2_derivative[j] += cost;
            NN->b2[j] -= delta;
        }

        for (int j = 0; j < INPUTS_R * HIDDENS_R; j++)
           NN->w1[j] -= NN->w1_derivative[j];

        for (int j = 0; j < HIDDENS_R; j++)
            NN->b1[j] -= NN->b1_derivative[j];

        for (int j = 0; j < OUTPUTS_R * HIDDENS_R; j++)
            NN->w2[j] -= NN->w2_derivative[j];

        for (int j = 0; j < OUTPUTS_R; j++)
            NN->b2[j] -= NN->b2_derivative[j];
     	
		// Print current cost
		if ((epoch > 0 && epoch % 1 == 0) || epoch == 1)
		{
			//printf("\b\b\b\b\b\b\b\b");
			printf("\n[Epoch : %d] Cost : ", epoch);
		}
		else if (epoch > 0)
			printf("\b\b\b\b\b\b\b\b");
		else
			printf("\n[Epoch : %d] Cost : ", epoch);
		printf("%8f", Calculate_Total_Cost(*NN, data));	
	}
	printf("\n\n");
}

void red()
{
  printf("\033[0;31m");
}

void green()
{
  printf("\033[0;32m");
}

void reset_color()
{
  printf("\033[0m");
}

int Neural_Network_Main(char* digit_png)
{
    // - Initialize the SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    }

    // - Create a window.
    SDL_Window* window = SDL_CreateWindow("Rotation_OCR", 0, 0, INIT_WIDTH, INIT_HEIGHT,
             SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
       errx(EXIT_FAILURE, "%s", SDL_GetError());

    // - Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
       errx(EXIT_FAILURE, "%s", SDL_GetError());

    // - Cree la surface depuis l'image
    SDL_Texture* StartText = IMG_LoadTexture(renderer, digit_png);
    if (StartText==NULL)
       errx(EXIT_FAILURE, "%s", SDL_GetError());

    int w = INIT_WIDTH;
    int h = INIT_HEIGHT;
    if (SDL_QueryTexture(StartText, NULL, NULL, &w, &h) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());


    //EXEC
    SDL_Surface* Start_surface = load_image(digit_png);

    //SDL_SetWindowSize(window, w, h);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, Start_surface);
    if (texture==NULL)
	    errx(EXIT_FAILURE, "%s", SDL_GetError());


	struct DataSet data;
	data.length = DATA_LENGTH;
	data.data_set = malloc(sizeof(struct Data) * data.length);
	Get_CSV_Data_Image(SELECTED_DATA, &data);


	struct Neural_Network NN;
	
	New_Matrix(HIDDENS_R, INPUTS_R, (&NN)->w1);
	New_Matrix(OUTPUTS_R, HIDDENS_R, (&NN)->w2);


	int file_exists = Is_File_Exists(SAVE);
	if (file_exists == 1)
	{
		Import_NN(&NN, SAVE);
	}

	// Train our Neural Network :
	if (file_exists == 0)
	{
		Learning(&NN, data);
		Export_NN(&NN, SAVE);
	}

	// Print results
	printf("------------ Results ------------\n\n");

	int score = 0;

	for (int j = 0; j < data.length; j++)
	{
		for (int i = 0; i < INPUTS_R; i++)
		{
			(&NN)->inputs[i] = data.data_set[j].input[i];
			//printf("data : %f\n", data.data_set[j].input[i]);
		}
		
		Get_Layers_Outputs(&NN);

		//Print_Matrix("Input", NN.inputs, INPUTS_R, INPUTS_C);
		int output_label = Max_label_from_doubles(NN.outputs, OUTPUTS_R * OUTPUTS_C);
		int expected_output_label = data.data_set[j].label[0] - '0';

		if (output_label == expected_output_label)
		{
		    green();
		    score++;
		}
		else
			red();
		printf("Expected : %d => Output : %d\n", expected_output_label, output_label);
		reset_color();
		//Print_Matrix("Output", NN.outputs, OUTPUTS_R, OUTPUTS_C);
	}
    
	printf("\nsucces during training : %d/100\n", (int)((double)score / (double)data.length * 100));

	printf("\n---------------------------------\n");
	

	printf("\n-------------- Test -------------\n\n");


    Uint32* pixels = Start_surface->pixels;
    SDL_PixelFormat* format = Start_surface->format;
    SDL_LockSurface(Start_surface);
	for (int i = 0; i < INPUTS_R; i++)
	{
		//(&NN)->inputs[i] = data.data_set[50].input[i];
        (&NN)->inputs[i] = pixel_to_grayscale(pixels[i], format);
        //printf("%f\n", (&NN)->inputs[i]);
		//printf("data : %f\n", data.data_set[j].input[i]);
	}
    SDL_UnlockSurface(Start_surface);

	Get_Layers_Outputs(&NN);

	//Print_Matrix("Input", NN.inputs, INPUTS_R, INPUTS_C);
    int output_label = Max_label_from_doubles(NN.outputs, OUTPUTS_R * OUTPUTS_C);

	printf("Expected : You know => Output : %d\n", output_label);
	//Print_Matrix("Output", NN.outputs, OUTPUTS_R, OUTPUTS_C);

	printf("\n---------------------------------\n");

	free(data.data_set);


    SDL_FreeSurface(Start_surface);

    //event_loop(renderer, texture);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}
