#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* --------- RANDOM --------- */

double random_value() {
	return (double)rand() / (double) RAND_MAX;
}





/* --------- ACTIVATION FUNCTIONS --------- */

double Sigmoid(double x) {
	return (1 / (1 + pow(2.71828, -x)));
}

double Sigmoid_Derivation(double x) {
	return Sigmoid(x) * (1 - Sigmoid(x));
}





/* --------- FUNCTIONS --------- */

double Exp(double x) {
	return pow(2.71828, x);
}

double Node_Cost(double output, double desired_output) {
	double error = output - desired_output;
	return error * error;
}

double Node_Cost_Derivative(double output, double desired_output) {
	return 2 * (output - desired_output);
}


double Softmax(double x_i, double *x, int n) {
	double sum = 0;
	
	for (int i = 0; i < n; i++) {
		sum += Exp(x[i]);
	}
	
	return Exp(x_i) / sum;
}


/* --------- DATA --------- */

struct Data {
	double input[2];
	double expected_output[64]; // Output nodes wanted
	char label[64];
};





/* --------- DATA SET --------- */

struct DataSet {
	int length;
	struct Data data_set[1024];
};





/* --------- LAYERS --------- */

struct Layer {
	int num_nodes_in;
    int num_nodes_out;

    double weights[64][64];
    double biases[64];

    double outputs[64];

    double cost_gradient_weights[64][64];
    double cost_gradient_biases[64];

    double weighted_inputs[64];
    double inputs[64];	
};

void Init_Layer(struct Layer *layer, int num_nodes_in, int num_nodes_out)
{
	layer->num_nodes_in = num_nodes_in;
	layer->num_nodes_out = num_nodes_out;
	
	//printf("%u\n", num_nodes_out);
	
	for (int i = 0; i < num_nodes_out; i++) {
		for (int j = 0; j < num_nodes_in; j++) {
			layer->weights[j][i] = (random_value()*2-1) / sqrt(num_nodes_in);
		}
		
		layer->biases[i] = 0;
	}
}

double *Calculate_Outputs_Layer(struct Layer *layer, double inputs[]) {
	for (int i = 0; i < layer->num_nodes_in; i++) {
		layer->inputs[i] = inputs[i];
	}
		
	for (int i = 0; i < layer->num_nodes_out; i++) {
		layer->weighted_inputs[i] = 0;
		layer->outputs[i] = 0;
		
		for (int j = 0; j < layer->num_nodes_in; j++) {
			layer->weighted_inputs[i] += layer->inputs[j] * layer->weights[j][i];
			layer->outputs[i] += layer->inputs[j] * layer->weights[j][i];
		}
		
		layer->outputs[i] += layer->biases[i];
		
		// Activation function...
		layer->outputs[i] = Sigmoid(layer->outputs[i]);
	}
	
	return layer->outputs;
}

void Apply_Gradients_Layer(struct Layer *layer, double learning_rate) {
	for (int i = 0; i < layer->num_nodes_out; i++) {
		layer->biases[i] -= layer->cost_gradient_biases[i] * learning_rate;
		
		for (int j = 0; j < layer->num_nodes_in; j++) {
			layer->weights[j][i] -= layer->cost_gradient_weights[j][i] * learning_rate;
		}
	}
}

// For Gradient Descent...
double *Calculate_Outputs_Layer_New_Node_Values_Layer(struct Layer *layer, double expected_output[]) {
	double *new_node_values = malloc(64 * sizeof(double));
	
	for (int i = 0; i < layer->num_nodes_out; i++) {
		double cost_derivative = Node_Cost_Derivative(layer->outputs[i], expected_output[i]);
		double activation_derivative = Sigmoid_Derivation(layer->weighted_inputs[i]);
		new_node_values[i] = cost_derivative * activation_derivative;
	}
	
	return new_node_values;
}

double *Calculate_Hidden_Layer_Node_Values_Layer(struct Layer *layer, struct Layer next_layer, double *next_node_values) {
	double *new_node_values = malloc(64 * sizeof(double));
	
	for (int i = 0; i < layer->num_nodes_out; i++) {
		double new_node_value = 0;
		
		for (int j = 0; j < next_layer.num_nodes_out; j++) {
			double weighted_input_derivative = next_layer.weights[i][j];
			new_node_value += weighted_input_derivative * next_node_values[j];
		}
		
		new_node_value *= Sigmoid_Derivation(layer->weighted_inputs[i]);
		new_node_values[i] = new_node_value;
	}
	
	return new_node_values;
}

void Update_Gradients_Layer(struct Layer *layer, double new_node_values[]) {
		for (int i = 0; i < layer->num_nodes_out; i++) {
			for (int j = 0; j < layer->num_nodes_in; j++) {
				double partial_derivative_cost_weight = layer->inputs[j] * new_node_values[i];
				layer->cost_gradient_weights[j][i] += partial_derivative_cost_weight;
			}
			
			double partial_derivative_cost_bias = 1 * new_node_values[i];
			layer->cost_gradient_biases[i] += partial_derivative_cost_bias;
		}
}

void Clear_Gradient_Layer(struct Layer *layer) {
	for (int i = 0; i < layer->num_nodes_out; i++) {
		for (int j = 0; j < layer->num_nodes_in; j++) {
			layer->cost_gradient_weights[j][i] = 0;
		}
		layer->cost_gradient_biases[i] = 0;
	}
}




/* --------- NEURAL NETWORK --------- */

struct NeuralNetwork {
	struct Layer layers[8];
	int num_layers;
	int layers_size[8];
};

void Init_Neural_Network(struct NeuralNetwork *NN, int num_layers, int layers_size[]) {
	for (int i = 0; i < num_layers-1; i++) {
		Init_Layer(&NN->layers[i], layers_size[i], layers_size[i+1]);
		NN->layers_size[i] = layers_size[i];
	}
	
	NN->num_layers = num_layers;
}

double *Calculate_Outputs_NN(struct NeuralNetwork *NN, double input[]) {
	Calculate_Outputs_Layer(&NN->layers[0], input);
	
	for (int i = 1; i < NN->num_layers-1; i++) {
		Calculate_Outputs_Layer(&NN->layers[i], NN->layers[i-1].outputs);
	}
	
	return NN->layers[NN->num_layers-2].outputs;
}

double Cost_Data_NN(struct NeuralNetwork *NN, struct Data data) {	
	double *res = Calculate_Outputs_NN(NN, data.input);
	
	double cost = 0;
	
	
	for (int i = 0; i < NN->layers_size[NN->num_layers-2]; i++) {
		cost += Node_Cost(res[i], data.expected_output[i]);
	}
	
	printf("%f | %f return %f | %f instead %f |%f\n", data.input[0], data.input[1], res[0], res[1], data.expected_output[0], data.expected_output[1]);
	
	return cost;
}

double Cost_DataSet_NN(struct NeuralNetwork *NN, struct DataSet data) {
	double total_cost = 0;
	
	for (int i = 0; i < data.length; i++) {
		total_cost += Cost_Data_NN(NN, data.data_set[i]);
	}
	
	return total_cost;
}

void Clear_All_Gradients_NN(struct NeuralNetwork *NN) {
	for (int i = 0; i < NN->num_layers-1; i++) {
		Clear_Gradient_Layer(&NN->layers[i]);
	}
}

void Apply_All_Gradients_NN(struct NeuralNetwork *NN, double learning_rate) {
	for (int i = 0; i < NN->num_layers-1; i++) {
		Apply_Gradients_Layer(&NN->layers[i], learning_rate);
	}
}

void Update_All_Gradients_NN(struct NeuralNetwork *NN, struct Data data) {
	Calculate_Outputs_NN(NN, data.input);
	
	// Backpropagation...
	// Output layer is the 2nd last layer
	double *new_node_values = Calculate_Outputs_Layer_New_Node_Values_Layer(&NN->layers[NN->num_layers-2], data.expected_output);
	Update_Gradients_Layer(&NN->layers[NN->num_layers-2], new_node_values);
	
	// We propage values from back layers to front layers...
	for (int i = NN->num_layers-2; i >= 0; i--) {
		new_node_values = Calculate_Hidden_Layer_Node_Values_Layer(&NN->layers[i], NN->layers[i+1], new_node_values);
		Update_Gradients_Layer(&NN->layers[i], new_node_values);
	}
}

void Gradient_Descent_NN(struct NeuralNetwork *NN, struct DataSet training_data, double learning_rate) {	
	for (int i = 0; i < training_data.length; i++) {
		Update_All_Gradients_NN(NN, training_data.data_set[i]);
	}
	
	Apply_All_Gradients_NN(NN, learning_rate / training_data.length);
	
	Clear_All_Gradients_NN(NN);
}

void Slow_Gradient_Descent_NN(struct NeuralNetwork *NN, struct DataSet training_data, double learning_rate)
{
	/*
	double h = 0.0001;
	double originalCost = Cost_DataSet_NN(NN, training_data);
	
	for (int l = 0; l < NN->num_layers; l++)
	{
		for (int i = 0; i < NN->layers[l].num_nodes_in; i++)
		{
			for (int j = 0; j < NN->layers[l].num_nodes_out; j++)
			{
				NN->layers[l].weights[j][i] += h;
				double deltaCost = Cost_DataSet_NN(NN, training_data) - originalCost;
				NN->layers[l].weights[j][i] -= h;
				NN->layers[l].cost_gradient_weights[j][i] = deltaCost / h;
			}
			NN->layers[l].biases[i] += h;
			double deltaCost = Cost_DataSet_NN(NN, training_data) - originalCost;
			NN->layers[l].biases[i] -= h;
			NN->layers[l].cost_gradient_biases[i] = deltaCost / h;
		}
	}
	
	Apply_All_Gradients_NN(NN, learning_rate);
	*/
}



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




void SDL_ExitWithError(const char *message) {
  SDL_Log("ERROR : %s > %s\n", message, SDL_GetError());
  SDL_Quit();
  exit(EXIT_FAILURE);
}




/* --------- MAIN --------- */

int main(int argc, char **argv) 
{
	// Initialize random
	srand(time(NULL));
	
	// Initialize the SDL lib...
  int quit = 0;
  SDL_Event event;
 
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_JPG);
 
  SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
 
  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Surface * image = IMG_Load("data/digits/0/img_1.jpg");
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
 
  while (quit != 1)
  {
      SDL_WaitEvent(&event);

      switch (event.type)
      {
          case SDL_QUIT:
          quit = 1;
          break;
      }
 
      //SDL_Rect dstrect = { 5, 5, 320, 240 };
      //SDL_RenderCopy(renderer, texture, NULL, &dstrect);
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
  }
 
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(image);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  
  IMG_Quit(); 
  SDL_Quit();

	// NN...
	struct NeuralNetwork NN;
	int layers_size[] = {2, 50, 2}; // 2 inputs nodes, 1 hidden layer of 50 nodes and 2 outputs nodes
	Init_Neural_Network(&NN, 3, layers_size);
	
	
	if (argc > 1) {
		if (strcmp(argv[1], "--learn") == 0) {
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
				snprintf(text, 128, "data/XOR/%u.txt", i);
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
			
			
			Export_NN(&NN, "NN.txt");
      printf("NN has been exported.");
		}
		else if (strcmp(argv[1], "--test") == 0 ) {
			IMPORT_NN(&NN, "NN.txt");
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
