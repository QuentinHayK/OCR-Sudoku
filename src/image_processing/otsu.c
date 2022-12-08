#include "matrix.h"

void otsu(Matrix* img)
{
    int height = img->h,
	width = img->w;
    int histo[256] = { 0 };
    for (int i=0; i<height; i+=1)
	for (int j=0; j<width; j+=1)
	    histo[img->mat[i][j]]++;

    int k,
	y,
	count,
	threshold;

    for (int t=0; t<256; t+=1)
    for (int i=0; i<height; i+=1)
	for (int j=0; j<width; j+=1)
}
