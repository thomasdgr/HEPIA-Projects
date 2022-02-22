#include "arrayPoints.h"

// création d'un tableau de points
arrayPoints createArrayPoints(int numberOfPoints){
    arrayPoints dataPoints;
    dataPoints.length = numberOfPoints;
    dataPoints.array = malloc(numberOfPoints * (sizeof(point_2d)));
	return dataPoints;
}

// destruction d'un tableau de points
void freeArrayPoints(arrayPoints* dataPoints){
    if(dataPoints->array != NULL){
		free(dataPoints->array);
		dataPoints->array = 0;
	}
	dataPoints->length = -1;
}

// création d'un tableau de points à partir d'une fonction
// donnée en paramètre
arrayPoints createArrayPointsFunction(double xBegin, double xEnd,  double step, double (*funct)(double)){
  	int size= (xEnd - xBegin) / step;
	arrayPoints dataPoints = createArrayPoints(size);
	for (int i = 0 ; i < size; i += 1){
		double x = xBegin + step * i;
        point_2d p = {x, funct(x)};
		dataPoints.array[i] = p;
	}
	return dataPoints;
}
