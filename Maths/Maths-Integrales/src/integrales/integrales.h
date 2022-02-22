#ifndef INTEGRALES_H
#define INTEGRALES_H

#define _GNU_SOURCE
#define M_PI 3.14159265358979323846

#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "../arrayPoints/arrayPoints.h"
#include "../vector/vector.h"

double calculateIntegralLeftRectangle(double a, double b, int N, double (*funct)(double));

double calculateIntegralTrapeze(double a, double b, int N, double (*funct)(double));

double errorIntegral(double exactValue, double approxValue);

double convolution(double x, int N, double (*filter)(double),  double (*functToFilter)(double));

double convolutionSpecific(double psi, int N, double x, double (*func)(double));

double exactIntegralValueWithF(double borneA, double borneB);

double funcToFilter(double x);

double filterFunctionS(double x);

double applyConvolutionS(double x);

double funcFilteredS(double x);

double filterFunctionH(double x);

double applyConvolutionH(double x);

void filterValidationS();

void filterValidationH();

#endif
