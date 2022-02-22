#include "pgm.h"

// lecture d'un fichier pgm et structuration des données pour préparer les manipulations
pgm pgm_read(char *filename){
  pgm res;
  FILE * image = fopen(filename, "rb"); // ouvre le fichier
  if(!image){ // verifie la validite du fichier
    res.max = -1;
    res.mat = matrix_default_value(res.mat);
    return res;
  }
  int sizeBuffer = 100;
  char buffer[sizeBuffer];
  char* content;
  // c'est un uint16 car ca correspond à la valeur max lisible dans le fichier
  uint16_t value;
  // lecture du header
  if (fgets(buffer, sizeBuffer, image) != NULL){
    content = strtok(buffer, " ");
    if(strcmp(content, "P5") == 0){
		  content = strtok(NULL, " ");
		  res.mat.n = atoi(content);
      content = strtok(NULL, " ");
		  res.mat.m = atoi(content);
      content = strtok(NULL, " ");
		  res.max = atoi(content);
      res.mat = matrix_create(res.mat.m, res.mat.n);
    }
	} else {
    printf("error while reading header");
    exit(EXIT_FAILURE);
  }
  // on saute vers l'image
  fseek(image,strlen(buffer), SEEK_SET );
  // lecture des données de l'image
  for (int i = 0; i < res.mat.m; i++){
    for (int j = 0; j < res.mat.n; j++){
      if(fread(&value, sizeof(uint16_t), 1, image) == 1){
        res.mat.data[i][j] = value;
      }
    }
  }
  fclose(image);
  matrix_mult_scalar_in_place(res.mat, 1.0/(double)res.max);
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
      fprintf(pgm_file, "%d", (int)(image.mat.data[i][j]));// * image.max));
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

// application d'une convolution à partir d'un pgm et d'un kernel
// retourne la matrice correspondant au résultat de la convolution
matrix applyConvolveOnPGM(pgm read, double ker[]){
  matrix k = matrix_create_from_array(3,3,ker);
	matrix res = matrix_convolve(read.mat, k);
  matrix_convert_in_eight_bits_in_place(res);
  matrix_destroy(&k);
  return res;
}