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
#include "optimisation.h"

// Création d'un point avec ses coordonnées
point_2d createPoint(double X, double Y){
    point_2d res = {X,Y};
    return res;
}

// Création d'un tableau de point_2d vide d'une taille de length
arrayPoints createArrayPoints(int length){
    arrayPoints res;
    res.length = length;
    res.array = malloc(sizeof(point_2d) * length);
    return res;
}

// Création d'un tableau de point_2d remplit de manière aléatoire
//    dans un intervalle délimité par minXY et maxXY
arrayPoints createRandomArrayPoints(int length,  point_2d minXY, point_2d maxXY){
    arrayPoints data;
    data.length = length;
    data.array = malloc(length * sizeof(point_2d));
    for(int i = 0; i < length; i++){
        double minX= minXY.x;
        double maxX= maxXY.x;
        double minY= minXY.y;
        double maxY= maxXY.y;
        double randX= (double) rand() / ((double) RAND_MAX + 1);
        randX= minX + randX * (maxX - minX);
        double randY= (double) rand() / ((double) RAND_MAX + 1);
        randY= minY + randY * (maxY - minY);
        data.array[i]= createPoint(randX,randY);
    }
    return data;
}

// Création d'un tableau de points représentant une droite sachant
//    son ordonnée à l'origine et son coefficient directeur. Le tableau contiendra "length" points.
arrayPoints createArrayPointsKnownStraightLine(int length, double a, double b){
	  arrayPoints data = createArrayPoints(length);
    for(int i = 0; i < length; i++){
        data.array[i] = createPoint(i,a*i+b);
    }
    return data;
}
// Création d'un tableau de points représentant une droite sur
//    laquelle on ajoute du bruit de manière aléatoire qui reste proche de la droite.
//      La valeur du bruit est comprise entre -maxNoise et +maxNoise.
arrayPoints createArrayPointsKnownStraightLineWithNoise(int length, double a, double b, double maxNoise){
    arrayPoints straightLine = createArrayPointsKnownStraightLine(length, a, b);
    for (int i= 0; i < length;i++){
      int randValue = rand() % ((int)maxNoise);
	    int sign = 1;
	    int randSign = rand() % 2;
	    if (randSign == 0){
			     sign = 1;
		  }else{
			     sign = -1;
		  }
		  straightLine.array[i].y += ((double)randValue * (double)sign);
	  }
    return straightLine;
}
// Destruction d'un tableau de point_2d
void freeArrayPoints(arrayPoints* data){
    free(data->array);
    data->array = NULL;
    data->length = -1;
}

// Obtention du coefficient directeur de la meilleure droite
//    d'un tableau de points (approche analytique)
double calculationCoefficientA(arrayPoints array){
    double n = array.length;
    double valueA= ( sum(array,Xi_Yi)*n - sum(array,Xi)*sum(array,Yi) ) / ( sum(array,Xi_Xi)*n - sum(array,Xi)*sum(array,Xi) );
    return valueA;
}

// Obtention de d'ordonnée à l'origine de la meilleure droite
//    d'un tableau de points (approche analytique)
double calculationCoefficientB(arrayPoints array, double a){
    double valueB= ( sum(array,Xi_Yi) - a*sum(array,Xi_Xi) ) / ( sum(array,Xi) );
    return valueB;
}

// Sum sur les points d'un tableau qui s'effectue selon
//    la fonction donnée en paramètre
double sum(arrayPoints data, double (*f)(point_2d)){
    double res = 0.0;
    for(int i = 0; i < data.length; i++){
        res += (*f)(data.array[i]);
    }
    return res;
}

//// fonctions utilitaires pour la somme ////
double Xi_Yi(point_2d point){
    return point.x * point.y;
}

double Xi_Xi(point_2d point){
    return point.x * point.x;
}

double Yi_Yi(point_2d point){
    return point.y * point.y;
}

double Xi(point_2d point){
    return point.x;
}

double Yi(point_2d point){
    return point.y;
}
//// fonctions utilitaires pour la somme ////

// Convertion d'un tableau de points_2d en un vecteur, utilisée pour l'affichage dans la librairie python
void convertArrayPointsToDoubleVector(arrayPoints arrayP, double_vector_t* vectorX, double_vector_t* vectorY){
	for (int i = 0; i < arrayP.length;i++){
      vectorX->components[i] = arrayP.array[i].x;
      vectorY->components[i] = arrayP.array[i].y;
  }
}

// Affichage d'un tableau de points
void printArrayPoints(arrayPoints data){
    for(int i = 0; i < data.length; i++){
        printf("%.2f,%.2f\n", data.array[i].x, data.array[i].y);
    }
}

// Exportation d'un tableau de points en un vecteur qui sera écrit
//    dans un fichier exploitable par la librairie python
void exportToVector(arrayPoints data, char* nameFileX, char* nameFileY){

	double_vector_t *arrayX = init_vector(data.length);
	double_vector_t *arrayY = init_vector(data.length);
	convertArrayPointsToDoubleVector(data, arrayX, arrayY);

  export_vector(nameFileX, arrayX);
  export_vector(nameFileY, arrayY);

  destroy_vector(&arrayX);
  destroy_vector(&arrayY);
}

// Calcul du gradient en un point donné parmis un tableau de points
point_2d gradientOnPoint(double a, double b, arrayPoints data){
    point_2d res = {0,0};
    res.x = 2.0 * (a * sum(data,Xi_Xi) + b * sum(data,Xi) - sum(data,Xi_Yi));
    res.y = 2.0 * (a * sum(data, Xi) + b * data.length - sum(data,Yi));
    return res;
}

// Retourne un point_2d ayant comme x la valeur de la pente, et comme y, l'ordonnée à l'origine.
//   Epsilon est la précision de la solution, arrayOfPoints le tableau de points, Xi le point de départ,
//   lambda le coefficient de descente (vitesse)
point_2d descenteGradient(double epsilon, arrayPoints arrayOfPoints, point_2d Xi, double lambda){
    double normeX = 0.0;
    double normeY = 0.0;
    normalizeArrayPoints(&arrayOfPoints, &normeX, &normeY);
	  double actualPrecision = 1.0;
    point_2d XiPlus1 = {0.0, 0.0};
	  while (actualPrecision > epsilon){
    		point_2d gradientOfXi = gradientOnPoint(Xi.x, Xi.y, arrayOfPoints);

    		XiPlus1.x = Xi.x - gradientOfXi.x * lambda;
    		XiPlus1.y = Xi.y -gradientOfXi.y * lambda;
        actualPrecision = sqrt(pow(XiPlus1.x - Xi.x,2) + pow(XiPlus1.y - Xi.y,2));
    		Xi = XiPlus1;
  	}
	  double aNormalized = Xi.x;
	  double bNormalized = Xi.y;

	  double xPredicted1 = rand()%1000;
    double xPredicted2 = rand()%1000;
    double yNormalized1 = aNormalized * (xPredicted1 / normeX) + bNormalized;
    double yNormalized2 = aNormalized * (xPredicted2 / normeX) + bNormalized;
    double yPredicted1 = yNormalized1 * normeY;
    double yPredicted2 = yNormalized2 * normeY;

    Xi.x = (yPredicted2 - yPredicted1) / (xPredicted2 - xPredicted1);
	  Xi.y = yPredicted1 - Xi.x * xPredicted1;

    denormalizeArrayPoints(&arrayOfPoints, normeX, normeY);

	  return Xi;
}

// Separe de manière aléatoire les données de data en trois sous tableaux de même tailles G1, G2, G3.
//    Ceux-ci doivent êtres alloués avant l'appel avec la bonne taille.
void separteArrayIntoGroups(arrayPoints data, arrayPoints* G1, arrayPoints* G2, arrayPoints* G3){
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    for(i = 0; i < data.length; i++){
        switch(rand() % 3){
            case 0:
                if(j < G1->length){
                    G1->array[j] = data.array[i];
                    j++;
                }else{
                    i--;
                }
                break;
            case 1:
                if(k < G2->length){
                    G2->array[k] = data.array[i];
                    k++;
                } else{
                    i--;
                }
                break;
            case 2:
                if(l < G3->length){
                    G3->array[l] = data.array[i];
                    l++;
                } else{
                    i--;
                }
                break;
        }
    }
}

// Retourne un nouveau tableau de points qui est la concaténation de arraySubSet1 et arraySubSet2
arrayPoints gatherTwoArray(arrayPoints arraySubSet1, arrayPoints arraySubSet2){
  int lengthResultArray=  arraySubSet1.length + arraySubSet2.length;
	arrayPoints arrayResult = createArrayPoints(lengthResultArray);
	for (int i = 0; i < arraySubSet1.length;i++){
		  arrayResult.array[i] = arraySubSet1.array[i];
	}
  for (int j = 0; j < arraySubSet2.length;j++){
		  arrayResult.array[j+ arraySubSet1.length] = arraySubSet2.array[j];
	}
	return arrayResult;
}

// Retourne une indication numérique sur la validité du modèle.
//    coeffA est la pente calculée , coeffB l'ordonnée à l'origine calculée et data le tableau de points.
int calculationErrorModel(double coeffA, double coeffB, arrayPoints dataPoints){
  	double errorSum = 0.0;
  	for (int i = 0; i < dataPoints.length; i++){
  		    double imageFromModel = coeffA * dataPoints.array[i].x + coeffB;
          errorSum+= (imageFromModel - dataPoints.array[i].y)* (imageFromModel - dataPoints.array[i].y);
  	}
    return errorSum;
}

// Normalise le vecteur x et y de data. La norme de X est stockée à l'adresse pointée par normeX. De même pour normeY
void normalizeArrayPoints(arrayPoints* data, double * normeX, double * normeY){
    *normeX = sqrt(sum(*data, Xi_Xi));
    *normeY = sqrt(sum(*data, Yi_Yi));
    for(int i = 0; i < data->length; i ++){
		    data->array[i].x = data->array[i].x / *normeX;
        data->array[i].y = data->array[i].y / *normeY;
    }
}

// Dénormalise le vecteur x et y de data. La valeur des normes doivent être donnés en paramètre.
void denormalizeArrayPoints(arrayPoints*data, double normeX, double normeY){
    for(int i = 0; i < data->length; i ++){
		    data->array[i].x = data->array[i].x * normeX;
        data->array[i].y = data->array[i].y * normeY;
    }
}


// Retourne le point_2d qui a la plus grande valeur en x de data
double highestXinArrayPoints(arrayPoints data){
    double highest = 0.0;
    double crt = 0.0;
    for(int i = 0; i < data.length; i++){
        crt = data.array[i].x;
        if(crt > highest){
            highest = crt;
        }
    }
    return highest;
}
