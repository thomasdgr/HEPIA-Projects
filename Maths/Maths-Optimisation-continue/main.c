/*****************************************************************************
		    ____
           /____ \         | Projet : TP sur l'optimisation continue
           | _ _`\|        |          dans le cadre du cours de maths
    .-.   `| O O |         | Auteurs : Quentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Optimisation avec une approche
 __/  |    | \__/|         |    analytique (recherche des coefficients)
(___) \.  _.\__. `\___     |    numérique (descente de gradients)
(___)  )\/  \_____/  ~\.   | Des tests sur un ensemble avec du bruit àléatoire
(___) . \   `         `\   |    permettent de valider le modèle ainsi qu'un
 (__)-    ,/        (   |  |    entrainement pour évaleur l'erreur.
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 13/11/2020

*****************************************************************************/
#include "optimisation/optimisation.h"

#define LENGTH 1000
#define LAMBDA 0.00001
#define EPSILON 0.0000000001

int main(){
  srand(time(NULL));

  point_2d lowest = createPoint(0.0, 0.0);
  point_2d highest = createPoint(10.0, 10.0);
  arrayPoints dataRandom = createRandomArrayPoints(LENGTH, lowest, highest);
  printf("\nTest avec des points aléatoires: ");

  printf("\nSolution analytique : ");
  double aRandom = calculationCoefficientA(dataRandom);
  double bRandom = calculationCoefficientB(dataRandom, aRandom);
  printf("a=%.2f, b=%.2f\n",aRandom, bRandom);

  printf("\nSolution numérique : ");
  point_2d Xi = createPoint(1.0, 1.0);
  point_2d res = descenteGradient(EPSILON, dataRandom, Xi, LAMBDA);
  printf("a=%.2f, b=%.2f\n", res.x, res.y);

  printf("\nTest avec du bruit : ");
	arrayPoints testValidationPoints = createArrayPointsKnownStraightLineWithNoise(LENGTH, 6.0, 15.0, 5.0);
	double aTestValidation= calculationCoefficientA(testValidationPoints);
  double bTestValidation= calculationCoefficientB(testValidationPoints, aTestValidation);
  double meanError = calculationErrorModel(aTestValidation, bTestValidation, testValidationPoints);
  printf("\n\tAnalytiquement: a=%.2f, b=%.2f, error=%.2f", aTestValidation, bTestValidation, meanError);

	Xi = createPoint(6.0, 14.0);
  point_2d gradientValidation2 = descenteGradient(EPSILON, testValidationPoints, Xi, LAMBDA);
  meanError = calculationErrorModel(gradientValidation2.x, gradientValidation2.y, testValidationPoints);
	printf("\n\tNumériquement:  a=%.2f, b=%.2f, error=%.2f\n", gradientValidation2.x, gradientValidation2.y, meanError);

  printf("\nEntrainement : ");
  arrayPoints G1 = createArrayPoints(LENGTH / 3);
	arrayPoints G2 = createArrayPoints(LENGTH / 3);
	arrayPoints G3 = createArrayPoints(LENGTH / 3 + LENGTH % 3);
  separteArrayIntoGroups(testValidationPoints, &G1, &G2, &G3);

  printf("\n\tG1 U G2 sur G3 : ");
	arrayPoints arrayConcat = gatherTwoArray(G1, G2);
  double aTraining = calculationCoefficientA(arrayConcat);
  double bTraining = calculationCoefficientB(arrayConcat, aTraining);
	double errorTraining = calculationErrorModel(aTraining, bTraining, G3);
	printf("a=%.2f, b=%.2f, error=%.2f\n", aTraining, bTraining, errorTraining);
	freeArrayPoints(&arrayConcat);

	printf("\tG1 U G3 sur G2 : ");
	arrayConcat = gatherTwoArray(G1, G3);
  aTraining = calculationCoefficientA(arrayConcat);
  bTraining = calculationCoefficientB(arrayConcat, aTraining);
	errorTraining = calculationErrorModel(aTraining, bTraining, G2);
	printf("a=%.2f, b=%.2f, error=%.2f\n", aTraining, bTraining, errorTraining);
	freeArrayPoints(&arrayConcat);

  printf("\tG2 U G3 sur G1 : ");
	arrayConcat = gatherTwoArray(G2, G3);
  aTraining = calculationCoefficientA(arrayConcat);
  bTraining = calculationCoefficientB(arrayConcat, aTraining);
	errorTraining = calculationErrorModel(aTraining, bTraining, G1);
	printf("a=%.2f, b=%.2f, error=%.2f\n", aTraining, bTraining, errorTraining);

  double highestX = highestXinArrayPoints(testValidationPoints);
	arrayPoints straightLineTest = createArrayPointsKnownStraightLine((int)highestX, aTestValidation, bTestValidation);
	exportToVector(testValidationPoints, "TestArrayPointsX.vec", "TestArrayPointsY.vec");
	exportToVector(straightLineTest, "TestLineX.vec", "TestLineY.vec");

  highestX = highestXinArrayPoints(dataRandom);
  arrayPoints straightLineRandom = createArrayPointsKnownStraightLine((int)highestX, aRandom, bRandom);
  exportToVector(dataRandom, "RandomArrayPointsX.vec", "RandomArrayPointsY.vec");
	exportToVector(straightLineRandom, "RandomLineX.vec", "RandomLineY.vec");

  freeArrayPoints(&straightLineRandom);
  freeArrayPoints(&straightLineTest);
	freeArrayPoints(&dataRandom);
	freeArrayPoints(&testValidationPoints);
  freeArrayPoints(&G1);
  freeArrayPoints(&G2);
  freeArrayPoints(&G3);
  freeArrayPoints(&arrayConcat);
}
