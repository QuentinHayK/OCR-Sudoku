#ifndef GRADIENTS
#define GRADIENTS

void fill_mag(Matrix* mag, Matrix* gradx, Matrix* grady);
void is_edge(Matrix* mag, double rad, int i, int j);
Matrix* grad(Matrix* mat);

#endif
