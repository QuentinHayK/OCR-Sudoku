#include <math.h>
#include <stdio.h>
#include "matrix.h"

void get_mean_dev(Matrix* mat, float* mean, float* dev)
{
    double sum = 0;
    double sum2 = 0;

    for (int i = 0; i < mat->h; i++)
        for (int j = 0; j < mat->w; j++)
	{
            double value = mat->mat[i][j];

            // Add the value and its square to the sums
            sum += value;
            sum2 += value * value;
        }

    int count = mat->h * mat->w;

    // Calculate the mean and standard deviation of the matrix
    *mean = sum / count;
    *dev = sqrt(sum2 / count - mean[0] * mean[0]);
}

void get_neighborhood_stats(Matrix* img, int i, int j, float* mean, float* dev)
{    
    int n = 5;
    int i_min = i-n < 0 ? 0 : i-n;
    int i_max = img->h < i+n ? img->h : 0;
    int j_min = 0 > j-n ? 0 : j-n;
    int j_max = img->w < j+n ? img->w : j+n;

    Matrix* neighborhood = new_mat(i_max - i_min, j_max - j_min);

    // Extract the neighborhood from the image
    for (int x = i_min; x < i_max; x++) {
        for (int y = j_min; y < j_max; y++) {
            neighborhood->mat[x-i_min][y-j_min] = img->mat[x][y];
        }
    }

    // Calculate the mean and standard deviation of the neighborhood
    get_mean_dev(neighborhood, mean, dev);
    freeMat(neighborhood);
}

void adap_thresh(Matrix* mat)
{
    Matrix* img = init2(mat->mat, mat->h, mat->w);

    for (int i = 0; i < img->h; i++)
	for (int j = 0; j < img->w; j++)
	{
	    float* mean = calloc(1, sizeof(float));
	    float* dev = calloc(1, sizeof(float));
	    get_neighborhood_stats(img, i, j, mean, dev);

	    printf("%d // %f\n", img->mat[i][j], *mean);
	    // Calculate the threshold value for the pixel
	    double threshold = *mean + 1 * (*dev);
	    free(mean);
	    free(dev);
	    
	    mat->mat[i][j] = img->mat[i][j] > threshold ? 255 : 0;
	}
    freeMat(img);
}
