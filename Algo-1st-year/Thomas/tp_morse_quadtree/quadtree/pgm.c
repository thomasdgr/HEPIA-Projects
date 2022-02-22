#include "pgm.h"
#include "matrix.h"
#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//cette fonction lit un fichier d'image pgm, et elle retourne la matrix de l'image
//pour prendre cette matrix, stockons les valeurs de la matrix dans un tab, pour nous créons la matrix à partir de la fonction matrix_create_from_array
pgm pgm_read(char *filename)
{
    char *line_buff = NULL; //la ligne de notre fichier
    size_t line_buff_size = 0; // le nombre de caractère de notre ligne
    FILE * fp = fopen(filename, "r");//le fichier

    if (!fp) // Vérification si le fichier existe
    {
      pgm failed;
      failed.max = -1;
      return failed;
    }
    else
    {
      pgm matrix_read;
      int v_a_prendre = 0;
      int m = -1, n = -1;
      // création de notre tab
      int size_array = -1;
      int index_array = 0;
      double* array = NULL;

      //avec cette boucle, on parcours notre fichier ligne par ligne,
      while(getline(&line_buff, &line_buff_size, fp) >= 0)
      {
        //avec cette boucle, on parcours les caractères de notre ligne
        char *token = strtok(line_buff," \n\t\f"); // va prend le premier élément de la ligne séparée par le premier délimiter
        while (token != NULL) // prendre les autres éléments
        {
              if(token[0] == 'P' || token[0] == '#')
              {
                break;
              }
              else
              {
                if(v_a_prendre == 0)
                {
                    n = atoi(token);
                    v_a_prendre++;
                }
                else if (v_a_prendre == 1)
                {
                    m = atoi(token);
                    v_a_prendre++;
                    size_array = m*n;
                    array = malloc(size_array*sizeof(double));
                    assert(array != NULL);
                }
                else if (v_a_prendre == 2)
                {
                    matrix_read.max = atoi(token);
                    v_a_prendre++;
                }
                else if (v_a_prendre == 3)
                {
                    array[index_array] = atoi(token); // met les valeurs dans le tab: array
                    index_array++;
                }
              }
              token = strtok(NULL, " \n\t\f");
          }
        }
        // création de notre matrix à partir du tab: array
        free(line_buff);
        matrix tmp_matrix = matrix_create_from_array(m,n,array);
        //matrix_normalize_in_place(tmp_matrix);
        matrix_read.mat = tmp_matrix;
        free(array);
        fclose(fp);
        return matrix_read;
      }
}

//cette fonction va met la matrix de l'image invalide
void pgm_destroy(pgm *image)
{
  image->max = - 1;
  matrix_destroy(&image->mat);
}

// cette focntion va écrit la matrix de l'image transformée dans un nouveau fichier pgm
int pgm_write(char *filename, pgm image)
{
  FILE * fp = fopen(filename, "w");

  if(!fp)
  {
    fclose(fp);
    return 0;
  }
  else
  {
    fprintf(fp, "P2\n");
    fprintf(fp, "# commentaire\n");
    fprintf(fp, "%d %d\n",image.mat.n, image.mat.m);
    fprintf(fp, "%d\n", image.max);
    for (int i = 0; i < image.mat.m; i++)
    {
      for (int j = 0; j < image.mat.n; j++)
      {
        fprintf(fp, "%d", (int)image.mat.data[i][j]);
        if(j+1 < image.mat.n)
        {
          fprintf(fp," ");
        }
      }
      fprintf(fp,"\n");
    }
    fclose(fp);
    return 1;
  }
}

// vérification si les deux matrix de l'image sont égaux
bool pgm_is_equal(pgm i1, pgm i2)
{
    if(i1.max != i2.max)
    {
      return false;
    }
    else
    {
      return matrix_is_equal(i1.mat, i2.mat);
    }
}
// vérification si les deux matrix de l'image sont égaux avec un taux d'erreur = epsilon
bool pgm_is_approx_equal(pgm i1, pgm i2, double epsilon)
{
    if (i1.max != i2.max)
    {
      return false;
    }
    else
    {
      return matrix_is_approx_equal(i1.mat, i2.mat, epsilon);
    }
}
