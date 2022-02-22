/*******************************************************************************
			       ____
           /____ \               |  Projet : manipulation de matrices
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : librairie de fonctions
 __/  |    | \__/|               |    utilisées pour appliquer des filtres
(___) \.  _.\__. `\___           |    sur des fichiers pgm
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	29/11/2019

\******************************************************************************/

#include "filter.h"

int apply_filter_in_place(matrix *mat, double array[], int kernel_m, int kernel_n){
  // création de la matrice kernel depuis le tableau
  matrix mat_kernel = matrix_create_from_array(kernel_m, kernel_n, array);
  // application des fonctions indispensables pour mettre un filtre
  // pas besoin de normaliser car on le fait deja dans pgm_read
  //et image.max = 1 donc normaliser par 1 ne sert à rien
  matrix_convolve_in_place(mat, mat_kernel);
  matrix_clipper_in_place(*mat);
  matrix_destroy(&mat_kernel);
  return 1;
}

// modifications qui écrasent les données de la matrice transmise en paramètre


// démo à faire pour in_place et sans :
//    double datamat[] = {-1.0, -1.0, -1.0,
//                    -1.0, 9.0, -1.0,
//                    -1.0, -1.0, -1.0};

// accentue l'effet de netteté de l'image
int filter_sharpen_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    // création du tableau qui correspond aux valeurs du kernel
    double datamat[] = {0.0, -1.0, 0.0,
                        -1.0, 5.0, -1.0,
                        0.0, -1.0, 0.0};
    apply_filter_in_place(mat, datamat,3,3);
    return 1;
  } else return 0;
}

// diminue la netteté de l'image (flou)
int filter_blur_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    double datamat[] = {1.0/9.0, 1.0/9.0, 1.0/9.0,
                      1.0/9.0, 1.0/9.0, 1.0/9.0,
                      1.0/9.0, 1.0/9.0, 1.0/9.0};
    apply_filter_in_place(mat, datamat,3,3);
    return 1;
  } else return 0;
}

// amméliore les contours détéctés dans l'image
int filter_edge_enhance_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    double datamat[] = {0.0, 0.0, 0.0,
                     -1.0, 1.0, 0.0,
                      0.0, 0.0, 0.0};
    apply_filter_in_place(mat, datamat,3,3);
    return 1;
  } else return 0;
}

// affiche uniquement les contours dans l'image
int filter_edge_detect_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    double datamat[] = {0.0, 1.0, 0.0,
                      1.0, -4.0, 1.0,
                      0.0, 1.0, 0.0};
    apply_filter_in_place(mat, datamat,3,3);
    return 1;
  } else return 0;
}

// augmente les reliefs dans l'image
int filter_emboss_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    double datamat[] = {-2.0, -1.0, 0.0,
                      -1.0, 1.0, 1.0,
                      0.0, 1.0, 2.0};
    apply_filter_in_place(mat, datamat,3,3);
    return 1;
  } else return 0;
}

// ajoutés
int filter_sobel_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    double datamat[] = {-1.0, -2.0, -1.0,
                      0.0, 0.0, 0.0,
                      1.0, 2.0, 1.0};
    apply_filter_in_place(mat, datamat,3,3);
    return 1;
  } else return 0;
}

int filter_smooth_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    double datamat[] = {1.0/16.0, 2.0/16.0, 1.0/16.0,
                      2.0/16.0, 4.0/16.0, 2.0/16.0,
                      1.0/16.0, 2.0/16.0, 1.0/16.0};
    apply_filter_in_place(mat, datamat,3,3);
    return 1;
  } else return 0;
}

// modifications appliquées dans une nouvelle matrice

// on appelle les memes fonctions qui modifient les valeurs dans un clone
matrix filter_sharpen(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    filter_sharpen_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix filter_blur(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    filter_blur_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix filter_edge_enhance(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    filter_edge_enhance_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix filter_edge_detect(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    filter_edge_detect_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix filter_emboss(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    filter_emboss_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

// ajoutés
matrix filter_sobel(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    filter_sobel_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix filter_smooth(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    filter_smooth_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}
