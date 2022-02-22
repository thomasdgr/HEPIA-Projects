#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../priority_queue/priority_queue_generic.h"
#include "../vector_list/city_list.h"
#include "../vector_list/connection_list.h"
#include "../matrix/matrix.h"

typedef struct dst_to_src {
    int src;
    int dst;
} dst_to_src;

void dijkstra(lst_connection *g, int src, int num, int dist[], int prev[]);
void floyd_warshall(matrix adj, matrix* dist, matrix* next);
bool cmp_dst_to_src(void* i, void* j);

#endif