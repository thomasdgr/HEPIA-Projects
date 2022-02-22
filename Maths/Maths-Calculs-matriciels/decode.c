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

#include "matrix.h"

void factorisation(matrix *L, matrix *U){
    for(int i = 0; i < L->n; i++){
        if(U->data[i][i] != 0.0){
            for(int j = i+1; j < L->n; j++){
                double ratio = -U->data[j][i]/U->data[i][i];
                L->data[j][i] = -ratio;
                for(int k = 0; k < L->n; k++){
                    U->data[j][k] = U->data[j][k] +ratio*U->data[i][k];
                }
            }
        }else{
            printf("ERREUR !!\n");
            exit(0);
        }
    }
}

matrix create_under_matrix(matrix mat, int esquive_i, int esquive_j){
    int mSousMat= mat.m-1;
    int nSousMat= mat.n-1;
    double sousTab[mSousMat*nSousMat];
    int nombreElementsTab=0;

    for(int i=0;i<mat.m;i++){
        for(int j=0;j<mat.n;j++){
            if(i != esquive_i && j!= esquive_j){
                sousTab[nombreElementsTab]=mat.data[i][j];
                nombreElementsTab++;
            }
        }
    }
    matrix sousMat = matrix_create_from_array(mSousMat, nSousMat, sousTab);
    return sousMat;
}

double determinant(matrix mat){
    if(mat.m==2 && mat.n==2){
        double valDeterminant= mat.data[0][0]*mat.data[1][1] - mat.data[1][0]*mat.data[0][1];
        return valDeterminant;
    }else{
        double determinantMat=0.0;
        for(int j=0; j<mat.n;j++){
            int signe_j= pow(-1,2+j);
            matrix sousMat= create_under_matrix(mat,0,j);
            determinantMat+= mat.data[0][j]* signe_j * determinant(sousMat);
            matrix_destroy(&sousMat);
        }
        return determinantMat;
    }
}

matrix resolve_z(matrix M, matrix B){
    double X[B.m];
    double sum = 0.0;
    for(int i = 0; i < B.m; i++){
        for(int j = 0; j < i; j++){
            sum+= X[j] * M.data[i][j];
        }
        X[i] = (B.data[i][0] - sum) / M.data[i][i];
        sum = 0.0;
    }
    matrix mat = matrix_create_from_array(B.m, 1, X);
    return mat;
}

matrix resolve_x(matrix M, matrix Z){
    double X[Z.m];
    double sum = 0.0;
    for(int i = Z.m-1; i >= 0; i--){
        for(int j = Z.m-1; j > i; j--){
            sum+= X[j] * M.data[i][j];
        }
        X[i] = (Z.data[i][0] - sum) / M.data[i][i];
        sum = 0.0;
    }
    matrix mat = matrix_create_from_array(Z.m, 1, X);
    return mat;
}
