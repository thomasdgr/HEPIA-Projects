/*******************************************************************************
			       ____
           /____ \               |  Projet : manipulation de matrices
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : librairie de fonctions
 __/  |    | \__/|               |    utilisées pour lire et écrire dans
(___) \.  _.\__. `\___           |    des fichiers pgm
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	29/11/2019

\******************************************************************************/

#include "pgm.h"

// lecture d'un fichier pgm et structuration des données pour préparer les manipulations
pgm pgm_read(char *filename){
  pgm res;
  FILE * image = fopen(filename, "r+"); // ouvre le fichier
  if(!image){ // verifie la validite du fichier
    res.max = -1;
    res.mat = matrix_default_value(res.mat);
    return res;
  }
  int ligne = 0;             // nombre de caratères retournés par getline()
  char *ligne_buffer = NULL; // pointeur ver le contenu de la ligne
  size_t num_buffer = 0;     // pas utilisé ici mais nécéssaire pour getline()
  int count = 0;             // numéro de la ligne
  char *token;               // pointeur vers un element de la ligne stockée dans ligne_buffer
  double *array=NULL;        // stock temporairement les valeurs avant de les mettre dans la matrice
  int increment=0;
  ligne = getline(&ligne_buffer, &num_buffer, image);
  // tant qu'une ligne avec plus de 0 caractères est retournée
  while((ligne = getline(&ligne_buffer, &num_buffer, image)) > 0){
    // excepte les commentaires et le type du fichier
    if(!(ligne_buffer[0] == 'P' || ligne_buffer[0] == '#')){
      count++;
      // ne fonctionne que si la structure standard d'un pgm est appliquée sur l'image
      if(count == 1){
        token = strtok(ligne_buffer, " ");
        res.mat.n = atoi(token);
        token = strtok(NULL, " ");
        res.mat.m = atoi(token);
        array = malloc((res.mat.m) * (res.mat.n) * sizeof(double));
      }
      if(count == 2){
        res.max = atoi(ligne_buffer);
      }
      // toute les valeurs de l'image sous forme de matrice
      if(count >= 3){
         // premier element de la ligne (première valeur)
        token = strtok(ligne_buffer, " ");
        do {
          // on vérifie que le token est bien un nombre
          if('0' <= token[0] && token[0] <= '9'){
            // ajout de la valeur qui est normalisée
            array[increment] = (double)atoi(token) / (double)res.max;
            increment++;
          }
          // retourne les éléments suivants de la ligne tant qu'il y en a
        } while ((token = strtok(NULL, " ")) != NULL);
      }
    }
  }
  res.mat = matrix_create_from_array(res.mat.m, res.mat.n, array);
  free(ligne_buffer);
  free(array);
  // ferme le fichier
  fclose(image);
  return res;
}

// destruction d'une structure pgm et de sa matrice
void pgm_destroy(pgm *image){
  image->max = -1;
  matrix_destroy(&image->mat);
}

// écriture selon les standards d'une structure pgm dans un fichier
int pgm_write(char *filename, pgm image){
  // ouverture avec droits d'ecriture
  FILE * pgm_file = fopen (filename, "w+");
  if(!pgm_file){
    return 0;
  }
  // affichage selon les standards des pgm
  fprintf(pgm_file, "P2\n");
  fprintf(pgm_file, "%d %d\n", image.mat.n,image.mat.m);
  fprintf(pgm_file, "%d\n", image.max);
  for(int i = 0; i < image.mat.m; i++){
    for(int j = 0; j < image.mat.n; j++){
      fprintf(pgm_file, "%d", (int)(image.mat.data[i][j] * image.max));
      if(j+1 < image.mat.n){
        fprintf(pgm_file, " ");
      }
    }
    fprintf(pgm_file, "\n");
  }
  fclose(pgm_file);
  return 1;
}

// comparaision de structures pgm
bool pgm_is_equal(pgm i1, pgm i2){
  if(i1.max != i2.max){
      return false;
    }
    return matrix_is_equal(i1.mat, i2.mat);
}

// comparaision aproximée de structures pgm
bool pgm_is_approx_equal(pgm i1, pgm i2, double epsilon){
  if(i1.max != i2.max){
    return false;
  }
  return matrix_is_approx_equal(i1.mat, i2.mat, epsilon);
}
