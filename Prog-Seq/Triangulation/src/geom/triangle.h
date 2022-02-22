#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point_3d.h"

typedef struct triangle{
    point_3d v1, v2, v3;
} triangle;

triangle triangle_create(point_3d v1, point_3d v2, point_3d v3);
point_3d triangle_compute_normal(triangle *t);
double triangle_compute_area(triangle *t);

#endif
