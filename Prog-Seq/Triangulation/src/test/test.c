/**********************************************************************************************************************************************************************************************************************************\
		         ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de tests pour chaque librairie utilisées au cours de l'execution
 __/  |    | \__/|               |                 du  programme à l'eception des listes_2d, listes_3d, listes_i_edge,
(___) \.  _.\__. `\___           |                 listes_i_triangle et listes_triangulation
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "test_filter_functions.h"
#include "test_map_functions.h"
#include "test_vector.h"
#include "test_point_3d.h"
#include "test_triangle.h"
#include "test_lidar.h"
#include "test_triangulation.h"
#include "test_triangulation_lst.h"
#include "test_lst_vector.h"
#include "test_stl.h"
#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

int main() {
    CU_pSuite lidar_suite = NULL;
    CU_pSuite point_3d_suite = NULL;
    CU_pSuite vector_list_suite = NULL;
    CU_pSuite vector_suite = NULL;
    CU_pSuite filter_suite = NULL;
    CU_pSuite map_suite = NULL;
    CU_pSuite triangle_suite = NULL;
    CU_pSuite stl_suite = NULL;
    CU_pSuite triangulation_array_suite = NULL;
    CU_pSuite triangulation_lst_suite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

    /* add a suite to the registry */
    filter_suite = CU_add_suite("Filter suite", NULL, NULL);
    if (NULL == filter_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(filter_suite, "test of is_even", test_is_even)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    map_suite = CU_add_suite("Map suite", NULL, NULL);
    if (NULL == map_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(map_suite, "test of square", test_square)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    vector_suite = CU_add_suite("Vector suite", NULL, NULL);
    if (NULL == vector_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(vector_suite, "test of vector_init", test_vector_init)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_is_equal", test_vector_is_equal)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_free", test_vector_free)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_length", test_vector_length)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_push", test_vector_push)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_pop", test_vector_pop)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_set", test_vector_set)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_get", test_vector_get)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_remove", test_vector_remove)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_insert", test_vector_insert)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_empty", test_vector_empty)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_map", test_vector_map)) ||
        (NULL == CU_add_test(vector_suite, "test of vector_filter", test_vector_filter)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add a suite to the registry */
    lidar_suite = CU_add_suite("Lidar suite", NULL, NULL);
    if (NULL == lidar_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(lidar_suite, "test of header_from_file", test_las_header_from_file)) ||
        (NULL == CU_add_test(lidar_suite, "test of print_header", test_print_header)) ||
        (NULL == CU_add_test(lidar_suite, "test of points_from_file", test_las_points_from_file)) ||
        (NULL == CU_add_test(lidar_suite, "test of print_point_record", test_print_point_record)))
    /*if ((NULL == CU_add_test(lidar_suite, "test of print_header", test_print_header)))*/
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add a suite to the registry */
    point_3d_suite = CU_add_suite("point_3d suite", NULL, NULL);
    if (NULL == point_3d_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(point_3d_suite, "test of point_3d_create", test_point_3d_create)) ||
        (NULL == CU_add_test(point_3d_suite, "test of point_3d_add_inplace", test_point_3d_add_inplace)) ||
        (NULL == CU_add_test(point_3d_suite, "test of point_3d_sub_inplace", test_point_3d_sub_inplace)) ||
        (NULL == CU_add_test(point_3d_suite, "test of point_3d_scale_inplace", test_point_3d_scale_inplace)) ||
        (NULL == CU_add_test(point_3d_suite, "test of point_3d_normalize_in_place", test_point_3d_normalize_in_place)) ||
        (NULL == CU_add_test(point_3d_suite, "test of point_3d_add", test_point_3d_add)) ||
        (NULL == CU_add_test(point_3d_suite, "test of point_3d_sub", test_point_3d_sub)) ||
        (NULL == CU_add_test(point_3d_suite, "test of point_3d_scale", test_point_3d_scale)) ||
        (NULL == CU_add_test(point_3d_suite, "test of point_3d_normalize", test_point_3d_normalize)) ||
        (NULL == CU_add_test(point_3d_suite, "test of compute_norm", test_compute_norm)) ||
        (NULL == CU_add_test(point_3d_suite, "test of compute_distance", test_compute_distance)) ||
        (NULL == CU_add_test(point_3d_suite, "test of point_3d_vector_product", test_point_3d_vector_product)) ||
        (NULL == CU_add_test(point_3d_suite, "test of print_point", test_print_point)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add a suite to the registry */
    triangle_suite = CU_add_suite("Triangle suite", NULL, NULL);
    if (NULL == triangle_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(triangle_suite, "test of triangle_create", test_triangle_create)) ||
        (NULL == CU_add_test(triangle_suite, "test of triangle_compute_norm", test_triangle_compute_normal)) ||
        (NULL == CU_add_test(triangle_suite, "test of triangle_compute_area", test_triangle_compute_area)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add a suite to the registry */
    stl_suite = CU_add_suite("STL suite", NULL, NULL);
    if (NULL == stl_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(stl_suite, "test of test_stl_file_create", test_stl_file_create)) ||
        (NULL == CU_add_test(stl_suite, "test of test_stl_file_close", test_stl_file_close)) ||
        (NULL == CU_add_test(stl_suite, "test of test_stl_file_write_triangle", test_stl_file_write_triangle)) ||
        (NULL == CU_add_test(stl_suite, "test of test_stl_file_create_and_write", test_stl_file_create_and_write)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add a suite to the registry */
    triangulation_array_suite = CU_add_suite("Triangulation Array suite", NULL, NULL);
    if (NULL == triangulation_array_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(triangulation_array_suite, "test of test_super_triangle_create", test_super_triangle_create)) ||
        (NULL == CU_add_test(triangulation_array_suite, "test of test_point_max", test_point_max)) ||
        (NULL == CU_add_test(triangulation_array_suite, "test of test_point_min", test_point_min)) ||
        (NULL == CU_add_test(triangulation_array_suite, "test of test_bowyer_watson", test_bowyer_watson)) ||
        (NULL == CU_add_test(triangulation_array_suite, "test of test_is_inside_circum_circle_points", test_is_inside_circum_circle_points)) ||
        (NULL == CU_add_test(triangulation_array_suite, "test of test_form_triangle_from_edge_and_point", test_form_triangle_from_edge_and_point)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add a suite to the registry */
    vector_list_suite = CU_add_suite("Vector_List suite", NULL, NULL);
    if (NULL == vector_list_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_init", test_lst_vector_init)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_is_equal", test_lst_vector_is_equal)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_length", test_lst_vector_length)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_push", test_lst_vector_push)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_pop", test_lst_vector_pop)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_set", test_lst_vector_set)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_get", test_lst_vector_get)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_remove", test_lst_vector_remove)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_insert", test_lst_vector_insert)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_empty", test_lst_vector_empty)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_free", test_lst_vector_free)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_map", test_lst_vector_map)) ||
        (NULL == CU_add_test(vector_list_suite, "test of test_lst_vector_filter", test_lst_vector_filter)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add a suite to the registry */
    triangulation_lst_suite = CU_add_suite("Triangulation List suite", NULL, NULL);
    if (NULL == triangulation_lst_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(triangulation_lst_suite, "test of test_lst_super_triangle_create", test_lst_super_triangle_create)) ||
        (NULL == CU_add_test(triangulation_lst_suite, "test of test_lst_point_max", test_lst_point_max)) ||
        (NULL == CU_add_test(triangulation_lst_suite, "test of test_lst_point_min", test_lst_point_min)) ||
        (NULL == CU_add_test(triangulation_lst_suite, "test of test_lst_bowyer_watson", test_lst_bowyer_watson)) ||
        (NULL == CU_add_test(triangulation_lst_suite, "test of test_lst_is_inside_circum_circle_points", test_lst_is_inside_circum_circle_points)) ||
        (NULL == CU_add_test(triangulation_lst_suite, "test of test_lst_form_triangle_from_edge_and_point", test_lst_form_triangle_from_edge_and_point)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic (console output) and Automated (xml output) interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    CU_automated_run_tests();

    // return CU_get_error();
    return CU_get_number_of_tests_failed();
}
