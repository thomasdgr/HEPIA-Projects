#include "integrales.h"

// calcul l'intégrale de la fonction donnée en paramètre avec
// la méthode du rectange à gauche 
double calculateIntegralLeftRectangle(double a, double b, int N, double (*funct)(double)){
	double resultIntegral = 0.0;
	double dx = (b - a) / (double) N;
	for (int i = 0; i < N - 1; i++){
		resultIntegral += funct(a + i * dx) * dx;
	}
	return resultIntegral;
}

// calcul l'intégrale de la fonction donnée en paramètre avec
// la méthode du trapèze 
double calculateIntegralTrapeze(double a, double b, int N, double (*funct)(double)){
	double resultIntegral = 0.0;
	double dx = (b - a) / (double) N;
	for (int i = 0; i < N - 1 ; i++){
		resultIntegral += ( (funct(a + i * dx + dx) + funct(a + i * dx)) * dx ) / 2;
	}
	return resultIntegral;
}

// calcul l'erreur connaissant la valeur exacte et la valeur approchée de l'intégrale
double errorIntegral(double exactValue, double approxValue){
	double E = ( exactValue - approxValue ) / exactValue;
	return E < 0 ? E * - 1.0 : E;
}

// calcul la convolution 
double convolution(double x, int N, double (*filter)(double),  double (*functToFilter)(double)){
  	double a = -50.0;
  	double b =  50.0;
  	double resultIntegral = 0.0;
	double dx = (b - a) / (double) N;
	for (int i = 0; i < N - 1; i++){
    	double yResult = functToFilter(a + i * dx) * filter(x -(a + i * dx));
		resultIntegral += yResult * dx;
	}
	return resultIntegral;
}

// calcul la valeur exacte pour la fonction f de l'ennoncé du tp
double exactIntegralValueWithF(double borneA, double borneB){
	double borneAAdjusted = borneA * borneA - borneA + 2.0;
    double borneBAdjusted = borneB * borneB - borneB + 2.0;
	return -1.0 * exp(-1.0 * borneAAdjusted) + exp(-1.0 * borneBAdjusted);
}

// effectuer la validation pour plusieurs valeurs de N

/*  double exactValue = exactIntegralValueWithF(a,b);
    printf("Valeure exacte: %.6f\n", exactValue);
    int NValues[] = {N, N*2, N*10, N*20, N*100, N*200};
    for(int i = 0; i < (int)(sizeof(NValues) / sizeof(NValues[0])); i++){
        printf("------N = %d------\n", NValues[i]);        
        double rectValue = calculateIntegralLeftRectangle(a, b, NValues[i], f);
		printf("\nRectangle à gauche: %.6f\n", rectValue);
	    printf("Erreur Rectangle: %.6f\n", errorIntegral(exactValue, rectValue));
        double trapValue = calculateIntegralTrapeze(a, b, NValues[i], f);
        printf("Trapèze: %.6f\n", trapValue);
	    printf("Erreur Trapèze: %.6f\n", errorIntegral(exactValue, trapValue));
    }*/

// fonction a filtrer (notée s(x) dans l'ennoncé)
double funcToFilter(double x){
    double omega1 = 1.0;
    double omega2 = 3.0;
    return sin(2.0 * M_PI * omega1 * x) + sin(2.0 * M_PI * omega2 * x);
}

// fonction de filtre (notée f(x) dans l'ennoncé)
double filterFunctionS(double x){
    double psi = 2.0;
    if( x >= (-psi / 2.0) && x <= (psi / 2.0)){
        return 1.0 / psi;
    }
    return 0;
}

// application de (s * f) (x)
double applyConvolutionS(double x){
    return convolution(x, 10000, filterFunctionS, funcToFilter);
}

// fonction attendue après la convolution (s * f) (x)
double funcFilteredS(double x){
    double omega2 = 3.0;
    return sin(2.0 * M_PI * omega2 * x);
}

// fonction de filtre (notée h(x) dans l'ennoncé)
double filterFunctionH(double x){
	double psi = 0.07; //2.0 / 1.5;
	return (1 / sqrt(2 * M_PI * psi)) * exp((-1 * x * x) / (2 * psi));
}

// application de (s * h) (x)
double applyConvolutionH(double x){
    return convolution(x, 10000, filterFunctionH, funcToFilter);
}

// création et exportation des tableaux de points pour la convolution (s * f) (x)
// afin d'afficher le résultat avec matplotlib
void filterValidationS(){
    arrayPoints dataFuncToFilter = createArrayPointsFunction(0,5, 0.001, funcToFilter);
    arrayPoints dataFuncConvolution = createArrayPointsFunction(0,5, 0.01, applyConvolutionS);
    arrayPoints dataFuncFiltered = createArrayPointsFunction(0,5, 0.001, funcFilteredS);

    exportArrayPointsToVector(dataFuncToFilter, "src/Python/funcToFilterX.vec", "src/Python/funcToFilterY.vec");
    exportArrayPointsToVector(dataFuncConvolution, "src/Python/funcConvolutionX.vec", "src/Python/funcConvolutionY.vec");
    exportArrayPointsToVector(dataFuncFiltered, "src/Python/funcFilteredX.vec", "src/Python/funcFilteredY.vec");

    freeArrayPoints(&dataFuncToFilter);
    freeArrayPoints(&dataFuncFiltered);
    freeArrayPoints(&dataFuncConvolution);
}

// création et exportation des tableaux de points pour la convolution (s * h) (x)
// afin d'afficher le résultat avec matplotlib
void filterValidationH(){
    arrayPoints dataFuncToFilter = createArrayPointsFunction(-2,2, 0.05, funcToFilter);
    arrayPoints dataFuncConvolution = createArrayPointsFunction(-2,2, 0.05, applyConvolutionH);
    arrayPoints dataFuncFilter = createArrayPointsFunction(-2,2, 0.05, filterFunctionH);

    exportArrayPointsToVector(dataFuncToFilter, "src/Python/funcToFilterX.vec", "src/Python/funcToFilterY.vec");
    exportArrayPointsToVector(dataFuncConvolution, "src/Python/funcConvolutionX.vec", "src/Python/funcConvolutionY.vec");
    exportArrayPointsToVector(dataFuncFilter, "src/Python/funcFilterX.vec", "src/Python/funcFilterY.vec");

    freeArrayPoints(&dataFuncToFilter);
    freeArrayPoints(&dataFuncConvolution);
	freeArrayPoints(&dataFuncFilter);
}