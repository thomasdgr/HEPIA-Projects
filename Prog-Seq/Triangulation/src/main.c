/**********************************************************************************************************************************************************************************************************************************\
			 ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Fichier principal du projet qui lit un fichier .las, effectue
 __/  |    | \__/|               |                 une triangulation et écrit le résultat dans un fichier .stl
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |  
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		 |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "geom/triangulation.h"
#include "geom/triangulation_lst.h"
#include "stl/stl.h"

double check_epsilon(char *test);

int main(int argc, char *argv[]){
  if(argc == 5){
    srand(time(NULL));
    header entete = header_from_file(argv[1]);
    uint32_t nb_points = entete.num_point_records;
    point_3d* points = points_from_file(argv[1], entete, &nb_points, false);
    vector_3d points_filter;
    vector_3d_init(&points_filter);
    lst_vector_3d lst_points_filter;
    lst_vector_3d_init(&lst_points_filter);
    printf("points totaux : %d\n", nb_points);
    double seuil = check_epsilon(argv[2]);
    for(int i = 0; i < (int)nb_points; i++){
      if(rand()/(double)RAND_MAX < seuil){
        vector_3d_push(&points_filter, points[i]);
        lst_vector_3d_push(&lst_points_filter, points[i]);
      }
    }
    printf("points triangulés : %d\n", points_filter.length);
    free(points);

    vector_i_triangle triangles;
    vector_i_triangle_init(&triangles);
    lst_vector_i_triangle lst_triangles;
    lst_vector_i_triangle_init(&lst_triangles);

    int length_array = 0;
    int length_list = 0;
    int length_final = 0;
    if(!strcmp(argv[4], "array")){
      printf("using array : \n");
      bowyer_watson(&points_filter, &triangles);
      length_array = triangles.length;
    } else if(!strcmp(argv[4], "list")){
      bowyer_watson_lst(&lst_points_filter, &lst_triangles);
      length_list = lst_triangles.length;
    }
    if(length_array > length_list){
      length_final = length_array;
    } else{
      length_final = length_list;
    }
    
    triangle *tab = malloc(length_final * sizeof(triangle));
    assert(tab != NULL);
    for (int i = 0; i < length_final; i++) {
      i_triangle t_tmp;
      point_3d elem_tmp1;
      point_3d elem_tmp2;
      point_3d elem_tmp3;
      if(!strcmp(argv[4], "array")){
        vector_i_triangle_get(&triangles, i, &t_tmp);
        vector_3d_get(&points_filter, t_tmp.p1, &elem_tmp1);
        vector_3d_get(&points_filter, t_tmp.p2, &elem_tmp2);
        vector_3d_get(&points_filter, t_tmp.p3, &elem_tmp3);
      } else if(!strcmp(argv[4], "list")){
        lst_vector_i_triangle_get(&lst_triangles, i, &t_tmp);
        lst_vector_3d_get(&lst_points_filter, t_tmp.p1-3, &elem_tmp1);
        lst_vector_3d_get(&lst_points_filter, t_tmp.p2-3, &elem_tmp2);
        lst_vector_3d_get(&lst_points_filter, t_tmp.p3-3, &elem_tmp3); 
    }
      triangle t = triangle_create(elem_tmp1, elem_tmp2, elem_tmp3);
      tab[i] = t;
    }
    stl_file_create_and_write(argv[3], "output", tab, length_final);
    vector_i_triangle_free(&triangles);
    vector_3d_free(&points_filter);
    lst_vector_i_triangle_free(&lst_triangles);
    lst_vector_3d_free(&lst_points_filter);
    free(tab);
    return 0;
  }
  printf("invalid parameters\n");
  printf("follow : ./main <file.las> <epsilon(between 0 and 1)> <outputfile.stl> <\"list\"or\"array\">\n");
  return 0;
}

double check_epsilon(char *value){
  for (size_t i = 0; i < strlen(value); i++){
    if (!isdigit(value[i]) && value[i] != '.'){
      assert(false &&  "second parameter invalid");
    }
  }
  double seuil = atof(value);
  assert(seuil<1.0 && "please, enter number between 0 and1");
  return seuil;
}