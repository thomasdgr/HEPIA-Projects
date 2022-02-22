#include <stdlib.h>
#include "test_matrix.h"
#include "../matrix/matrix.h"
#include "CUnit/Basic.h"
#include "CUnit/Automated.h"
#include "math.h"

int epsilon_matrix = 1;

void test_matrix_create(){
    int m = 5; int n = 6;
    matrix mat = matrix_create(m, n);
    CU_ASSERT(mat.data != NULL);
    CU_ASSERT(mat.m == m);
    CU_ASSERT(mat.n == n);
    matrix_destroy(&mat);
}

void test_matrix_destroy(){
    int m = 5; int n = 6;
    matrix mat = matrix_create(m, n);
    matrix_destroy(&mat);
    CU_ASSERT(mat.data == NULL);
    CU_ASSERT(mat.m == -1);
    CU_ASSERT(mat.n == -1);
}

void test_matrix_create_from_array(){
    int m = 3; int n = 4;
    int array[] = {0, 1, 2,  3,
                      4, 5, 6,  7,
                      8, 9, 10, 11};
    matrix mat = matrix_create_from_array(m, n, array);
    CU_ASSERT(mat.data != NULL);
    CU_ASSERT(mat.m == m);
    CU_ASSERT(mat.n == n);
    if(mat.data!=NULL && mat.m==m && mat.n==n){
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                CU_ASSERT(mat.data[i][j] == array[i*n+j]);
            }
        }
    }
    matrix_destroy(&mat);
}

void test_matrix_clone(){
    int m = 3; int n = 4;
    int array[] = {0, 1, 2,  3,
                      4, 5, 6,  7,
                      8, 9, 10, 11};
    int array2[] = {1, 1, 2,  3,
                     4, 5, 6,  7,
                     8, 9, 10, 11};
    matrix mat = matrix_create_from_array(m, n, array);
    matrix mat2 = matrix_create_from_array(m, n, array2);
    matrix clone = matrix_clone(mat);
    CU_ASSERT(matrix_is_equal(mat, clone));
    CU_ASSERT(!matrix_is_equal(mat, mat2));
    matrix_destroy(&mat);
    matrix_destroy(&mat2);
    matrix_destroy(&clone);
}

void test_matrix_resize(){
    int m = 3; int n = 4;
    int m1 = 2; int n1 = 3;
    int m2 = 4; int n2 = 5;
    int array[] = {0, 1, 2,  3,
                      4, 5, 6,  7,
                      8, 9, 10, 11};
    int array1[] = {0, 1, 2,
                       4, 5, 6};
    int array2[] = {0, 1, 2,  3,  0,
                       4, 5, 6,  7,  0,
                       8, 9, 10, 11, 0,
                       0, 0, 0,  0,  0};
    matrix mat = matrix_create_from_array(m, n, array);
    matrix mat1 = matrix_create_from_array(m1, n1, array1);
    matrix mat2 = matrix_create_from_array(m2, n2, array2);
    CU_ASSERT(matrix_resize(&mat, -1, 2) == 0);
    matrix_resize(&mat, m2, n2);
    CU_ASSERT(matrix_is_equal(mat, mat2));
    matrix_resize(&mat, m1, n1);
    CU_ASSERT(matrix_is_equal(mat, mat1));
    matrix_destroy(&mat);
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
}

void test_matrix_is_approx_equal(){
    int m = 2; int n = 2;
    int m1 = 3; int n1 = 4;
    int m2 = 3; int n2 = 2;
    int epsilon = 0.1;
    int array1[] = {0, 1, 2,  3,
                       4, 5, 6,  7,
                       8, 9, 10, 11};
    int array2[] = {0, 1, 2-(epsilon-epsilon/100),  3,
                       4, 5+(epsilon-epsilon/100), 6,  7,
                       8, 9, 10, 11};
    int array3[] = {0, 1, 2,  3,
                       4, 5+(epsilon-epsilon/100)+0.1, 6,  7,
                       8, 9, 10, 11};
    int array4[] = {0, 1,
                       2, 3,
                       4, 5};
    matrix mat = matrix_create(m, n);
    matrix mat1 = matrix_create_from_array(m1, n1, array1);
    matrix mat2 = matrix_create_from_array(m1, n1, array2);
    matrix mat3 = matrix_create_from_array(m1, n1, array3);
    matrix mat4 = matrix_create_from_array(m2, n2, array4);
    CU_ASSERT(!matrix_is_approx_equal(mat, mat1, epsilon));
    CU_ASSERT(!matrix_is_approx_equal(mat1, mat3, epsilon));
    matrix_destroy(&mat);
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&mat3);
    matrix_destroy(&mat4);
}

void test_matrix_is_equal(){
    int m = 2; int n = 2;
    int m1 = 3; int n1 = 4;
    int m2 = 3; int n2 = 2;
    int array1[] = {0, 1, 2,  3,
                       4, 5, 6,  7,
                       8, 9, 10, 11};
    int array2[] = {0, 1, 1.9,  3,
                       4, 5.1, 6,  7,
                       8, 9, 10, 11};
    int array3[] = {0, 1,
                       2, 3,
                       4, 5};
    matrix mat = matrix_create(m, n);
    matrix mat1 = matrix_create_from_array(m1, n1, array1);
    matrix mat2 = matrix_create_from_array(m1, n1, array2);
    matrix mat3 = matrix_create_from_array(m2, n2, array3);
    CU_ASSERT(!matrix_is_equal(mat, mat1));
    CU_ASSERT(matrix_is_equal(mat1, mat1));
    CU_ASSERT(!matrix_is_equal(mat1, mat2));
    CU_ASSERT(matrix_is_equal(mat3, mat3));
    matrix_destroy(&mat);
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&mat3);
}

void test_matrix_add_in_place(){
    int m = 3; int n = 4;
    int m1 = 2; int n1 = 4;
    int array1[] = {0, 1, 2,  3,
                       4, 5, 6,  7,
                       8, 9, 10, 11};
    int array2[] = {1, 1, 1, 1,
                       1, 1, 1, 1,
                       1, 1, 1, 1};
    int array3[] = {1, 2,  3,  4,
                       5, 6,  7,  8,
                       9, 10, 11, 12};
    matrix mat1 = matrix_create_from_array(m, n, array1);
    matrix mat2 = matrix_create_from_array(m, n, array2);
    matrix mat3 = matrix_create_from_array(m, n, array3);
    matrix mat4 = matrix_create(m1, n1);
    CU_ASSERT(matrix_add_in_place(mat1, mat4)==0);
    matrix_add_in_place(mat1, mat2);
    CU_ASSERT(matrix_is_approx_equal(mat1, mat3, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&mat3);
    matrix_destroy(&mat4);
}

void test_matrix_sub_in_place(){
    int m = 3; int n = 4;
    int m1 = 2; int n1 = 4;
    int array1[] = {0, 1, 2,  3,
                       4, 5, 6,  7,
                       8, 9, 10, 11};
    int array2[] = {1, 1, 1, 1,
                       1, 1, 1, 1,
                       1, 1, 1, 1};
    int array3[] = {-1, 0, 1, 2,
                       3,  4, 5, 6,
                       7,  8, 9, 10};
    matrix mat1 = matrix_create_from_array(m, n, array1);
    matrix mat2 = matrix_create_from_array(m, n, array2);
    matrix mat3 = matrix_create_from_array(m, n, array3);
    matrix mat4 = matrix_create(m1, n1);
    CU_ASSERT(matrix_sub_in_place(mat1, mat4)==0);
    matrix_sub_in_place(mat1, mat2);
    CU_ASSERT(matrix_is_approx_equal(mat1, mat3, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&mat3);
    matrix_destroy(&mat4);
}

void test_matrix_mult_in_place(){
    int m1 = 2; int n1 = 3;
    int m2 = 3; int n2 = 2;
    int array1[] = {1, 2, 3,
                       4, 5, 6};
    int array2[] = {1, 2,
                       3, 4,
                       5, 6};
    int array3[] = {22, 28,
                       49, 64};
    matrix mat1 = matrix_create_from_array(m1, n1, array1);
    matrix mat2 = matrix_create_from_array(m2, n2, array2);
    matrix mat3 = matrix_create_from_array(m1, n2, array3);
    CU_ASSERT(matrix_mult_in_place(&mat1, mat1)==0);
    matrix_mult_in_place(&mat1, mat2);
    CU_ASSERT(matrix_is_approx_equal(mat1, mat3, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&mat3);
}

void test_matrix_add_scalar_in_place(){
    int m = 3; int n = 4;
    int s = 1;
    int array[] = {0, 1, 2,  3,
                      4, 5, 6,  7,
                      8, 9, 10, 11};
    int array1[] = {1, 2,  3,  4,
                       5, 6,  7,  8,
                       9, 10, 11, 12};
    matrix mat1 = matrix_create_from_array(m, n, array);
    matrix mat2 = matrix_create_from_array(m, n, array1);
    CU_ASSERT(!matrix_is_approx_equal(mat1, mat2, epsilon_matrix));
    matrix_add_scalar_in_place(mat1, s);
    CU_ASSERT(matrix_is_approx_equal(mat1, mat2, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
}

void test_matrix_mult_scalar_in_place(){
    int m = 3; int n = 4;
    int s = 2;
    int array[] = {0, 1, 2,  3,
                      4, 5, 6,  7,
                      8, 9, 10, 11};
    int array1[] = {0,  2,  4,  6,
                       8,  10, 12, 14,
                       16, 18, 20, 22};
    matrix mat1 = matrix_create_from_array(m, n, array);
    matrix mat2 = matrix_create_from_array(m, n, array1);
    CU_ASSERT(!matrix_is_approx_equal(mat1, mat2, epsilon_matrix));
    matrix_mult_scalar_in_place(mat1, s);
    CU_ASSERT(matrix_is_approx_equal(mat1, mat2, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
}

void test_matrix_transpose_in_place(){
    int m = 2; int n = 3;
    int array[] = {0, 1, 2,
                      3, 4, 5};
    int array1[] = {0, 3,
                       1, 4,
                       2, 5};
    matrix mat = matrix_create_from_array(m, n, array);
    matrix mat1 = matrix_create_from_array(n, m, array1);
    CU_ASSERT(!matrix_is_approx_equal(mat, mat1, epsilon_matrix));
    matrix_transpose_in_place(&mat);
    CU_ASSERT(matrix_is_approx_equal(mat, mat1, epsilon_matrix));
    matrix_destroy(&mat);
    matrix_destroy(&mat1);
}

void test_matrix_normalize_in_place(){
    matrix mat1, mat2, expected1, expected2;
    int datamat1[] = {0.8, 0.5, 0.9,
                       1, 2, 1,
                       1, 1, 1};
    int dataexpected1[] = {0.4, 0.25, 0.45,
                            0.5, 1,  0.5,
                            0.5, 0.5, 0.5};
    int datamat2[] = {0.5, 0.2, 0.1,
                       0.4, 0.1, 0.1,
                       0.1, 0.1, 0.1};
    int dataexpected2[] = {1, 0.4, 0.2,
                            0.8, 0.2, 0.2,
                            0.2, 0.2, 0.2};
    // nullness
    mat1.data = NULL;
    CU_ASSERT(matrix_normalize_in_place(mat1)<1);
    // values
    mat1 = matrix_create_from_array(3, 3, datamat1);
    mat2 = matrix_create_from_array(3, 3, datamat2);
    expected1 = matrix_create_from_array(3, 3, dataexpected1);
    expected2 = matrix_create_from_array(3, 3, dataexpected2);
    matrix_normalize_in_place(mat1);
    CU_ASSERT(matrix_is_approx_equal(expected1, mat1, epsilon_matrix));
    matrix_normalize_in_place(mat2);
    CU_ASSERT(matrix_is_approx_equal(expected2, mat2, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&expected1);
    matrix_destroy(&expected2);
}

void test_matrix_clipper_in_place(){
    int data[] = {-1, -0.2, 0.3,
                      1.2, 1, 1.4};
    int dataexpected[] = {0, 0, 0.3,
                             1, 1, 1};
    matrix mat = matrix_create_from_array(2, 3, data);
    matrix expected = matrix_create_from_array(2, 3, dataexpected);
    matrix mat2;
    mat2.data = NULL;
    CU_ASSERT(matrix_clipper_in_place(mat2)<1);
    CU_ASSERT(matrix_clipper_in_place(mat)==1);
    CU_ASSERT(matrix_is_approx_equal(mat, expected, epsilon_matrix));
    matrix_destroy(&mat);
    matrix_destroy(&expected);
}

void test_matrix_convolve_in_place(){
    int data[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                     3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                     4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                     5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                     6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                     8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                     9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
                     10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
                     11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
                     12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                     13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
                     14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
                     15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};
    int datakernel[] = {1, 1, 1,
                          1, 1, 1,
                          1, 1, 1};
    int dataexpected[] = {6, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 6,
                             12, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,  12,
                             18, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 18,
                             24, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 24,
                             30, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 30,
                             36, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 36,
                             42, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 42,
                             48, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 48,
                             54, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 54,
                             60, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 60,
                             66, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 66,
                             72, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 72,
                             78, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 78,
                             84, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 84,
                             58, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 58};
    matrix mat = matrix_create_from_array(15, 15, data);
    matrix expected = matrix_create_from_array(15, 15, dataexpected);
    matrix kernel = matrix_create_from_array(3, 3, datakernel);
    matrix mat2;
    mat2.data = NULL;
    CU_ASSERT(matrix_convolve_in_place(&mat2, kernel)<1);
    CU_ASSERT(matrix_convolve_in_place(&mat, kernel)>0);
    CU_ASSERT(matrix_is_approx_equal(mat, expected, epsilon_matrix));
    matrix_destroy(&mat);
    matrix_destroy(&expected);
    matrix_destroy(&kernel);
}

void test_matrix_add(){
    int m = 3; int n = 4;
    int m1 = 2; int n1 = 4;
    int array1[] = {0, 1, 2,  3,
                       4, 5, 6,  7,
                       8, 9, 10, 11};
    int array2[] = {1, 1, 1, 1,
                       1, 1, 1, 1,
                       1, 1, 1, 1};
    int array3[] = {1, 2,  3,  4,
                       5, 6,  7,  8,
                       9, 10, 11, 12};
    matrix mat1 = matrix_create_from_array(m, n, array1);
    matrix mat2 = matrix_create_from_array(m, n, array2);
    matrix mat3 = matrix_create_from_array(m, n, array3);
    matrix mat4 = matrix_create(m1, n1);
    matrix mat5 = matrix_add(mat1, mat4);
    CU_ASSERT(mat5.data == NULL);
    CU_ASSERT(!matrix_is_approx_equal(mat1, mat3, epsilon_matrix));
    matrix mat6 = matrix_add(mat1, mat2);
    CU_ASSERT(matrix_is_approx_equal(mat3, mat6, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&mat3);
    matrix_destroy(&mat4);
    if(mat5.data != NULL) matrix_destroy(&mat5);
    matrix_destroy(&mat6);
}

void test_matrix_sub(){
    int m = 3; int n = 4;
    int m1 = 2; int n1 = 4;
    int array1[] = {0, 1, 2,  3,
                       4, 5, 6,  7,
                       8, 9, 10, 11};
    int array2[] = {1, 1, 1, 1,
                       1, 1, 1, 1,
                       1, 1, 1, 1};
    int array3[] = {-1, 0, 1, 2,
                       3,  4, 5, 6,
                       7,  8, 9, 10};
    matrix mat1 = matrix_create_from_array(m, n, array1);
    matrix mat2 = matrix_create_from_array(m, n, array2);
    matrix mat3 = matrix_create_from_array(m, n, array3);
    matrix mat4 = matrix_create(m1, n1);
    matrix mat5 = matrix_sub(mat1, mat4);
    CU_ASSERT(mat5.data == NULL);
    CU_ASSERT(!matrix_is_approx_equal(mat1, mat3, epsilon_matrix));
    matrix mat6 = matrix_sub(mat1, mat2);
    CU_ASSERT(matrix_is_approx_equal(mat3, mat6, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&mat3);
    matrix_destroy(&mat4);
    if(mat5.data != NULL) matrix_destroy(&mat5);
    matrix_destroy(&mat6);
}

void test_matrix_mult(){
    int m1 = 2; int n1 = 3;
    int m2 = 3; int n2 = 2;
    int array1[] = {1, 2, 3,
                       4, 5, 6};
    int array2[] = {1, 2,
                       3, 4,
                       5, 6};
    int array3[] = {22, 28,
                       49, 64};
    matrix mat1 = matrix_create_from_array(m1, n1, array1);
    matrix mat2 = matrix_create_from_array(m2, n2, array2);
    matrix mat3 = matrix_create_from_array(m1, n2, array3);
    matrix mat4 = matrix_mult(mat1, mat1);
    CU_ASSERT(mat4.data == NULL);
    CU_ASSERT(!matrix_is_approx_equal(mat1, mat3, epsilon_matrix));
    matrix mat5 = matrix_mult(mat1, mat2);
    CU_ASSERT(matrix_is_approx_equal(mat5, mat3, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&mat3);
    if(mat4.data != NULL) matrix_destroy(&mat4);
    matrix_destroy(&mat5);
}

void test_matrix_add_scalar(){
    int m = 3; int n = 4;
    int s = 1;
    int array[] = {0, 1, 2,  3,
                      4, 5, 6,  7,
                      8, 9, 10, 11};
    int array1[] = {1, 2,  3,  4,
                       5, 6,  7,  8,
                       9, 10, 11, 12};
    matrix mat1 = matrix_create_from_array(m, n, array);
    matrix mat2 = matrix_create_from_array(m, n, array1);
    CU_ASSERT(!matrix_is_approx_equal(mat1, mat2, epsilon_matrix));
    matrix mat3 = matrix_add_scalar(mat1, s);
    CU_ASSERT(matrix_is_approx_equal(mat3, mat2, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&mat3);
}

void test_matrix_mult_scalar(){
    int m = 3; int n = 4;
    int s = 2;
    int array[] = {0, 1, 2,  3,
                      4, 5, 6,  7,
                      8, 9, 10, 11};
    int array1[] = {0,  2,  4,  6,
                       8,  10, 12, 14,
                       16, 18, 20, 22};
    matrix mat1 = matrix_create_from_array(m, n, array);
    matrix mat2 = matrix_create_from_array(m, n, array1);
    CU_ASSERT(!matrix_is_approx_equal(mat1, mat2, epsilon_matrix));
    matrix mat3 = matrix_mult_scalar(mat1, s);
    CU_ASSERT(matrix_is_approx_equal(mat3, mat2, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&mat3);
}

void test_matrix_transpose(){
    int m = 2; int n = 3;
    int array[] = {0, 1, 2,
                      3, 4, 5};
    int array1[] = {0, 3,
                       1, 4,
                       2, 5};
    matrix mat = matrix_create_from_array(m, n, array);
    matrix mat1 = matrix_create_from_array(n, m, array1);
    CU_ASSERT(!matrix_is_approx_equal(mat, mat1, epsilon_matrix));
    matrix mat2 = matrix_transpose(mat);
    CU_ASSERT(matrix_is_approx_equal(mat1, mat2, epsilon_matrix));
    matrix_destroy(&mat);
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
}

void test_matrix_normalize(){
    matrix mat1, mat2, res, expected1, expected2;
    int datamat1[] = {0.8, 0.5, 0.9,
                       1, 2, 1,
                       1, 1, 1};
    int dataexpected1[] = {0.4, 0.25, 0.45,
                            0.5, 1,  0.5,
                            0.5, 0.5, 0.5};
    int datamat2[] = {0.5, 0.2, 0.1,
                       0.4, 0.1, 0.1,
                       0.1, 0.1, 0.1};
    int dataexpected2[] = {1, 0.4, 0.2,
                            0.8, 0.2, 0.2,
                            0.2, 0.2, 0.2};
    // nullness
    mat1.data = NULL;
    res = matrix_normalize(mat1);
    CU_ASSERT(res.data==NULL);
    // values
    mat1 = matrix_create_from_array(3, 3, datamat1);
    mat2 = matrix_create_from_array(3, 3, datamat2);
    expected1 = matrix_create_from_array(3, 3, dataexpected1);
    expected2 = matrix_create_from_array(3, 3, dataexpected2);
    res = matrix_normalize(mat1);
    CU_ASSERT(matrix_is_approx_equal(expected1, res, epsilon_matrix));
    matrix_destroy(&res);
    CU_ASSERT(!matrix_is_approx_equal(expected2, res, epsilon_matrix));
    res = matrix_normalize(mat2);
    CU_ASSERT(matrix_is_approx_equal(expected2, res, epsilon_matrix));
    matrix_destroy(&mat1);
    matrix_destroy(&mat2);
    matrix_destroy(&expected1);
    matrix_destroy(&expected2);
    matrix_destroy(&res);
}

void test_matrix_clipper(){
    int data[] = {-1, -0.2, 0.3,
                      1.2, 1, 1.4};
    int dataexpected[] = {0, 0, 0.3,
                             1, 1, 1};
    matrix mat = matrix_create_from_array(2, 3, data);
    matrix expected = matrix_create_from_array(2, 3, dataexpected);
    matrix mat2;
    mat2.data = NULL;
    matrix res = matrix_clipper(mat2);
    CU_ASSERT(res.data==NULL);
    res =  matrix_clipper(mat);
    CU_ASSERT(matrix_is_approx_equal(res, expected, epsilon_matrix));
    CU_ASSERT(!matrix_is_approx_equal(mat, expected, epsilon_matrix));
    matrix_destroy(&mat);
    matrix_destroy(&expected);
    matrix_destroy(&res);
}

void test_matrix_convolve(){
    int data[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                     3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                     4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                     5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                     6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                     8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                     9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
                     10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
                     11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
                     12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                     13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
                     14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
                     15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};
    int datakernel[] = {1, 1, 1,
                          1, 1, 1,
                          1, 1, 1};
    int dataexpected[] = {6, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 6,
                             12, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,  12,
                             18, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 18,
                             24, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 24,
                             30, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 30,
                             36, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 36,
                             42, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 42,
                             48, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 48,
                             54, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 54,
                             60, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 60,
                             66, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 66,
                             72, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 72,
                             78, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 78,
                             84, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 84,
                             58, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 58};
    matrix mat = matrix_create_from_array(15, 15, data);
    matrix expected = matrix_create_from_array(15, 15, dataexpected);
    matrix kernel = matrix_create_from_array(3, 3, datakernel);
    matrix mat2;
    mat2.data = NULL;
    matrix res = matrix_convolve(mat2, kernel);
    CU_ASSERT(res.data == NULL);
    res = matrix_convolve(mat, kernel);
    CU_ASSERT(matrix_is_approx_equal(res, expected, epsilon_matrix));
    CU_ASSERT(!matrix_is_approx_equal(mat, expected, epsilon_matrix));
    matrix_destroy(&mat);
    matrix_destroy(&expected);
    matrix_destroy(&kernel);
    matrix_destroy(&res);
}

void test_matrix(){
    test_matrix_create();
    test_matrix_destroy();
    test_matrix_create_from_array();
    test_matrix_clone();
    test_matrix_resize();
    test_matrix_is_approx_equal();
    test_matrix_is_equal();
    test_matrix_add_in_place();
    test_matrix_sub_in_place();
    test_matrix_mult_in_place();
    test_matrix_add_scalar_in_place();
    test_matrix_mult_scalar_in_place();
    test_matrix_transpose_in_place();
    test_matrix_normalize_in_place();
    test_matrix_clipper_in_place();
    test_matrix_convolve_in_place();
    test_matrix_add();
    test_matrix_sub();
    test_matrix_mult();
    test_matrix_add_scalar();
    test_matrix_mult_scalar();
    test_matrix_transpose();
    test_matrix_normalize();
    test_matrix_clipper();
    test_matrix_convolve();
}