#include "test_point_3d.h"
#include "../vector/vector/vector.h"
#include "../geom/point_3d.h"
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

void test_point_3d_create(){
    point_3d point1;
    point1.x = 1;
    point1.y = 2;
    point1.z = 3;

    point_3d point2 = point_3d_create(1,2,3);

    CU_ASSERT(point1.x == point2.x);    
    CU_ASSERT(point1.y == point2.y);    
    CU_ASSERT(point1.z == point2.z);    
} 

void test_point_3d_add_inplace(){
    point_3d point1 = point_3d_create(1,2,3);
    point_3d point2 = point_3d_create(4,5,6);

    point_3d_add_inplace(&point1, &point2);

    CU_ASSERT(point1.x == 5);    
    CU_ASSERT(point1.y == 7);    
    CU_ASSERT(point1.z == 9); 
}

void test_point_3d_sub_inplace(){
    point_3d point1 = point_3d_create(4,5,6);
    point_3d point2 = point_3d_create(1,2,3);

    point_3d_sub_inplace(&point1, &point2);

    CU_ASSERT(point1.x == 3);    
    CU_ASSERT(point1.y == 3);    
    CU_ASSERT(point1.z == 3); 
}

void test_point_3d_scale_inplace(){
    point_3d point1 = point_3d_create(4,5,6);

    point_3d_scale_inplace(&point1, 2);

    CU_ASSERT(point1.x == 8);    
    CU_ASSERT(point1.y == 10);    
    CU_ASSERT(point1.z == 12); 
}

void test_point_3d_add(){
    point_3d point1 = point_3d_create(1,2,3);
    point_3d point2 = point_3d_create(4,5,6);

    point_3d point3 = point_3d_add(&point1, &point2);

    CU_ASSERT(point3.x == 5);    
    CU_ASSERT(point3.y == 7);    
    CU_ASSERT(point3.z == 9); 
}

void test_point_3d_sub(){
    point_3d point1 = point_3d_create(4,5,6);
    point_3d point2 = point_3d_create(1,2,3);

    point_3d point3 = point_3d_sub(&point1, &point2);

    CU_ASSERT(point3.x == 3);    
    CU_ASSERT(point3.y == 3);    
    CU_ASSERT(point3.z == 3); 
}

void test_point_3d_scale(){
    point_3d point1 = point_3d_create(4,5,6);

    point_3d point3 = point_3d_scale(&point1, 2);

    CU_ASSERT(point3.x == 8);    
    CU_ASSERT(point3.y == 10);    
    CU_ASSERT(point3.z == 12); 
}

void test_compute_norm(){
    point_3d point1 = point_3d_create(4,5,6);

    double norme = compute_norm(&point1);
    CU_ASSERT((int)norme == 8);
}

void test_compute_distance(){
    point_3d point1 = point_3d_create(4,5,6);
    point_3d point2 = point_3d_create(1,2,3);

    double distance = compute_distance(&point1, &point2);
    CU_ASSERT((int)distance == 5);
}

void test_print_point(){
    point_3d point1 = point_3d_create(4,5,6);
    point_3d point2 = point_3d_create(1,2,3);

    CU_ASSERT(point1.x == 4);
    CU_ASSERT(point1.y == 5);
    CU_ASSERT(point1.z == 6);
    
    CU_ASSERT(point2.x == 1);
    CU_ASSERT(point2.y == 2);
    CU_ASSERT(point2.z == 3);
}

void test_point_3d_normalize_in_place(){
    point_3d point1 = point_3d_create(2,4,8);
    point_3d point2 = point_3d_create(2,4,8);
    double norme = sqrt(84);

    point_3d_normalize_in_place(&point1);
    point2.x /= norme;
    point2.y /= norme;
    point2.z /= norme;

    CU_ASSERT(point1.x == point2.x);
    CU_ASSERT(point1.y == point2.y);
    CU_ASSERT(point1.z == point2.z);
}
void test_point_3d_normalize(){
    point_3d point1 = point_3d_create(4,5,6);

    point_3d point2 = point_3d_normalize(&point1);
    point_3d_normalize_in_place(&point1);
    
    CU_ASSERT(point2.x == point1.x);
    CU_ASSERT(point2.y == point1.y);
    CU_ASSERT(point2.z == point1.z);
}
void test_point_3d_vector_product(){
    point_3d point1 = point_3d_create(1,2,3);
    point_3d point2 = point_3d_create(4,5,6);

    point_3d point3 = point_3d_vector_product(&point1, &point2);

    CU_ASSERT(point3.x == -3);
    CU_ASSERT(point3.y == 6);
    CU_ASSERT(point3.z == -3);
}
