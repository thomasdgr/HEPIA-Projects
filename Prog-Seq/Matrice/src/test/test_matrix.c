#include <stdlib.h>
#include "test_matrix.h"
#include "../matrix.h"
#include "CUnit/Basic.h"
#include "CUnit/Automated.h"
#include "math.h"

double epsilon_matrix = 0.000001;

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
    double array[] = {0.0, 1.0, 2.0,  3.0,
                      4.0, 5.0, 6.0,  7.0,
                      8.0, 9.0, 10.0, 11.0};
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
    double array[] = {0.0, 1.0, 2.0,  3.0,
                      4.0, 5.0, 6.0,  7.0,
                      8.0, 9.0, 10.0, 11.0};
    double array2[] = {1.0, 1.0, 2.0,  3.0,
                     4.0, 5.0, 6.0,  7.0,
                     8.0, 9.0, 10.0, 11.0};
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
    double array[] = {0.0, 1.0, 2.0,  3.0,
                      4.0, 5.0, 6.0,  7.0,
                      8.0, 9.0, 10.0, 11.0};
    double array1[] = {0.0, 1.0, 2.0,
                       4.0, 5.0, 6.0};
    double array2[] = {0.0, 1.0, 2.0,  3.0,  0.0,
                       4.0, 5.0, 6.0,  7.0,  0.0,
                       8.0, 9.0, 10.0, 11.0, 0.0,
                       0.0, 0.0, 0.0,  0.0,  0.0};
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
    double epsilon = 0.1;
    double array1[] = {0.0, 1.0, 2.0,  3.0,
                       4.0, 5.0, 6.0,  7.0,
                       8.0, 9.0, 10.0, 11.0};
    double array2[] = {0.0, 1.0, 2.0-(epsilon-epsilon/100.0),  3.0,
                       4.0, 5.0+(epsilon-epsilon/100.0), 6.0,  7.0,
                       8.0, 9.0, 10.0, 11.0};
    double array3[] = {0.0, 1.0, 2.0,  3.0,
                       4.0, 5.0+(epsilon-epsilon/100.0)+0.1, 6.0,  7.0,
                       8.0, 9.0, 10.0, 11.0};
    double array4[] = {0.0, 1.0,
                       2.0, 3.0,
                       4.0, 5.0};
    matrix mat = matrix_create(m, n);
    matrix mat1 = matrix_create_from_array(m1, n1, array1);
    matrix mat2 = matrix_create_from_array(m1, n1, array2);
    matrix mat3 = matrix_create_from_array(m1, n1, array3);
    matrix mat4 = matrix_create_from_array(m2, n2, array4);
    CU_ASSERT(!matrix_is_approx_equal(mat, mat1, epsilon));
    CU_ASSERT(matrix_is_approx_equal(mat1, mat2, epsilon));
    CU_ASSERT(!matrix_is_approx_equal(mat1, mat3, epsilon));
    CU_ASSERT(matrix_is_approx_equal(mat4, mat4, epsilon));
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
    double array1[] = {0.0, 1.0, 2.0,  3.0,
                       4.0, 5.0, 6.0,  7.0,
                       8.0, 9.0, 10.0, 11.0};
    double array2[] = {0.0, 1.0, 1.9,  3.0,
                       4.0, 5.1, 6.0,  7.0,
                       8.0, 9.0, 10.0, 11.0};
    double array3[] = {0.0, 1.0,
                       2.0, 3.0,
                       4.0, 5.0};
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
    double array1[] = {0.0, 1.0, 2.0,  3.0,
                       4.0, 5.0, 6.0,  7.0,
                       8.0, 9.0, 10.0, 11.0};
    double array2[] = {1.0, 1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0, 1.0};
    double array3[] = {1.0, 2.0,  3.0,  4.0,
                       5.0, 6.0,  7.0,  8.0,
                       9.0, 10.0, 11.0, 12.0};
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
    double array1[] = {0.0, 1.0, 2.0,  3.0,
                       4.0, 5.0, 6.0,  7.0,
                       8.0, 9.0, 10.0, 11.0};
    double array2[] = {1.0, 1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0, 1.0};
    double array3[] = {-1.0, 0.0, 1.0, 2.0,
                       3.0,  4.0, 5.0, 6.0,
                       7.0,  8.0, 9.0, 10.0};
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
    double array1[] = {1.0, 2.0, 3.0,
                       4.0, 5.0, 6.0};
    double array2[] = {1.0, 2.0,
                       3.0, 4.0,
                       5.0, 6.0};
    double array3[] = {22.0, 28.0,
                       49.0, 64.0};
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
    double s = 1.0;
    double array[] = {0.0, 1.0, 2.0,  3.0,
                      4.0, 5.0, 6.0,  7.0,
                      8.0, 9.0, 10.0, 11.0};
    double array1[] = {1.0, 2.0,  3.0,  4.0,
                       5.0, 6.0,  7.0,  8.0,
                       9.0, 10.0, 11.0, 12.0};
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
    double s = 2.0;
    double array[] = {0.0, 1.0, 2.0,  3.0,
                      4.0, 5.0, 6.0,  7.0,
                      8.0, 9.0, 10.0, 11.0};
    double array1[] = {0.0,  2.0,  4.0,  6.0,
                       8.0,  10.0, 12.0, 14.0,
                       16.0, 18.0, 20.0, 22.0};
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
    double array[] = {0.0, 1.0, 2.0,
                      3.0, 4.0, 5.0};
    double array1[] = {0.0, 3.0,
                       1.0, 4.0,
                       2.0, 5.0};
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
    double datamat1[] = {0.8, 0.5, 0.9,
                       1.0, 2.0, 1.0,
                       1.0, 1.0, 1.0};
    double dataexpected1[] = {0.4, 0.25, 0.45,
                            0.5, 1.0,  0.5,
                            0.5, 0.5, 0.5};
    double datamat2[] = {0.5, 0.2, 0.1,
                       0.4, 0.1, 0.1,
                       0.1, 0.1, 0.1};
    double dataexpected2[] = {1.0, 0.4, 0.2,
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
    double data[] = {-1.0, -0.2, 0.3,
                      1.2, 1.0, 1.4};
    double dataexpected[] = {0.0, 0.0, 0.3,
                             1.0, 1.0, 1.0};
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
    double data[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
                     2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
                     3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0,
                     4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0,
                     5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0,
                     6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0,
                     7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0,
                     8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,
                     9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0,
                     10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0,
                     11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0,
                     12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0,
                     13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0,
                     14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0,
                     15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0};
    double datakernel[] = {1.0, 1.0, 1.0,
                          1.0, 1.0, 1.0,
                          1.0, 1.0, 1.0};
    double dataexpected[] = {6.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 6.0,
                             12.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0,  12.0,
                             18.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 18.0,
                             24.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 24.0,
                             30.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 30.0,
                             36.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 36.0,
                             42.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 42.0,
                             48.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 48.0,
                             54.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 54.0,
                             60.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 60.0,
                             66.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 66.0,
                             72.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 72.0,
                             78.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 78.0,
                             84.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 84.0,
                             58.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 58.0};
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
    double array1[] = {0.0, 1.0, 2.0,  3.0,
                       4.0, 5.0, 6.0,  7.0,
                       8.0, 9.0, 10.0, 11.0};
    double array2[] = {1.0, 1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0, 1.0};
    double array3[] = {1.0, 2.0,  3.0,  4.0,
                       5.0, 6.0,  7.0,  8.0,
                       9.0, 10.0, 11.0, 12.0};
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
    double array1[] = {0.0, 1.0, 2.0,  3.0,
                       4.0, 5.0, 6.0,  7.0,
                       8.0, 9.0, 10.0, 11.0};
    double array2[] = {1.0, 1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0, 1.0,
                       1.0, 1.0, 1.0, 1.0};
    double array3[] = {-1.0, 0.0, 1.0, 2.0,
                       3.0,  4.0, 5.0, 6.0,
                       7.0,  8.0, 9.0, 10.0};
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
    double array1[] = {1.0, 2.0, 3.0,
                       4.0, 5.0, 6.0};
    double array2[] = {1.0, 2.0,
                       3.0, 4.0,
                       5.0, 6.0};
    double array3[] = {22.0, 28.0,
                       49.0, 64.0};
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
    double s = 1.0;
    double array[] = {0.0, 1.0, 2.0,  3.0,
                      4.0, 5.0, 6.0,  7.0,
                      8.0, 9.0, 10.0, 11.0};
    double array1[] = {1.0, 2.0,  3.0,  4.0,
                       5.0, 6.0,  7.0,  8.0,
                       9.0, 10.0, 11.0, 12.0};
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
    double s = 2.0;
    double array[] = {0.0, 1.0, 2.0,  3.0,
                      4.0, 5.0, 6.0,  7.0,
                      8.0, 9.0, 10.0, 11.0};
    double array1[] = {0.0,  2.0,  4.0,  6.0,
                       8.0,  10.0, 12.0, 14.0,
                       16.0, 18.0, 20.0, 22.0};
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
    double array[] = {0.0, 1.0, 2.0,
                      3.0, 4.0, 5.0};
    double array1[] = {0.0, 3.0,
                       1.0, 4.0,
                       2.0, 5.0};
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
    double datamat1[] = {0.8, 0.5, 0.9,
                       1.0, 2.0, 1.0,
                       1.0, 1.0, 1.0};
    double dataexpected1[] = {0.4, 0.25, 0.45,
                            0.5, 1.0,  0.5,
                            0.5, 0.5, 0.5};
    double datamat2[] = {0.5, 0.2, 0.1,
                       0.4, 0.1, 0.1,
                       0.1, 0.1, 0.1};
    double dataexpected2[] = {1.0, 0.4, 0.2,
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
    double data[] = {-1.0, -0.2, 0.3,
                      1.2, 1.0, 1.4};
    double dataexpected[] = {0.0, 0.0, 0.3,
                             1.0, 1.0, 1.0};
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
    double data[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
                     2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
                     3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0,
                     4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0,
                     5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0,
                     6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0,
                     7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0,
                     8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,
                     9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0,
                     10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0,
                     11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0,
                     12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0,
                     13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0,
                     14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0,
                     15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0};
    double datakernel[] = {1.0, 1.0, 1.0,
                          1.0, 1.0, 1.0,
                          1.0, 1.0, 1.0};
    double dataexpected[] = {6.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 6.0,
                             12.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0,  12.0,
                             18.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 18.0,
                             24.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 36.0, 24.0,
                             30.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 30.0,
                             36.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 54.0, 36.0,
                             42.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 63.0, 42.0,
                             48.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 72.0, 48.0,
                             54.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 81.0, 54.0,
                             60.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 60.0,
                             66.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 99.0, 66.0,
                             72.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 108.0, 72.0,
                             78.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 117.0, 78.0,
                             84.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 126.0, 84.0,
                             58.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 87.0, 58.0};
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
