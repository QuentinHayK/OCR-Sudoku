#pragma once

double random_value();

double Sigmoid(double x);
double Exp(double x);

double Node_Cost(double output, double desired_output);

double Softmax(double x_i, double *x, int n);
