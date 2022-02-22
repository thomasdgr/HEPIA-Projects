/*******************************************************************************
			 ____
           /____ \               |  Projet : C_FF
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : librairie de fonctions
 __/  |    | \__/|               |    utilisées pour faire des tests sur le reste
(___) \.  _.\__. `\___           |    du projet et vérifier le bon fonctionnement
(___)  )\/  \_____/  ~\.         |    
(___) . \   `         `\         |   
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		 |	Date :	03/06/2020

\******************************************************************************/
#include "test_priority_queue.h"
#include "test_heapsort.h"
#include "test_list.h"
#include "test_matrix.h"
#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

int main() {
    CU_pSuite priority_queue = NULL;
    CU_pSuite heapsort = NULL;
    CU_pSuite list = NULL;
    CU_pSuite matrix = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

    priority_queue = CU_add_suite("Priority lane suite", NULL, NULL);
    if (NULL == priority_queue) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(priority_queue, "test of priority_queue", test_priority_queue)) ||
        (NULL == CU_add_test(priority_queue, "test of priority_queue_generic", test_priority_queue_generic)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    heapsort = CU_add_suite("Heapsort suite", NULL, NULL);
    if (NULL == heapsort) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(heapsort, "test of heapsort", test_heapsort)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    list = CU_add_suite("City List suite", NULL, NULL);
    if (NULL == list) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(list, "test of city_list", test_city_list)) ||
        (NULL == CU_add_test(list, "test of connection_list", test_connection_list)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    matrix = CU_add_suite("Matrix suite", NULL, NULL);
    if (NULL == matrix) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(matrix, "test of matrix", test_matrix)))

    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic (console output) and Automated (xml output) interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    printf("\n");
    //CU_basic_show_failures(CU_get_failure_list()); // montrer les echecs en fin de tests

    CU_automated_run_tests();

    // return CU_get_error();
    return CU_get_number_of_tests_failed();
}
