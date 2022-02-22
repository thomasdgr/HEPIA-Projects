#include "matrix.h"

// créé un matrice en fonction de son nombre de ligne (m) et son nombre de colonne (n)
matrix matrix_create(int m, int n){
  matrix mat;
  // vérification de la validité
  if(m <= 0 || n<= 0){
    mat.m = -1;
    mat.n = -1;
    mat.data = NULL;
  }
    mat.m = m;
    mat.n = n;
    // on alloue les pointeurs des lignes (m)
    mat.data = malloc(m * sizeof(double*));
    // pour chaque ligne on a un tableau de valeurs (n fois)
    mat.data[0]= malloc(n * m * sizeof(double));

  for (int i = 0; i < m; i++) {
    // chaque ligne pointe vers une partie successive et contigue de taille n du tableau m*n
    mat.data[i] = mat.data[0] + i * n;
  }
  return mat;
}

// détruit une matrice donnée en paramètre
void matrix_destroy(matrix *mat){
  // on libere les pointeurs successifs vers les valeurs
  free(mat->data[0]);
  // on libere les valeurs
  free(mat->data);
  // reset par defaut
  mat->m = -1;
  mat->n = -1;
  mat->data = NULL;
}
// reset de la matrice pour identifier une erreur
matrix matrix_default_value(matrix mat){
  mat.m = -1;
  mat.n = -1;
  mat.data = NULL;
  return mat;
}

// verification de la validité d'une matrice
bool matrix_is_valide(matrix mat){
    if(mat.m <= 0 || mat.n <= 0 || mat.data == NULL){
    mat = matrix_default_value(mat);
    return false;
  }
  return true;
}

// créé un matrice à partir d'un tableau donné en paramètre
matrix matrix_create_from_array(int m, int n, double data[]){
  matrix mat = matrix_create(m,n);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      // on ajoute chaque valeur à la matrice comme à la création
      mat.data[i][j]= data[i * n + j];
    }
  }
  return mat;
}

// clonage d'une matrice
matrix matrix_clone(matrix mat){
  if(matrix_is_valide(mat)){
    matrix mat_clone = matrix_create(mat.m, mat.n);
    for(int i = 0; i < mat_clone.m; i++) {
      for(int k = 0; k < mat_clone.n; k++) {
        // les valeurs de l'ancienne matrice sont stockees dans la nouvelle
        mat_clone.data[i][k] = mat.data[i][k];
      }
    }
    return mat_clone;
  }
  return matrix_default_value(mat);
}

// transfère les valeurs de mat_clone dans mat_final -> utile pour les fonctions in_place
matrix transfert_clone_to_final(matrix mat_clone, matrix mat_final){
  if(mat_clone.n == mat_final.n && mat_clone.m == mat_final.m && matrix_is_valide(mat_clone) && matrix_is_valide(mat_final)){
    for (int i = 0; i < mat_clone.m; i++) {
      for (int j = 0; j < mat_clone.n; j++) {
        mat_final.data[i][j] = mat_clone.data[i][j];
      }
    }
    return mat_final;
  }
   return matrix_default_value(mat_final);
}

// affichage d'une matrice
void matrix_print(matrix mat){
  if(matrix_is_valide(mat)){
    printf("\n");
    for (int i = 0; i < mat.m ; i++) {
      printf("\t");
      for (int j = 0; j < mat.n; j++) {
        // deux decimales lors de l'affichage
        printf(" %.2f ", (double)mat.data[i][j]);
      }
    printf("\n");
    }
  }
}

// redimensionnement d'une matrice sans realloc() car plus efficace au nombre d'oppérations à faire
int matrix_resize(matrix *mat, int m, int n){
  if((n <= 0 || m <= 0) && matrix_is_valide(*mat)){
    return 0;
  }
  // on cree une nouvelle matrice avec la bonne taille
  matrix mat_resize = matrix_create(m,n);
  for(int i = 0; i < mat_resize.m; i++) {
    for(int j = 0; j < mat_resize.n; j++) {
      if(i < mat->m && j < mat->n){
        // on met les anciennes valeurs dans la nouvelle matrice
        mat_resize.data[i][j] = (mat->data)[i][j];
      }
      else{
        mat_resize.data[i][j] = 0;
      }
    }
  }
  // on detruit l'ancienne matrice
  matrix_destroy(mat);
  mat->data = mat_resize.data;
  mat->m = mat_resize.m;
  mat->n = mat_resize.n;
  return 1;
}

// vérification aproximative (selon epsilon) de l'égalité entre 2 matrices données en paramètre
bool matrix_is_approx_equal(matrix mat1, matrix mat2, double epsilon){
  bool mat_equal = false;
  double ecart;
  if(mat1.n == mat2.n && mat1.m == mat2.m && epsilon > 0 && matrix_is_valide(mat1) && matrix_is_valide(mat2)){
    mat_equal = true;
    for (int i = 0; i < mat1.m; i++) {
      for (int j = 0; j < mat1.n; j++) {
        if(mat2.data[i][j] < mat1.data[i][j]){
          ecart = mat1.data[i][j] - mat2.data[i][j];
        } else {
          ecart = mat2.data[i][j] - mat1.data[i][j];
        }
        if(ecart >= epsilon){
          mat_equal = false;
          return mat_equal;
        }
      }
    }
  }
  return mat_equal;
}

// regarde si deux matrices sont parfaitement égales
bool matrix_is_equal(matrix mat1, matrix mat2){
  if(mat1.m == mat2.m && mat1.n == mat2.n && matrix_is_valide(mat1) && matrix_is_valide(mat2)){
    for (int i = 0; i < mat1.m; i++){
      for (int j = 0; j < mat1.n; j++){
        if (mat1.data[i][j] != mat2.data[i][j]){
          return false;
        }
      }
    }
    return true;
  }
  return false;
}

/////////////////// modifications qui écrasent les données de la matrice (ou mat1) transmise en paramètre ///////////////////

// somme de deux matrices
int matrix_add_in_place(matrix mat1, matrix mat2){
  if(mat1.n == mat2.n && mat1.m == mat2.m && matrix_is_valide(mat1) && matrix_is_valide(mat2)){
    for (int i = 0; i < mat1.m; i++) {
      for (int j = 0 ; j < mat1.n; j++) {
        // on prend les valeurs situées a la meme position et on les aditionne
         mat1.data[i][j] = mat1.data[i][j] + mat2.data[i][j];
      }
    }
    return 1;
  }
  return 0;
}

// soustraction de deux matrices
int matrix_sub_in_place(matrix mat1, matrix mat2){
  if(mat1.n == mat2.n && mat1.m == mat2.m && matrix_is_valide(mat1) && matrix_is_valide(mat2)){
  for (int i = 0; i < mat1.m; i++) {
      for (int j = 0 ; j < mat1.n; j++) {
        // on prend les valeurs situées a la meme position et on les soustrait
         mat1.data[i][j] = mat1.data[i][j] - mat2.data[i][j];
      }
    }
    return 1;
  }
  return 0;
}

// multiplication de deux matrices
int matrix_mult_in_place(matrix *mat1, matrix mat2){
  if(mat1->n == mat2.m && matrix_is_valide(*mat1) && matrix_is_valide(mat2)){
    int sum = 0;
    matrix mult = matrix_create(mat1->m, mat2.n);
    for (int i = 0; i < mat1->m; i++) {
      for (int j = 0; j < mat2.n; j++) {
        for (int k = 0; k < mat2.m; k++) {
          // on somme les multiplications des lignes de A par les colonnes de B
          sum = sum + mat1->data[i][k] * mat2.data[k][j];
        }
        mult.data[i][j] = sum;
        sum = 0;
      }
    }
    // dans cette operation, la taille de la matrice sera A.m *B.n
    matrix_resize(mat1, mult.m, mult.n);
    transfert_clone_to_final(mult, *mat1);
    matrix_destroy(&mult);
    return 1;
  }
  return 0;
}

// addition d'une matrice par une constante
int matrix_add_scalar_in_place(matrix mat, double n){
  if(matrix_is_valide(mat)){
    for(int i = 0; i < mat.m; i++){
      for(int j = 0; j < mat.n; j++){
        // ajoute dans mat la somme par un nombre
        mat.data[i][j] = n + mat.data[i][j];
      }
    }
    return 1;
  }
  return 0;
}

// multiplication d'une matrice par une constante
int matrix_mult_scalar_in_place(matrix mat, double n){
  if(matrix_is_valide(mat)){
    for(int i = 0; i < mat.m; i++){
      for(int j = 0; j < mat.n; j++){
        // ajouter dans mat la multiplication par un nombre
        mat.data[i][j] = n * mat.data[i][j];
      }
    }
    return 1;
  }
  return 0;
}

// echanger les lignes et les colonnes d'une matrice
int matrix_transpose_in_place(matrix *mat){
  if(matrix_is_valide(*mat)){
    matrix transpose = matrix_create(mat->n, mat->m);
    for (int i = 0; i < mat->m; i++){
      for(int j = 0 ; j < mat->n ; j++ ){
        // on stock les valeurs dans un clone
        transpose.data[j][i] = mat->data[i][j];
      }
    }
    matrix_resize(mat, transpose.m, transpose.n);
    transfert_clone_to_final(transpose, *mat);
    matrix_destroy(&transpose);
    return 1;
  }
  return 0;
}

// division de toutes les valeurs par la valeur max
int matrix_normalize_in_place(matrix mat){
  if(matrix_is_valide(mat)){
    double max_value = 0;
    // on cherche la valeur max
    for(int i=0; i<mat.m; i++){
      for(int j=0; j<mat.n; j++){
        if(mat.data[i][j] < 0){
          // valeur absolue
          mat.data[i][j] = mat.data[i][j] < 0 ? mat.data[i][j] * - 1.0 : mat.data[i][j];
        }
        if (mat.data[i][j] > max_value){
          max_value = mat.data[i][j];
        }
      }
    }
    // on divise chaque valeur par le max
    for(int i=0; i<mat.m; i++){
      for(int j=0; j<mat.n; j++){
        mat.data[i][j] = mat.data[i][j] / max_value;
      }
    }
    return 1;
  }
  return 0;
}

// toutes les valeurs de la matrice sont comprises entre 0 et 1
int matrix_clipper_in_place(matrix mat){
  if(matrix_is_valide(mat)){
    for (int i = 0; i < mat.m; i++) {
        for (int j = 0 ; j < mat.n; j++) {
          if(mat.data[i][j] < 0){
            mat.data[i][j] = 0;
          } else if (mat.data[i][j] > 1) {
            mat.data[i][j] = 1;
          }
        }
    }
    return 1;
  }
  return 0;
}

int matrix_convolve_in_place(matrix *mat, matrix kernel){
  if(matrix_is_valide(*mat) && matrix_is_valide(kernel)){
    matrix mat1 = matrix_clone(*mat);
    double somme = 0;
    // on trouve le centre du kernel
    int Kx = kernel.m / 2;
    int Ky = kernel.n / 2;
    // pour chaque valeur de la matrice on veut faire un somme de multiplication de mat.nm avec kernel.nm
    for (int i = 0; i < mat1.m; i++){
      for (int j = 0; j < mat1.n; j++){
        for (int k = 0; k < kernel.m; k++){
          for (int l = 0; l < kernel.n; l++){
            // on verifie que les valeurs du kernel sont superposables avec les valeurs de la matrice
            if((i-Kx+k) < mat1.m && (i-Kx+k) >= 0 && (j-Ky+l) < mat1.n && (j-Ky+l) >= 0){
              somme += (double)kernel.data[k][l] * (double)mat1.data[(i-Kx+k)][(j-Ky+l)];
            }
          }
        }
        mat->data[i][j] = somme;
        somme = 0;
      }
    }
    matrix_destroy(&mat1);
    return 1;
  }
  return 0;
}

/////////////////// modifications appliquées dans une nouvelle matrice ///////////////////

// finir d'utiliser is_valide et _default_value

matrix matrix_add(matrix mat1, matrix mat2){
  if(mat1.n == mat2.n && mat1.m == mat2.m && matrix_is_valide(mat1) && matrix_is_valide(mat2)){
    matrix newmat = matrix_clone(mat1);
    matrix_add_in_place(newmat, mat2);
    return newmat;
  }
    return matrix_default_value(mat1);
}

matrix matrix_sub(matrix mat1, matrix mat2){
  if(mat1.n == mat2.n && mat1.m == mat2.m && matrix_is_valide(mat1) && matrix_is_valide(mat2)){
    matrix newmat = matrix_clone(mat1);
    matrix_sub_in_place(newmat, mat2);
    return newmat;
  }
    return matrix_default_value(mat1);
  //return matrix_add(mat1,matrix_mult_scalar(mat2,-1));
}

matrix matrix_mult(matrix mat1, matrix mat2){
  if(mat1.n == mat2.m && matrix_is_valide(mat1) && matrix_is_valide(mat2)){
    matrix newmat = matrix_clone(mat1);
    matrix_mult_in_place(&newmat, mat2);
    return newmat;
  }
  return matrix_default_value(mat1);
}

matrix matrix_add_scalar(matrix mat, double n){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    matrix_add_scalar_in_place(newmat, n);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix matrix_mult_scalar(matrix mat, double n){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    matrix_mult_scalar_in_place(newmat, n);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix matrix_transpose(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    matrix_transpose_in_place(&newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix matrix_normalize(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    matrix_normalize_in_place(newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix matrix_clipper(matrix mat){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    matrix_clipper_in_place(newmat);
    return newmat;
  }
  return matrix_default_value(mat);
}

matrix matrix_convolve(matrix mat, matrix kernel){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    matrix_convolve_in_place(&newmat, kernel);
    return newmat;
  }
  return matrix_default_value(mat);
}

// ajoutés pour le tp de convolution

// suppression des *sizes* premieres et dernieres lignes et colonnes de la matrice
matrix matrix_crop(matrix mat, int size){
  if(matrix_is_valide(mat)){
    matrix newmat = matrix_clone(mat);
    matrix_resize(&newmat, newmat.m - (size*2), newmat.n - (size*2));
    for(int i = 0; i < newmat.m; i++){
      for(int j = 0; j < newmat.n; j++){
        int newI = i + size;
        int newJ = j + size;
        if( (newI < 0) || (newJ < 0) || (newI > (mat.m - 1)) || (newJ > (mat.n - 1)) ){
          newmat.data[i][j] = 0;
        } else{
          newmat.data[i][j] = mat.data[newI][newJ];
        }
      }
    }
    return newmat;
  }
  return matrix_default_value(mat);
}

// retourne la valeur max d'une matrice
double matrix_max_value(matrix mat){
  double max = 0.0;
  for(int i = 0; i < mat.m; i++){
    for(int j = 0; j < mat.n; j++){
      if (mat.data[i][j] > max){
        max = mat.data[i][j];
      }
    }
  }
  return max;
}

// retourne la valeur min d'une matrice
double matrix_min_value(matrix mat){
  double min = mat.data[0][0];
  for(int i = 0; i < mat.m; i++){
    for(int j = 0; j < mat.n; j++){
      if (mat.data[i][j] < min){
        min = mat.data[i][j];
      }
    }
  }
  return min;
}

// conversion d'une matrice en 8 bits pour l'affichage avec sdl2
void matrix_convert_in_eight_bits_in_place(matrix mat){
	double maxValue = matrix_max_value(mat);
	double minValue = matrix_min_value(mat);
	for (int i = 0; i < mat.m; i++){
		for (int j = 0; j < mat.n; j++){
			mat.data[i][j] = (mat.data[i][j] - minValue) / (maxValue - minValue); // * 1
		}
	}
}