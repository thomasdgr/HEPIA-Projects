#ifndef COVOLVE_H
#define COVOLVE_H

#define _GNU_SOURCE

#include <math.h>
#include "../ppm/ppm.h"

typedef struct partial_convolution{
  int idThread;
  int numberOfThreads;
  img_t* imgSource;
  img_t *imgDest;
  double* kernel;
  int kernelSize;

} partial_convolution;

void* convolve(void* arg);

#endif

