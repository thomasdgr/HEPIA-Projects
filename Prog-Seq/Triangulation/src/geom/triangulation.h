#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>

#include "../vector/vector/vector_2d.h"
#include "../vector/vector/vector_3d.h"
#include "../vector/vector/vector_i_edge.h"
#include "../vector/vector/vector_i_triangle.h"
#include "triangle.h"
#include "point_3d.h"

void super_triangle(vector_3d *points, vector_i_triangle *triangles);
bool is_inside_circum_circle_points(point_3d p0, point_3d p1, point_3d p2, point_3d p3, point_3d *pc, double *rsqr, double epsilon);
void bowyer_watson(vector_3d *points, vector_i_triangle *triangles);
i_triangle form_triangle_from_edge_and_point(i_edge a, int point);
bool edge_common_with_triangle(i_edge a, i_triangle t);
bool same_triangle(i_triangle t1, i_triangle t2);
point_3d point_max(vector_3d points);
point_3d point_min(vector_3d points);
i_edge i_edge_create(int x, int y);
void clean_v_triangles(vector_3d* points, vector_i_triangle* triangles);
void remove_and_create_triangle(vector_i_triangle* mauvais_triangles, vector_i_triangle* triangles, vector_i_edge* arretes, int point);
void manage_outer_edges(vector_i_triangle* mauvais_triangles, vector_i_edge* arretes, vector_i_edge* arretes_tmp);

#endif
