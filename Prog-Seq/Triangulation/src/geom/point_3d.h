#ifndef POINT_3D_H
#define POINT_3D_H

// la structure point_3d est créée dans lidar.h
#include "../lidar/lidar.h"

point_3d point_3d_create(double x, double y, double z);
void point_3d_add_inplace(point_3d *p1, point_3d *p2);
void point_3d_sub_inplace(point_3d *p1, point_3d *p2);
void point_3d_scale_inplace(point_3d *p1, double a);
point_3d point_3d_add(point_3d *p1, point_3d *p2);
point_3d point_3d_sub(point_3d *p1, point_3d *p2);
point_3d point_3d_scale(point_3d *p1, double a);
double compute_norm(point_3d *p);
double compute_distance(point_3d *p1, point_3d *p2);
void print_point(point_3d *p);
void point_3d_normalize_in_place(point_3d *p);
point_3d point_3d_normalize(point_3d *p);
point_3d point_3d_vector_product(point_3d *p1, point_3d *p2);

#endif
