/*******************************************************************************
			       ____
           /____ \               |  Projet : manipulation de matrices
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : programme pour lire les
 __/  |    | \__/|               |    opérations d'un fichier txt et appliquer
(___) \.  _.\__. `\___           |    les fonctions à partir des autres
(___)  )\/  \_____/  ~\.         |    librairies (matrix, pgm, geo et filter)
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	29/11/2019

\******************************************************************************/

#include "pgm.h"
#include "geom.h"
#include "matrix.h"
#include "filter.h"
#include "gfx.h"

int main(int argc, char* argv[]){
  char const* fileName = "";
  char const* visual_option = "";
  if(argc > 1){
    fileName = argv[1];
    if(argc > 2){
      visual_option = argv[2];
    }
  } else {
    printf("please enter an operation_file");
    exit(0);
  }
  FILE* file = fopen(fileName, "r+");
  char line[256];
  char* token;
  char* token1;
  char* token2;
  char* token3;
  bool is_valid = false; // verifie que le pgm est bien ouvert
  // ou n'est pas fermé avant d'appliquer des fonctions
  pgm read;
  pgm read_2;
  while (fgets(line, sizeof(line), file)) {
    // premier element de la ligne qui va executer la fonction
    token = strtok(line, " \n\t\f");
    // on compare en brut la valeur du token et une valeur
    //attendu pour savoir quelle fonction executer
    if(strcmp(token, "read") == 0){
      // on prend les arguments qui suivent dans token1, 2 ou 3 pour la fonction
      token1 = strtok(NULL, " \n\t\f");
      read = pgm_read(token1);
      if(read.max == -1){
        printf("path incorrect or file does not exist in fuction pgm_read\n");
      }
      is_valid = true;
    }
    else if(strcmp(token, "write") == 0 && is_valid == true){
      token1 = strtok(NULL, " \n\t\f");
      pgm_write(token1,read);
      is_valid = false;
      printf("result is created in matrice-ci/%s\n",token1);
    }
    else if(strcmp(token, "rotate") == 0 && is_valid == true){
      token1 = strtok(NULL, " \n\t\f");
      token2 = strtok(NULL, " \n\t\f");
      token3 = strtok(NULL, " \n\t\f");
      // on verifie que les parametres sont bien des nombres
      if('0' <= token1[0] && token1[0] <= '9' && '0' <= token2[0] && token2[0] <= '9' && '0' <= token3[0] && token3[0] <= '9'){
        double angle =atof(token3);
        double datacenter[] = {atof(token1), atof(token2)};
        matrix center = matrix_create_from_array(1, 2, datacenter);
        geom_rotate_in_place(&read.mat, angle, center);
        matrix_destroy(&center);
      } else {
        printf("bad argument selected after rotate function\n");
        continue;
      }
    }
    else if(strcmp(token, "translate") == 0 && is_valid == true){
      token1 = strtok(NULL, " \n\t\f");
      token2 = strtok(NULL, " \n\t\f");
      double datatranslate[] = {atof(token1), atof(token2)};
      matrix translate = matrix_create_from_array(1, 2, datatranslate);
      geom_translate_in_place(&read.mat, translate);
      matrix_destroy(&translate);
    }
    else if(strcmp(token, "zoom") == 0 && is_valid == true){
      token1 = strtok(NULL, " \n\t\f");
      token2 = strtok(NULL, " \n\t\f");
      double datazoom[] = {atof(token1), atof(token2)};
      matrix zoom = matrix_create_from_array(1, 2, datazoom);
      geom_zoom_in_place(&read.mat, zoom);
      matrix_destroy(&zoom);
    }
    else if(strcmp(token, "resize") == 0 && is_valid == true){
      token1 = strtok(NULL, " \n\t\f");
      token2 = strtok(NULL, " \n\t\f");
      matrix_resize(&read.mat, atoi(token1), atoi(token2));
    }
    else if(strcmp(token, "photomaton") == 0 && is_valid == true){
      geom_photomaton_in_place(&read.mat);
    }
    else if(strcmp(token, "symmetry") == 0 && is_valid == true){
      token1 = strtok(NULL, " \n\t\f");
      if(strcmp(token1, "vertical") == 0){
        geom_vertical_axis_reflect_in_place(&read.mat);
      }
      else if(strcmp(token1, "horizontal") == 0){
        geom_horizontal_axis_reflect_in_place(&read.mat);
      }
      else if(strcmp(token1, "center") == 0){
        geom_central_reflect_in_place(&read.mat);
      }
      else {
        printf("bad argument selected after symmetry function\n");
      }
    }
    else if((strcmp(token, "mult") == 0 || strcmp(token, "add") == 0 || strcmp(token, "sub") == 0) && is_valid == true){
      token1 = strtok(NULL, " \n\t\f");
      read_2 = pgm_read(token1);
      if(read_2.max == -1){
        printf("path incorrect or file does not exist after fuction %s\n",token);
      }
      else if(strcmp(token, "mult") == 0){
        matrix_mult_in_place(&read.mat, read_2.mat);
      }
      else if(strcmp(token, "add") == 0){
        matrix_add_in_place(read.mat, read_2.mat);
      }
      else if(strcmp(token, "sub") == 0){
        matrix_sub_in_place(read.mat, read_2.mat);
      }
      else {
        printf("bad argument selected after function %s\n",token);
      }
    }
    else if((strcmp(token, "mult_scalar") == 0) && is_valid == true){
      token1 = strtok(NULL, " \n\t\f");
      if('0' <= token1[0] && token1[0] <= '9'){
        matrix_mult_scalar_in_place(read.mat, atof(token1));
      } else {
        printf("bad argument selected after function %s\n",token);
      }
    }
    else if((strcmp(token, "add_scalar") == 0) && is_valid == true){
      token1 = strtok(NULL, " \n\t\f");
      if('0' <= token1[0] && token1[0] <= '9'){
        matrix_add_scalar_in_place(read.mat, atof(token1));
      } else {
        printf("bad argument selected after function %s\n",token);
      }
    }
    else if(strcmp(token, "sharpen") == 0 && is_valid == true){
      filter_sharpen_in_place(&read.mat);
    }
    else if(strcmp(token, "sobel") == 0 && is_valid == true){
      filter_sobel_in_place(&read.mat);
    }
    else if(strcmp(token, "smooth") == 0 && is_valid == true){
      filter_smooth_in_place(&read.mat);
    }
    else if(strcmp(token, "blur") == 0 && is_valid == true){
      filter_blur_in_place(&read.mat);
    }
    else if(strcmp(token, "edge_enhance") == 0 && is_valid == true){
      filter_edge_enhance_in_place(&read.mat);
    }
    else if(strcmp(token, "edge_detect") == 0 && is_valid == true){
      filter_edge_detect_in_place(&read.mat);
    }
    else if(strcmp(token, "emboss") == 0 && is_valid == true){
      filter_emboss_in_place(&read.mat);
    }
    // démo :

    // gestion des cas inattendus
    else {
      if(token[0] == '#' || token[0] == '\n'){
        continue;
      } else if(is_valid == false){
        printf("please make sure pgm is created before applying fuctions\n");
        continue;
      } else {
        printf("bad argument selected for function %s\n", token);
        continue;
      }
    }
    // affichage avec le mode visual
    if(strcmp(visual_option, "visual") == 0 && is_valid == true){
      struct gfx_context_t* context = NULL;
      printf("press ENTER to continue\n");
      printf("applying %s ...\n", token);
      while(gfx_keypressed() != SDLK_RETURN){
        if(gfx_keypressed() == SDLK_SPACE){
          exit(0);
        }
        render_image(read.mat.m, read.mat.n, &context, read.mat);
        gfx_present(context);
      }
      gfx_destroy(context);
    }
  }
    fclose(file);
    pgm_destroy(&read);
    return 0;
}
