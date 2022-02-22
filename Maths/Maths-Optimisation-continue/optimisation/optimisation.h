/*****************************************************************************
		     ____
           /____ \         | Projet : TP sur l'optimisation continue
           | _ _`\|        |          dans le cadre du cours de maths
    .-.   `| O O |         | Auteurs : Quentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Fonctions utilisées pour la 
(___)  )\/  \_____/  ~\.   |                réalisation de ce travail pratique 
(___) . \   `         `\   |                sur l'optimisation.
 (__)-    ,/        (   |  |
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 13/11/2020

*****************************************************************************/
#ifndef OPTIMISATION_H
#define OPTIMISATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "../vector/vector.h"


typedef struct {
    double x,y;
} point_2d;

typedef struct {
    point_2d* array;
    int length;
} arrayPoints;

point_2d createPoint(double X, double Y);
arrayPoints createArrayPoints(int length);
arrayPoints createRandomArrayPoints(int length,  point_2d minXY, point_2d maxXY);
void freeArrayPoints(arrayPoints* data);
arrayPoints createArrayPointsKnownStraightLine(int length, double a, double b);
arrayPoints createArrayPointsKnownStraightLineWithNoise(int length, double a, double b, double maxNoise);
double calculationCoefficientA(arrayPoints array);
double calculationCoefficientB(arrayPoints array, double a);
double sum(arrayPoints data, double (*f)(point_2d));
double Xi_Yi(point_2d point);
double Xi_Xi(point_2d point);
double Yi_Yi(point_2d point);
double Xi(point_2d point);
double Yi(point_2d point);
void convertArrayPointsToDoubleVector(arrayPoints arrayP, double_vector_t* vectorX, double_vector_t* vectorY);
void printArrayPoints(arrayPoints data);
void exportToVector(arrayPoints data, char *nameFileX, char *nameFileY);
point_2d descenteGradient(double epsilon, arrayPoints arrayOfPoints, point_2d Xi, double lambda);
void separteArrayIntoGroups(arrayPoints data, arrayPoints* G1, arrayPoints* G2, arrayPoints* G3);
arrayPoints gatherTwoArray(arrayPoints arraySubSet1, arrayPoints arraySubSet2);
int calculationErrorModel(double coeffA, double coeffB, arrayPoints dataPoints);
void normalizeArrayPoints(arrayPoints *data, double *normeX, double* normeY);
void denormalizeArrayPoints(arrayPoints*data, double normeX, double normeY);
double highestXinArrayPoints(arrayPoints data);

#endif