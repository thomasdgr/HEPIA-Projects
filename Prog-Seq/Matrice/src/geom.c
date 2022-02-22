/*******************************************************************************
			       ____
           /____ \               |  Projet : manipulation de matrices
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : librairie de fonctions
 __/  |    | \__/|               |  utilisées pour appliquer des transformations
(___) \.  _.\__. `\___           |  géometriques sur des matrices pgm
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	29/11/2019

\******************************************************************************/

#include "geom.h"

// modifications qui écrasent les données de la matrice transmise en paramètre

// applique une géometrie depuis l'axe vertical sur la matrice
int geom_vertical_axis_reflect_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    double tmp = 0;
    for (int i = 0; i < mat->n; i++) {
      for (int j = 0; j < (mat->m-1)/2; j++) {
        // swap des valeurs pour eviter le clone
        tmp = mat->data[i][j];
        mat->data[i][j] = mat->data[i][mat->n -1-j];
        mat->data[i][mat->n -1-j] = tmp;
      }
    }
    return 1;
  }
  return 0;
}

// applique une géometrie depuis l'axe hotizontal sur la matrice
int geom_horizontal_axis_reflect_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    double tmp = 0;
    for (int i = 0; i < (mat->n-1)/2; i++) {
      for (int j = 0; j < mat->m; j++) {
        // swap des valeurs pour eviter le clone
        tmp = mat->data[i][j];
        mat->data[i][j] = mat->data[mat->m -1-i][j];
        mat->data[mat->m -1-i][j] = tmp;
      }
    }
    return 1;
  }
  return 0;
}

// applique une géometrie depuis le centre de la matrice
int geom_central_reflect_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    // application des deux fonctions precedentes
    geom_horizontal_axis_reflect_in_place(mat);
    geom_vertical_axis_reflect_in_place(mat);
    return 1;
  }
  return 0;
}

// applique une rotation à partir d'un centre donné en paramètre
//et d'un angle en radian
int geom_rotate_in_place(matrix *mat, double angle, matrix center){
  if(matrix_is_valide(*mat) && matrix_is_valide(center)){
    matrix mat_clone = matrix_clone(*mat);
    for (int i = 0; i < mat->m; i++){
      for (int j = 0; j < mat->n; j++){
        // P = (x;y)
        double Px = i - center.data[0][0];
        double Py = j - center.data[0][1];
        // nouvelle position dans la matrice : P' = (x';y') par rapport au centre -> (0;0)
        double Px_final = round(((Px * cos(angle)) - (Py * sin(angle))) + center.data[0][0]);
        double Py_final = round(((Px * sin(angle)) + (Py * cos(angle))) + center.data[0][1]);
        // si on est dans la matrice ou pour remplire les trous avec des 0
        if (Px_final < 0.0 || Px_final >= mat->m || Py_final < 0.0 || Py_final >= mat->n){
          mat->data[i][j] = 0;
        } else{
          mat->data[i][j] = mat_clone.data[(int)Px_final][(int)Py_final];
        }
      }
    }
    matrix_destroy(&mat_clone);
    return 1;
  }
  return 0;
}

// applique le mode photomaton qui divise l'image en 4x4 plus petites.
//Pour faire un 8x8 on appelle 2x la fonction
int geom_photomaton_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    matrix mat_clone = matrix_clone(*mat);
    int i2 = 0;
    int j2 = 0;
    for (int i = 0; i < mat->m; i++) {
      for (int j = 0; j < mat->n; j++) {
        // les valeurs de une ligne sur deux et de une colonne sur deux
        //sont déplacées vers leurs positions finales
        if (i % 2 == 0){
          i2 = i / 2;
        } else {
          i2 = (mat->m / 2) + (i / 2);
        }
        if (j % 2 == 0){
          j2 = j / 2;
        } else {
          j2 = (mat->n / 2) + (j / 2);
        }
        mat_clone.data[i2][j2] = mat->data[i][j];
      }
    }
    // modifications appliquées dans une nouvelle matrice transfert des valeurs
    //intermediaires vers la matrice de départ pour executer le mode in_place
    *mat = transfert_clone_to_final(mat_clone, *mat);
    matrix_destroy(&mat_clone);
    return 1;
  }
  return 0;
}

// application d'une translation de l'image dans un sens
//et d'un nombre de pixels donné par la matrice translation
int geom_translate_in_place(matrix *mat, matrix translation){
  if(matrix_is_valide(*mat) && matrix_is_valide(translation)){
    matrix mat_clone = matrix_clone(*mat);
    // on remplie la matrice avec des 0
    matrix_mult_scalar_in_place(mat_clone, 0);
    int trans_m = translation.data[0][1];
    int trans_n = translation.data[0][0];
    for (int i = 0; i < mat->m; i++) {
      for (int j = 0; j < mat->n; j++) {
        // nouvelle position du point après translation
        int i2 = i + trans_m;
        int j2 = j + trans_n;
        // on vérifie qu'on est bien dans les limites de la matrice
        if(i2 >=0 && i2 < mat->m && j2 >= 0 && j2 < mat->n){
          mat_clone.data[i2][j2] = mat->data[i][j];
        }
      }
    }
    *mat = transfert_clone_to_final(mat_clone, *mat);
    matrix_destroy(&mat_clone);
    return 1;
  }
  return 0;
}

// application d'un zoom in ou zoom out
//selon les valeurs données à la matrice factors
int geom_zoom_in_place(matrix *mat, matrix factors){
  if(matrix_is_valide(*mat) && matrix_is_valide(factors)){
    double zoom_X = factors.data[0][1];
    double zoom_Y = factors.data[0][0];
    matrix  mat_clone = matrix_clone(*mat);
    // on multiplie ou divise chaque colonne et ligne par les valeurs de factors
    for (int i = 0; i < mat->m; i++){
      for (int j = 0; j < mat->n; j++){
        // on vérifie qu'on est bien dans les limites de la matrice
        if(j < (mat->n * zoom_Y) && i < (mat->m * zoom_X)){
          mat->data[i][j] = mat_clone.data[(int)(i/zoom_X)][(int)(j/zoom_Y)];
        } else {
          mat->data[i][j] = 0;
        }
      }
    }
    matrix_destroy(&mat_clone);
    return 1;
  }
  return 0;
}

// modifications appliquées dans une nouvelle matrice 

// on appelle les memes fonctions qui modifient les valeurs dans un clone
matrix geom_vertical_axis_reflect(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    geom_vertical_axis_reflect_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix geom_horizontal_axis_reflect(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    geom_horizontal_axis_reflect_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix geom_central_reflect(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    geom_central_reflect_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix geom_rotate(matrix mat, double angle, matrix center){
  if(matrix_is_valide(mat) && matrix_is_valide(center)){
    matrix newmat = matrix_clone(mat);
    geom_rotate_in_place(&newmat, angle, center);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix geom_photomaton(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    geom_photomaton_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix geom_translate(matrix mat, matrix translation){
  if(matrix_is_valide(mat) && matrix_is_valide(translation)){
    matrix newmat = matrix_clone(mat);
    geom_translate_in_place(&newmat, translation);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix geom_zoom(matrix mat, matrix factors){
  if(matrix_is_valide(mat) && matrix_is_valide(factors)){
    matrix newmat = matrix_clone(mat);
    geom_zoom_in_place(&newmat, factors);
    return newmat;
  }
  return matrix_default_value(mat);
}
