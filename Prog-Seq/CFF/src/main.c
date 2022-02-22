#include "priority_queue/priority_queue_generic.h"
#include "xml_parser/xml_parser.h"
#include "dijkstra_floyd/dijkstra.h"
#include "vector_list/city_list.h"
#include "vector_list/connection_list.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define _GNU_SOURCE
#define PATH_SIZE 1000

int main(int argc, char** argv) {
   char *line = NULL;
   char *str1 = NULL;
   char *str2 = NULL;
   char *str3 = NULL;;
   size_t len = 0;
   FILE *input = stdin;

   lst_city v1;
   lst_city_init(&v1);

   lst_connection* tab;
   
   matrix mat = matrix_create(1,1);

   if(argc>1) input = fopen(argv[1],"r\n");

   char filepath[PATH_SIZE];
   size_t return_value = 0;
   char* return_pointer;
   return_pointer = getcwd(filepath, PATH_SIZE);
   if(return_pointer == NULL){
      printf("error with getcwd()\n");
   }
   strcat(filepath, "/villes.xml");
   read_xml("src/villes.xml", &v1, &tab, &mat);
   fprintf(stderr, "Le fichier XML %s a été chargé\n", filepath);

   matrix mat_next = matrix_create(mat.m, mat.n);
   matrix mat_dist = matrix_create(mat.m, mat.n);

   // pour passer d'une matrice à une liste d'adjacence et l'inverse
   //matrix list2matrix = convert_lst_to_matrix(&tab, &v1);
   //lst_connection* matrix2list = convert_matrix_to_lst(&mat2, &v1);
   
   int dist[v1.length];
   int prev[v1.length];
   int choix = 0;

   do{
      fprintf(stderr, "Choix  0: quitter\n");
      fprintf(stderr, "Choix  1: liste des villes\n");
      fprintf(stderr, "Choix  2: matrice des poids\n");
      fprintf(stderr, "Choix  3: liste des poids\n");         
      fprintf(stderr, "Choix  4: matrice des temps de parcours (Floyd)\n");
      fprintf(stderr, "Choix  5: matrice des suivants (Floyd)\n");
      fprintf(stderr, "Choix  6: temps de parcours entre deux villes (Floyd)\n");
      fprintf(stderr, "Choix  7: parcours entre deux villes (Floyd)\n");
      fprintf(stderr, "Choix  8: tableau des temps de parcours (Dijkstra)\n");
      fprintf(stderr, "Choix  9: tableau des précédences (Dijkstra)\n");
      fprintf(stderr, "Choix 10: temps de parcours entre deux villes (Dijkstra)\n");
      fprintf(stderr, "Choix 11: parcours entre deux villes (Dijkstra)\n");

      fprintf(stderr, "Entrez votre choix: ");
      return_value = getline(&line, &len, input);
      if((int)return_value == -1){
         printf("error\n");
      }
      choix = atoi(line);
      switch(choix) {
      case 1:
         print_lst_city(&v1);
         break;
      case 2:
         matrix_print(mat);
         break;
      case 3:
         print_lst_tab_connection(tab);
         break;
      case 4:
         floyd_warshall(mat, &mat_dist, &mat_next);
         for(int i = 0; i < mat_dist.m; i++){
            for(int j = 0; j < mat_dist.n; j++){
               if(mat_dist.data[i][j] == INT_MAX){
                  printf("inf ");
               } else {
                  printf("%d ", mat_dist.data[i][j]);
               }
            }
            printf("\n");
         }
         break;
      case 5:
         floyd_warshall(mat, &mat_dist, &mat_next);
         for(int i = 0; i < mat_next.m; i++){
            for(int j = 0; j < mat_next.n; j++){
               printf("%d ", mat_next.data[i][j]);
            }
            printf("\n"); 
         }
         break;
      case 6:
         floyd_warshall(mat, &mat_dist, &mat_next);
         fprintf(stderr, "Ville d'origine: ");
         return_value = getline(&str1, &len, input);
         if((int)return_value == -1){
            printf("error\n");
         }
         fprintf(stderr, "Ville de destination: ");
         return_value = getline(&str2, &len, input);
         if((int)return_value == -1){
            printf("error\n");
         }
         fprintf(stderr, "Distance: ");
         strtok(str1, "\n");
         strtok(str2, "\n");
         for(int i = 0; i < mat_dist.m; i++){
            for(int j = 0; j < mat_dist.n; j++){
               if(i == get_index_from_city(str1) && j == get_index_from_city(str2)){
                  if(mat_dist.data[i][j] == INT_MAX){
                     printf("inf\n");
                  } else {
                     printf("%d\n", mat_dist.data[i][j]);
                  }
               }
            }
         }
         break;   
      case 7:
         fprintf(stderr, "Ville d'origine: ");
         return_value = getline(&str1, &len, input);
         if((int)return_value == -1){
            printf("error\n");
         }
         fprintf(stderr, "Ville de destination: ");
         return_value = getline(&str2, &len, input);
         if((int)return_value == -1){
            printf("error\n");
         }
         fprintf(stderr, "Parcours: ");
         strtok(str1, "\n");
         strtok(str2, "\n");
         bool leave = false;
         int crt = get_index_from_city(str1);
         int fin = get_index_from_city(str2);
         char resultat[100] = "[";
         strcat(resultat, str1);
         floyd_warshall(mat, &mat_dist, &mat_next);
         while(crt != fin){
            for(int i = 0; i < mat_next.m; i++){
               for(int j = 0; j < mat_next.n; j++){
                  if(i == crt && j == fin){
                     crt = mat_next.data[i][j];
                     strcat(resultat, ":");
                     strcat(resultat, get_city_from_index(crt));
                     if(crt == fin){
                        leave = true;
                     }
                     break;
                  }
                  if(leave)break;
               }
               if(leave)break;
            }
            if(leave)break;
         }
         strcat(resultat, "]");
         printf("%s\n",resultat);
         break;
      case 8:
         fprintf(stderr, "Ville d'origine: ");
         return_value = getline(&str1, &len, input);
         if((int)return_value == -1){
            printf("error\n");
         }
         fprintf(stderr, "Parcours: ");
         strtok(str1, "\n");
         for(int i = 0; i < v1.length; i++){
            if(i == get_index_from_city(str1)){
               dijkstra(tab, i, v1.length, dist, prev);
               for(int j = 0; j < v1.length; j++){
                  if(dist[j] ==INT_MAX){
                     printf("[%s:inf] ", get_city_from_index(j));
                  }else{
                     printf("[%s:%d] ",get_city_from_index(j), dist[j]);
                  }
               }
            }
         }
         printf("\n");
         break;
      case 9:
         fprintf(stderr, "Ville d'origine: ");
         return_value = getline(&str1, &len, input);
         if((int)return_value == -1){
            printf("error\n");
         }
         strtok(str1, "\n");
         for(int i = 0; i < v1.length; i++){
            if(i == get_index_from_city(str1)){
               dijkstra(tab, i, v1.length, dist, prev);
               for(int j = 0; j < v1.length; j++){
                  if(prev[j] != -1){
                     printf("[%s<-%s] ",get_city_from_index(prev[j]),get_city_from_index(j));
                  }
               }
               break;
            }
         }
         printf("\n");
         break;
      case 10:
         fprintf(stderr, "Ville d'origine: ");
         return_value = getline(&str1, &len, input);
         if((int)return_value == -1){
            printf("error\n");
         }
         fprintf(stderr, "Ville de destination: ");
         return_value = getline(&str2, &len, input);
         if((int)return_value == -1){
            printf("error\n");
         }
         fprintf(stderr, "Distance:  ");
         strtok(str1, "\n");
         strtok(str2, "\n");
         dijkstra(tab, get_index_from_city(str1), v1.length, dist, prev);
         for(int j = 0; j < v1.length; j++){
            if(j == get_index_from_city(str2)){
               printf("%d\n", dist[j]);
            }
         }
         break;      
      case 11:
         fprintf(stderr, "Ville d'origine: ");
         return_value = getline(&str1, &len, input);
         if((int)return_value == -1){
            printf("error\n");
         }
         fprintf(stderr, "Ville de destination: ");
         return_value = getline(&str2, &len, input);
         if((int)return_value == -1){
            printf("error\n");
         }
         fprintf(stderr, "Parcours: ");
         strtok(str1, "\n");
         strtok(str2, "\n");
         char res[100] = "[";
         strcat(res, str1);
         strcat(res, ":");
         char tab_city[15][30];
         int count = 0;
         int crt2 = get_index_from_city(str2);
         int fin2 = get_index_from_city(str1);
         dijkstra(tab, fin2, v1.length, dist, prev);
         while(crt2 != fin2){
            for(int j = 0; j < v1.length; j++){
               if(j == crt2){
                  crt2 = prev[j];
                  if(crt2 != fin2){
                     strcpy(tab_city[count], get_city_from_index(prev[j]));
                     count++;
                  }
                  break;
               }
            }
         }
         for(int i = count-1; i >= 0; i--){
            strcat(res, tab_city[i]);
            strcat(res, ":");
         }
         strcat(res, str2);
         strcat(res, "]");
         printf("%s\n",res);
         break;
      }
   }while(choix != 0);
   free(line);
   free(str1);
   free(str2);
   free(str3);
   fclose(input);
   tab_connection_free(tab, v1.length);
   lst_city_free(&v1);
   matrix_destroy(&mat);
   matrix_destroy(&mat_dist);
   matrix_destroy(&mat_next);

   return 0;
}