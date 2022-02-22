#ifndef TRIANGULATION_LST_H
#define TRIANGULATION_LST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>

#include "../vector/vector_list/vector_list_2d.h"
#include "../vector/vector_list/vector_list_3d.h"
#include "../vector/vector_list/vector_list_i_edge.h"
#include "../vector/vector_list/vector_list_i_triangle.h"
#include "triangle.h"
#include "triangulation.h"
#include "point_3d.h"

void super_triangle_lst(lst_vector_3d *points, lst_vector_i_triangle *triangles);
bool is_inside_circum_circle_points_lst(point_3d p0, point_3d p1, point_3d p2, point_3d p3, point_3d *pc, double *rsqr, double epsilon);
void bowyer_watson_lst(lst_vector_3d *points, lst_vector_i_triangle *triangles);
i_triangle form_triangle_from_edge_and_point_lst(i_edge a, int point);
bool edge_common_with_triangle_lst(i_edge a, i_triangle t);
bool same_triangle_lst(i_triangle t1, i_triangle t2);
point_3d point_max_lst(lst_vector_3d points);
point_3d point_min_lst(lst_vector_3d points);
void clean_v_triangles_lst(lst_vector_3d* points, lst_vector_i_triangle* triangles);
void remove_and_create_triangle_lst(lst_vector_i_triangle* mauvais_triangles, lst_vector_i_triangle* triangles, lst_vector_i_edge* arretes, int point);
void manage_outer_edges_lst(lst_vector_i_triangle* mauvais_triangles, lst_vector_i_edge* arretes, lst_vector_i_edge* arretes_tmp);

#endif
