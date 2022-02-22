#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>


// cette fonction crée une matrix de taille m*n, retourne une matrix vailde ou un matrix failed
matrix matrix_create(int m, int n)
{
  if (m < 1 || n < 1)
  {
    matrix failed;
    failed.data = NULL;
    failed.m = -1;
    failed.n = -1;
    return failed;
  }
  // on stocke les valeurs de notre matrix dans la mémoire de façon continue
  double **matrix_data = malloc(m* sizeof(double*)); //alloue une place dans la mémoire de taille m, pour stocker les adresses des début des lignes
  double *zone_matrix = malloc(m*n *sizeof(double)); // alloue une place dans la mémoire de taille m*n, pour stocker les valeurs de notre matrix

  if(matrix_data == NULL)
  {
    exit(0);
  }

  for (int i = 0; i < m; i++)
  {
    matrix_data[i] = &zone_matrix[n*i]; // stocke dans matrix_data les addresses des début lignes, n représentes les colonnes
  }

  //initialise tous les valeurs à 0
  for (int i = 0; i < m; i++)
   {
    for (int j = 0; j < n; j++)
    {
      matrix_data[i][j] = 0;
    }
  }

  matrix mat;
  mat.m = m;
  mat.n = n;
  mat.data = matrix_data;
  return mat;
}

// cette fonction libère de la mémoire la zone alloué pour stocké la matrix. elle met aussi la matrix comme invalide
void matrix_destroy(matrix *mat)
{
  mat->m = -1;
  mat->n = -1;
  free(*mat->data); //on libère la zone où on stocke tous les datas de la matrix
  free(mat->data);//on libère la zone où on stocke tous les addresses des lignes
  mat->data = NULL;
}

// cette fonction crée une matrix de taille m*n à partir d'un tableau de valeur, retourne une matrix vailde ou un matrix failed
matrix matrix_create_from_array(int m, int n, double data[])
{
  if(data == NULL)
  {
    matrix failed = matrix_create(-1,-1);
    return failed;
  }
    matrix mat = matrix_create(m,n);
    int temp = 0;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        mat.data[i][j] = data[temp];
        temp++;
      }
    }
    return mat;
}

// cette fonction clone une matrix en paramètre, retourne une matrix vailde ou un matrix failed
matrix matrix_clone(matrix mat)
{
    if(matrix_legal(mat))
    {
      matrix failed = matrix_create(-1,-1);
      return failed;
    }
    else
    {
      matrix newmat = matrix_create(mat.m, mat.n);
      for (int i = 0; i < mat.m; i++)
      {
        for (int j = 0; j < mat.n; j++)
        {
          newmat.data[i][j] = mat.data[i][j];
        }
      }
      return newmat;
    }
}

// cette fonction affiche une matrix en paramètre
void matrix_print(matrix mat)
{
  //affichage des valeurs de la matrice stockée dans la mémoire
  printf("la matrice: \n");
  for (int i = 0; i < mat.m; i++)
  {
    for (int j = 0; j < mat.n; j++)
    {
      printf("%f ", mat.data[i][j] );
    }
    printf("\n");
  }
  printf("\n");printf("\n");
}

// cette fonction redimmensionne une matrix avec m et n
int matrix_resize(matrix *mat, int m, int n)
{
  if(m< 1 || n< 1 || matrix_legal(*mat))
  {
    return 0;
  }
  else
  {
    matrix temp_mat = matrix_clone(*mat);

    mat->data = realloc(mat->data, m * sizeof(double*)); //réalloue la mémoire à laquelle on stocke les addresses des débuts des lignes
    *(mat->data) = realloc(*(mat->data), m*n * sizeof(double)); //réalloue la mémoire à laquelle on stocke les valeurs de la matrix

    // on redirige les pointeurs
    for (int i = 0; i < m; i++)
    {
      mat->data[i] = mat->data[0] + n*i;
    }

    //réinitialise à zéro la matrix
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        mat->data[i][j] = 0.0;
      }
    }
    //on va remettre les valeurs originales à laquelle on a stocké avec la matrix clone: temp_mat dans la nouvelle matrix avec les nouvelles dimmensions
    // pour remettre les valeurs originales, on parcourt la matrix qui a les dimmensions les plus petits, donc c'est soit la matrix cloné ou la matrix réallouée
    // cette étape nous évite de sortir de la matrix qui a les dimmensions les plus petites lorsqu'on remet les valeurs
    int temp_ligne;
    int temp_colonne;
    if(m < mat->m)
    {temp_ligne = m;}
    else
    {temp_ligne = mat->m;}
    if(n < mat->n)
    {temp_colonne = n;}
    else
    {temp_colonne = mat->n;}

    // là, on remet les valeurs originales dans la matrix réallouée
    for (int i = 0; i < temp_ligne; i++)
    {
      for (int j = 0; j < temp_colonne; j++)
      {
        mat->data[i][j] = temp_mat.data[i][j];
      }
    }

    mat->m = m;
    mat->n = n;
    matrix_destroy(&temp_mat);
    return 1;
  }
}

// cette fonction vérifie si deux matrix : mat1 et mat 2 sont égaux avec une epsilon, retourne true si égaux, false non égaux
bool matrix_is_approx_equal(matrix mat1, matrix mat2, double epsilon)
{
  double ep_max = 0.0;
  double ep_min = 0.0;

  if(mat1.m == mat2.m && mat1.n == mat2.n && epsilon > 0)
  {
    for (int i = 0; i < mat1.m; i++)
    {
      for (int j = 0; j < mat1.n; j++)
      {
        ep_max = mat2.data[i][j]+epsilon;
        ep_min = mat2.data[i][j]-epsilon;
        if (mat1.data[i][j] > ep_max || mat1.data[i][j] < ep_min)
        {
          return false;
        }
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}

// cette fonction vérifie si deux matrix : mat1 et mat2 sont égaux, retourne true si égaux, false non égaux
bool matrix_is_equal(matrix mat1, matrix mat2)
{
  if(mat1.n == mat2.n && mat1.m == mat2.m)
  {
    for (int i = 0; i < mat1.m; i++)
    {
      for (int j = 0; j < mat1.n; j++)
      {
        if (mat1.data[i][j] != mat2.data[i][j])
        {
          return false;
        }
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}

// cette fonction additionne 2 matrix: mat1 et mat2
int matrix_add_in_place(matrix mat1, matrix mat2)
{
  if (mat2.m != mat1.m || mat2.n != mat1.n || matrix_legal(mat1) || matrix_legal(mat2))
  {
    return 0;
  }
  else
  {
    for (int i = 0; i < mat2.m; i++)
    {
      for (int j = 0; j < mat2.n; j++)
      {
        mat1.data[i][j] += mat2.data[i][j];
      }
    }
    return 1;
  }
}

// cette fonction soustrait 2 matrix: mat1 et mat2
int matrix_sub_in_place(matrix mat1, matrix mat2)
{
  matrix_mult_scalar_in_place(mat2, -1);
  return matrix_add_in_place(mat1, mat2);
}

// cette fonction multiplie 2 matrix: mat1 et mat2
int matrix_mult_in_place(matrix *mat1, matrix mat2)
{
  if (mat1->n != mat2.m || matrix_legal(*mat1) || matrix_legal(mat2))
  {
    return 0;
  }

    matrix mat_temp = matrix_clone(*mat1);
    matrix_resize(mat1, mat1->m, mat2.n);
    for (int i = 0; i < mat1->m; i++)
    {
      for (int j = 0; j < mat1->n; j++)
      {
        mat1->data[i][j] = 0.0;
        for (int k = 0; k < mat_temp.n; k++)
        {
          mat1->data[i][j] += (mat_temp.data[i][k] * mat2.data[k][j]);
        }
      }
    }
    matrix_destroy(&mat_temp);
    return 1;
}

// cette fonction additionne un matrix: mat1 à un scalaire: n
int matrix_add_scalar_in_place(matrix mat1, double n)
{
  if(matrix_legal(mat1))
  {
    return 0;
  }
  for (int i = 0; i < mat1.m; i++)
  {
    for (int j = 0; j < mat1.n; j++)
    {
      mat1.data[i][j] += n;
    }
  }
  return 1;
}

// cette fonction multiplie un matrix: mat1 à un scalaire: n
int matrix_mult_scalar_in_place(matrix mat1, double n)
{
  if(matrix_legal(mat1))
  {
    return 0;
  }
  for (int i = 0; i < mat1.m; i++)
  {
    for (int j = 0; j < mat1.n; j++)
    {
      mat1.data[i][j] *= n;
    }
  }
  return 1;
}

// cette fonction applique une transpose à la matrix mat passée en paramètre
int matrix_transpose_in_place(matrix *mat)
{
  if(matrix_legal(*mat))
  {
    return 0;
  }
  matrix mat_temp = matrix_clone(*mat);
  matrix_resize(mat, mat->n, mat->m);

  for (int i = 0; i < mat->m; i++)
  {
    for (int j = 0; j < mat->n; j++)
    {
      mat->data[i][j] = mat_temp.data[j][i];
    }
  }
  matrix_destroy(&mat_temp);
  return 1;
}

// cette fonction met les valeurs de la matrix: mat entre 0 et 1
int matrix_normalize_in_place(matrix mat)
{
  if(matrix_legal(mat))
  {
    return 0;
  }
  else
  {
    double v_max = 0.0;
    // cherche la valeur maximum
    for (int i = 0; i < mat.m; i++)
    {
      for (int j = 0; j < mat.n; j++)
      {
        if(v_max < mat.data[i][j])
        {
          v_max = mat.data[i][j];
        }
      }
    }
    matrix_mult_scalar_in_place(mat, (1.0/v_max));
    return 1;
  }
}

// cette fonction met les valeurs de la matrix à 0.0 si ils sont négatives, à 1.0 si ils dépassent 1.0
int matrix_clipper_in_place(matrix mat)
{
  if(matrix_legal(mat))
  {
    return 0;
  }
  else
  {
    for (int i = 0; i < mat.m; i++)
    {
      for (int j = 0; j < mat.n; j++)
      {
        if(mat.data[i][j] < 0.0)
        {
          mat.data[i][j] = 0.0;
        }
        else if(mat.data[i][j] > 1.0)
        {
          mat.data[i][j] = 1.0;
        }
      }
    }
    return 1;
  }
}

// cette fonction clone la matrix mat en paramètre, et elle applique la fonction matrix_add_in_place au clone, elle retourne la matrix clonée.
matrix matrix_add(matrix mat1, matrix mat2)
{
  if (mat2.m != mat1.m || mat2.n != mat1.n || matrix_legal(mat1) || matrix_legal(mat2))
  {
    matrix failed = matrix_create(-1,-1);
    return failed;
  }
    matrix mat_resultat = matrix_clone(mat1);
    matrix_add_in_place(mat_resultat, mat2);
    return mat_resultat;
}

// cette fonction clone la matrix mat en paramètre, et elle applique la fonction matrix_sub_in_place au clone, elle retourne la matrix clonée.
matrix matrix_sub(matrix mat1, matrix mat2)
{
  matrix_mult_scalar_in_place(mat2,-1);
  return matrix_add(mat1, mat2);
}

// cette fonction clone la matrix mat en paramètre, et elle applique la fonction matrix_mult_in_place au clone, elle retourne la matrix clonée.
matrix matrix_mult(matrix mat1, matrix mat2)
{
  if (mat1.n != mat2.m || matrix_legal(mat1) || matrix_legal(mat2))
  {
    matrix failed = matrix_create(-1,-1);
    return failed;
  }
  matrix mat_resultat = matrix_clone(mat1);
  matrix_mult_in_place(&mat_resultat, mat2);
  return mat_resultat;
}

// cette fonction clone la matrix mat en paramètre, et elle applique la fonction matrix_add_scalar_in_place au clone, elle retourne la matrix clonée.
matrix matrix_add_scalar(matrix mat, double n)
{
  if(matrix_legal(mat))
  {
    matrix failed = matrix_create(-1,-1);
    return failed;
  }
  matrix mat_resultat = matrix_clone(mat);
  matrix_add_scalar_in_place(mat_resultat, n);
  return mat_resultat;
}

// cette fonction clone la matrix mat en paramètre, et elle applique la fonction matrix_mult_scalar_in_place au clone, elle retourne la matrix clonée.
matrix matrix_mult_scalar(matrix mat, double n)
{
  if(matrix_legal(mat))
  {
    matrix failed = matrix_create(-1,-1);
    return failed;
  }
  matrix mat_resultat = matrix_clone(mat);
  matrix_mult_scalar_in_place(mat_resultat, n);
  return mat_resultat;
}

// cette fonction clone la matrix mat en paramètre, et elle applique la fonction matrix_normalize_in_place au clone, elle retourne la matrix clonée.
matrix matrix_normalize(matrix mat)
{
  if(matrix_legal(mat))
  {
    matrix failed = matrix_create(-1,-1);
    return failed;
  }
  else
  {
    matrix newmat = matrix_clone(mat);
    matrix_normalize_in_place(newmat);
    return newmat;
  }
}

// cette fonction clone la matrix mat en paramètre, et elle applique la fonction matrix_transpose_in_place au clone, elle retourne la matrix clonée.
matrix matrix_transpose(matrix mat)
{
  if(matrix_legal(mat))
  {
    matrix failed = matrix_create(-1,-1);
    return failed;
  }
  matrix mat_resultat = matrix_clone(mat);
  matrix_transpose_in_place(&mat_resultat);
  return mat_resultat;
}

// cette fonction clone la matrix mat en paramètre, et elle applique la fonction matrix_clipper_in_place au clone, elle retourne la matrix clonée.
matrix matrix_clipper(matrix mat)
{
    if(matrix_legal(mat))
    {
      matrix failed = matrix_create(-1,-1);
      return failed;
    }
    matrix newmat = matrix_clone(mat);
    matrix_clipper_in_place(newmat);
    return newmat;
}

//vérifie si une matrix est valide
bool matrix_legal(matrix mat)
{
  return (mat.m < 1 || mat.n <1 || mat.data == NULL);
}
