/*******************************************************************************
			      ____
           /____ \               |  Projet : TP Système d'équation matriciel
           | _ _`\|              |
    .-.   `| O O |               |  Auteurs : Thomas Dagier, Gustavo Pertuzati, Quentin Rod
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : résoudre l'équation matrice_A * vecteur_X = matrice_B
 __/  |    | \__/|               |                 en suivant les notions abordées en cours à partir d'une
(___) \.  _.\__. `\___           |                 librairie de matrice créée dans le TP de Prog Séqu
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |  Executer le projet avec la commande "make" dans le terminal
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	30/04/2020
\******************************************************************************/

#include "decode.h"

int main(){
  double A[] = {203.000, 272.000, 355.000, 545.000, 577.000, 1000.000, 754.000, 518.000, 529.000, 862.000,
                118.000, 158.000, 206.000, 316.000, 335.000, 580.000 , 438.000, 301.000, 307.000, 500.000,
                 10.000,  13.000,  18.000,  27.000,  29.000,  51.000 ,  38.000,  26.000,  27.000,  43.000,
                 63.000,  85.000, 110.000, 170.000, 180.000, 312.000 , 235.000, 161.000, 165.000, 269.000,
                122.000, 163.000, 213.000, 327.000, 347.000, 601.000 , 453.000, 311.000, 318.000, 518.000,
                 61.000,  82.000, 107.000, 165.000, 175.000, 303.000 , 228.000, 157.000, 160.000, 261.000,
                 26.000,  35.000,  46.000,  71.000,  75.000, 130.000 ,  98.000,  67.000,  68.000, 112.000,
                 75.000, 100.000, 131.000, 201.000, 213.000, 369.000 , 278.000, 191.000, 195.000, 318.000,
                 54.000,  72.000,  94.000, 144.000, 152.000, 264.000 , 199.000, 137.000, 139.000, 227.000,
                 13.000,  18.000,  23.000,  36.000,  38.000,  66.000 ,  50.000,  34.000,  35.000,  57.000};

  double B[] = { 47.000,
                 51.000,
                -66.000,
                 91.000,
                -68.000,
                -57.000,
                -72.000,
                -71.000,
                -53.000,
                 13.000};

  matrix matA = matrix_create_from_array(10, 10, A);
  matrix matB = matrix_create_from_array(matA.m, 1, B);

  double val_determinant = determinant(matA);
  printf("determinant = %f\nEst-ce que A est inversible ? ",val_determinant);
  printf((val_determinant != 0) ? "oui\n" : "non\n");
  if(val_determinant!=0){
    matrix matU = matrix_clone(matA);
    matrix matL = matrix_create_identity_matrix(matA.m, matA.n);

    factorisation(&matL, &matU);
    printf("\nEst-ce que L * U vaut bien A ? ");
    matrix verifA = matrix_mult(matL, matU);
    printf(matrix_is_approx_equal(matA, verifA, 0.1) ? "oui\n" : "non\n");

    matrix matZ = resolve_z(matL, matB);
    matrix matX = resolve_x(matU, matZ);
    printf("\nEst-ce que A * X vaut bien B ? ");
    matrix verifB = matrix_mult(matA, matX);
    printf(matrix_is_approx_equal(matB, verifB, 0.1) ? "oui\n" : "non\n");
    printf("\nValeurs de la matrice X:");
    matrix_print(matX);

    matrix_destroy(&matU);
    matrix_destroy(&matL);
    matrix_destroy(&matZ);
    matrix_destroy(&matX);
    matrix_destroy(&verifA);
    matrix_destroy(&verifB);
  }else{
    printf("La résolution ne peut être effectuée car la matrice n'est pas inversible.");
  }


  matrix_destroy(&matA);
  matrix_destroy(&matB);


  return 0;
}
