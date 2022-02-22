#include "test_triangle.h"
#include "../geom/triangle.h"
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

void test_triangle_create(){
    point_3d point1 = point_3d_create(1,2,3);
    point_3d point2 = point_3d_create(4,5,6);
    point_3d point3 = point_3d_create(7,8,9);

    triangle mon_triangle = triangle_create(point1, point2, point3);

    CU_ASSERT(mon_triangle.v1.x == point1.x);
    CU_ASSERT(mon_triangle.v1.y == point1.y);
    CU_ASSERT(mon_triangle.v1.z == point1.z);

    CU_ASSERT(mon_triangle.v2.x == point2.x);
    CU_ASSERT(mon_triangle.v2.y == point2.y);
    CU_ASSERT(mon_triangle.v2.z == point2.z);

    CU_ASSERT(mon_triangle.v3.x == point3.x);
    CU_ASSERT(mon_triangle.v3.y == point3.y);
    CU_ASSERT(mon_triangle.v3.z == point3.z);
}

void test_triangle_compute_normal(){
    point_3d point1 = point_3d_create(1,2,3);
    point_3d point2 = point_3d_create(4,5,6);
    point_3d point3 = point_3d_create(7,8,9);

    triangle mon_triangle = triangle_create(point1, point2, point3);

    point_3d v_normal = triangle_compute_normal(&mon_triangle);

    CU_ASSERT(v_normal.x == 0);
    CU_ASSERT(v_normal.y == 0);
    CU_ASSERT(v_normal.z == 0);
}

void test_triangle_compute_area(){
    point_3d point1 = point_3d_create(1,2,3);
    point_3d point2 = point_3d_create(4,5,6);
    point_3d point3 = point_3d_create(7,8,9);

    triangle mon_triangle = triangle_create(point1, point2, point3);

    double area = triangle_compute_area(&mon_triangle);

    CU_ASSERT(area == 0);
}
