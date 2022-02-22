#ifndef ARRAYPOINTS_H
#define ARRAYPOINTS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct point_2d{
    double x,y;
} point_2d;

typedef struct arrayPoints{
    point_2d* array;
    int length;
} arrayPoints;

arrayPoints createArrayPoints(int numberOfPoints);
void freeArrayPoints(arrayPoints *dataPoints);
arrayPoints createArrayPointsFunction(double xBegin, double xEnd, double step, double (*funct)(double));

#endif
