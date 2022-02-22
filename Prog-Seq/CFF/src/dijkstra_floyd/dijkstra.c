/*******************************************************************************
			____
           /____ \               |  Projet : C_FF
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : librairie de fonctions
 __/  |    | \__/|               |    utilisées pour trouver les plus courts
(___) \.  _.\__. `\___           |    chemins dans une liste et une matrice 
(___)  )\/  \_____/  ~\.         |    d'adjacence. 
(___) . \   `         `\         |    Algorithme de Dijkstra et de Floyd-Warshall
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		 |	Date :	03/06/2020

\******************************************************************************/
#include "dijkstra.h"

void dijkstra(lst_connection *g, int src, int num, int dist[], int prev[]){
    // initialisation
    for(int i = 0; i < num; i++){
        if(i == src){
            dist[src] = 0;
            prev[src] = -1;
        }else{
            dist[i] = __INT_MAX__;
            prev[i] = 0;
        }
    }
    // creation d'une queue de priorité iitialisée avec 1 élément
    dst_to_src elem = {src,0};
    priority_queue_generic q;
    priority_queue_generic_init(&q);
    priority_queue_generic_push(&q, (void*)(&elem), cmp_dst_to_src);
    int count = 0;
    // application de l'algorithme de Dijkstra
    while(!priority_queue_generic_is_empty(&q)){
        dst_to_src* p;
        priority_queue_generic_pop(&q, (void**)&p);
        p = *(dst_to_src**)&p;
        int index = p->src;
        dst_to_src storage[200];
        // les foreach me manquent donc j'en ai fait un en souvenir du bon vieux temps
        for (connection* v = (&g[p->src])->head ; v != NULL; v = v->next){
            int d_new = dist[index] + v->weight;
            if(d_new < dist[v->neighbor]){
                dist[v->neighbor] = d_new;
                prev[v->neighbor] = p->src;
                dst_to_src tmp = {v->neighbor, d_new};
                storage[count] = tmp;
                priority_queue_generic_push(&q, (void*)(storage+count), cmp_dst_to_src);
                count++;
            }
        }    
    }
}

void floyd_warshall(matrix adj, matrix* dist, matrix* next){
    // initialisation
    for(int i = 0; i < adj.m; i++){
        for(int j = 0; j < adj.n; j++){
            dist->data[i][j] = adj.data[i][j];
        }
    }
    for(int i = 0; i < adj.m; i++){
        for(int j = 0; j < adj.n; j++){
            if(dist->data[i][j] != __INT_MAX__){
                next->data[i][j] = j;
            } if(i == j){
                next->data[i][j] = -1;
                dist->data[i][j] = 0;
            }
        }
    }
    // application de l'algorithme de Floyd-Warshall
    for(int k = 0; k < adj.m; k++){
        for(int i = 0; i < adj.m; i++){
            for(int j = 0; j < adj.m; j++){
                if(dist->data[i][j] > dist->data[i][k] + dist->data[k][j]){
                    if(dist->data[i][k] != __INT_MAX__ && dist->data[k][j] != __INT_MAX__){
                        dist->data[i][j] = dist->data[i][k] + dist->data[k][j];
                        next->data[i][j] = next->data[i][k];
                    }
                }  
            }
        }
    }
}

// pas très utile ici car on a besoin d'une structure LIFO
bool cmp_dst_to_src(void* i, void* j){
    dst_to_src tmp1 = *(dst_to_src *)i;
    dst_to_src tmp2 = *(dst_to_src *)j;
    return tmp1.dst > tmp2.dst;
}