#ifndef ADAPTATIVE_THRESHOLD
#define ADAPTATIVE_THRESHOLD

void get_mean_dev(Matrix* mat, float* mean, float* dev);
void get_neighborhood_stats(Matrix* img, int i, int j, float* mean, float* dev);
void adap_thresh(Matrix* mat);

#endif
