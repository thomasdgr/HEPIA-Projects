#include "test_triangulation.h"
#include "../geom/triangulation.h"
#include "../stl/stl.h"
#include "../lidar/lidar.h"
#include "../geom/triangle.h"
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

void test_is_inside_circum_circle_points(){

}

void test_point_max(){
  point_3d p1 = point_3d_create(1,8,0);
  point_3d p2 = point_3d_create(3,6,0);
  point_3d p3 = point_3d_create(5,4,0);
  point_3d p4 = point_3d_create(7,2,0);
  vector_3d points;
  vector_3d_init(&points);
  error_code e1 = vector_3d_push(&points, p1);
  error_code e2 = vector_3d_push(&points, p2);
  error_code e3 = vector_3d_push(&points, p3);
  error_code e4 = vector_3d_push(&points, p4);

  CU_ASSERT(e1 == ok);
  CU_ASSERT(e2 == ok);
  CU_ASSERT(e3 == ok);
  CU_ASSERT(e4 == ok);

  point_3d result = point_3d_create(7,8,0);
  point_3d result_test = point_max(points);
  CU_ASSERT(result.x = result_test.x);
  CU_ASSERT(result.y = result_test.y);

  vector_3d_free(&points);
}

void test_point_min(){
  point_3d p1 = point_3d_create(1,8,0);
  point_3d p2 = point_3d_create(3,6,0);
  point_3d p3 = point_3d_create(5,4,0);
  point_3d p4 = point_3d_create(7,2,0);
  vector_3d points;
  vector_3d_init(&points);
  error_code e1 = vector_3d_push(&points, p1);
  error_code e2 = vector_3d_push(&points, p2);
  error_code e3 = vector_3d_push(&points, p3);
  error_code e4 = vector_3d_push(&points, p4);

  CU_ASSERT(e1 == ok);
  CU_ASSERT(e2 == ok);
  CU_ASSERT(e3 == ok);
  CU_ASSERT(e4 == ok);

  point_3d result = point_3d_create(1,2,0);
  point_3d result_test = point_min(points);
  CU_ASSERT(result.x = result_test.x);
  CU_ASSERT(result.y = result_test.y);

  vector_3d_free(&points);
}

void test_super_triangle_create(){
  point_3d p1 = point_3d_create(1,8,0);
  point_3d p2 = point_3d_create(3,6,0);
  point_3d p3 = point_3d_create(5,4,0);
  point_3d p4 = point_3d_create(7,2,0);
  vector_3d points;
  vector_3d_init(&points);
  vector_3d_push(&points, p1);
  vector_3d_push(&points, p2);
  vector_3d_push(&points, p3);
  vector_3d_push(&points, p4);

  vector_i_triangle triangles;
  vector_i_triangle_init(&triangles);

  super_triangle(&points, &triangles);

  CU_ASSERT(points.content[triangles.content[0].p1].x == 124.0);
  CU_ASSERT(points.content[triangles.content[0].p1].y == 11.0);
  CU_ASSERT(points.content[triangles.content[0].p2].x == 4.0);
  CU_ASSERT(points.content[triangles.content[0].p2].y == -115.0);
  CU_ASSERT(points.content[triangles.content[0].p3].x == -116.0);
  CU_ASSERT(points.content[triangles.content[0].p3].y == 11.0);
  vector_3d_free(&points);
  vector_i_triangle_free(&triangles);
}

void test_bowyer_watson(){

  point_3d point_1 = {79.692045, 177.291743, 0.0};
  point_3d point_2 = {105.876045, 15.998743, 0.0};
  point_3d point_3 = {-249.549955, 146.060743, 0.0};
  point_3d point_4 = {214.277045, 40.505743, 0.0};
  point_3d point_5 = {-246.241955, 164.004743, 0.0};
  point_3d point_6 = {182.411045, 146.041743, 0.0};
  point_3d point_7 = {78.422045, -238.258257, 0.0};
  point_3d point_8 = {149.081045, 152.309743, 0.0};
  point_3d point_9 = {112.333045, 88.411743, 0.0};
  point_3d point_10 = {-116.498955, -186.731257, 0.0};

  vector_3d points;
  vector_3d_init(&points);
  vector_3d_push(&points, point_1);
  vector_3d_push(&points, point_2);
  vector_3d_push(&points, point_3);
  vector_3d_push(&points, point_4);
  vector_3d_push(&points, point_5);
  vector_3d_push(&points, point_6);
  vector_3d_push(&points, point_7);
  vector_3d_push(&points, point_8);
  vector_3d_push(&points, point_9);
  vector_3d_push(&points, point_10);

  vector_i_triangle triangles;
  vector_i_triangle_init(&triangles);

  bowyer_watson(&points, &triangles);

  triangle tab[triangles.length];

  for(int i = 0; i < triangles.length; i++){
    point_3d p_tmp;
    CU_ASSERT(vector_3d_get(&points, triangles.content[i].p1, &p_tmp) == ok);
    point_3d p1 = p_tmp;

    CU_ASSERT(vector_3d_get(&points, triangles.content[i].p2, &p_tmp) == ok);
    point_3d p2 = p_tmp;

    CU_ASSERT(vector_3d_get(&points, triangles.content[i].p3, &p_tmp) == ok);
    point_3d p3 = p_tmp;

    triangle t = triangle_create(p1, p2, p3);
    tab[i] = t;
  }

  stl_file_create_and_write("resultat_triangulation_TABLEAUX.stl", "r", tab, triangles.length);

  vector_3d_free(&points);
  vector_i_triangle_free(&triangles);
}

void test_form_triangle_from_edge_and_point(){
  point_3d p1 = point_3d_create(1,7,0);
  point_3d p2 = point_3d_create(2,6,0);
  point_3d p3 = point_3d_create(3,5,0);
  point_3d p4 = point_3d_create(4,4,0);
  point_3d p5 = point_3d_create(5,3,0);
  point_3d p6 = point_3d_create(6,2,0);
  point_3d p7 = point_3d_create(7,1,0);

  vector_3d points;
  vector_3d_init(&points);
  vector_3d_push(&points, p1);
  vector_3d_push(&points, p2);
  vector_3d_push(&points, p3);
  vector_3d_push(&points, p4);
  vector_3d_push(&points, p5);
  vector_3d_push(&points, p6);
  vector_3d_push(&points, p7);

  i_edge arrete = i_edge_create(2,6);
  point_3d p_tmp;
  CU_ASSERT(vector_3d_get(&points, arrete.p1, &p_tmp) == ok);
  CU_ASSERT(p_tmp.x == 3.0);
  CU_ASSERT(p_tmp.y == 5.0);
  CU_ASSERT(vector_3d_get(&points, arrete.p2, &p_tmp) == ok);
  CU_ASSERT(p_tmp.x == 7.0);
  CU_ASSERT(p_tmp.y == 1.0);

  i_triangle t = form_triangle_from_edge_and_point(arrete, 2);
  CU_ASSERT(vector_3d_get(&points, t.p1, &p_tmp) == ok);
  CU_ASSERT(p_tmp.x == 3.0);
  CU_ASSERT(p_tmp.y == 5.0);
  CU_ASSERT(vector_3d_get(&points, t.p2, &p_tmp) == ok);
  CU_ASSERT(p_tmp.x == 3.0);
  CU_ASSERT(p_tmp.y == 5.0);
  CU_ASSERT(vector_3d_get(&points, t.p3, &p_tmp) == ok);
  CU_ASSERT(p_tmp.x == 7.0);
  CU_ASSERT(p_tmp.y == 1.0);

  vector_3d_free(&points);
}
