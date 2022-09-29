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


/* --------- FUNCTIONS --------- */

double Exp(double x) {
	return pow(2.71828, x);
}

double Node_Cost(double output, double desired_output) {
	double error = desired_output - output;
	return error * error;
}


double Softmax(double x_i, double *x, int n) {
	double sum = 0;

	for (int i = 0; i < n; i++) {
		sum += Exp(x[i]);
	}

	return Exp(x_i) / sum;
}
