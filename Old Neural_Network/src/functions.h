#pragma once

double random_value();

double Sigmoid(double x);
double Sigmoid_Derivation(double x);

double Exp(double x);

double Node_Cost(double output, double desired_output);
double Node_Cost_Derivative(double output, double desired_output);

double Softmax(double * inputs, int index, int length);
double Softmax_Derivation(double * inputs, int index, int length);
