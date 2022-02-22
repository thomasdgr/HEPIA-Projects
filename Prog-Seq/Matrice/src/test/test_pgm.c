#include "../pgm.h"
#include "test_pgm.h"
#include "CUnit/Basic.h"
#include "CUnit/Automated.h"

double epsilon_pgm = 0.000001;

void test_pgm_is_equal(){
    double data1[] = {0.1, 0.2, 0.3,
                      0.4, 0.5, 0.6};
    double data2[] = {0.1, 0.1, 0.1,
                      0.1, 0.1, 0.1};
    matrix m1, m2;
    m1 = matrix_create_from_array(2, 3, data1);
    m2 = matrix_create_from_array(2, 3, data2);
    pgm i1, i2, i3;
    i1.max = 10.0; i1.mat = m1;
    i2.max = 10.0; i2.mat = m2;
    i3.max = 11.0; i3.mat = m1;
    CU_ASSERT(!pgm_is_equal(i1, i2));
    CU_ASSERT(!pgm_is_equal(i1, i3));
    CU_ASSERT(pgm_is_equal(i1, i1));
    matrix_destroy(&m1);
    matrix_destroy(&m2);
}

void test_pgm_is_approx_equal(){
    double epsilon = 0.01;
    double data1[] = {0.1, 0.2, 0.3,
                      0.4, 0.5, 0.6};
    double data2[] = {0.1, 0.1, 0.1,
                      0.1, 0.1, 0.1};
    double data3[] = {0.1+epsilon-epsilon/10.0, 0.2, 0.3,
                      0.4, 0.5, 0.6};
    matrix m1, m2, m3;
    m1 = matrix_create_from_array(2, 3, data1);
    m2 = matrix_create_from_array(2, 3, data2);
    m3 = matrix_create_from_array(2, 3, data3);
    pgm i1, i2, i3, i4;
    i1.max = 10.0; i1.mat = m1;
    i2.max = 10.0; i2.mat = m2;
    i3.max = 11.0; i3.mat = m1;
    i4.max = 10.0; i4.mat = m3;
    CU_ASSERT(!pgm_is_approx_equal(i1, i2, epsilon));
    CU_ASSERT(!pgm_is_approx_equal(i1, i3, epsilon));
    CU_ASSERT(pgm_is_approx_equal(i1, i1, epsilon));
    CU_ASSERT(pgm_is_approx_equal(i1, i4, epsilon));
    matrix_destroy(&m1);
    matrix_destroy(&m2);
    matrix_destroy(&m3);
}

void test_pgm_read(){
    pgm expected, read;
    double data_expected[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                              0, 3, 3, 3, 3, 0, 0, 7, 7, 7, 7, 0, 0,11,11,11,11, 0, 0,15,15,15,15, 0,
                              0, 0, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0,15, 0, 0, 0,
                              0, 0, 3, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0,11,11,11,11, 0, 0, 0,15, 0, 0, 0,
                              0, 0, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0,15, 0, 0, 0,
                              0, 0, 3, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0,11,11,11,11, 0, 0, 0,15, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    matrix mat_expected;
    mat_expected = matrix_create_from_array(7, 24, data_expected);
    matrix_mult_scalar_in_place(mat_expected, 1.0/15.0);
    expected.max = 15.0;
    expected.mat = mat_expected;
    read = pgm_read("file_does_not_exist");
    CU_ASSERT(read.max == -1);
    CU_ASSERT(!pgm_is_approx_equal(read, expected, epsilon_pgm));
    read = pgm_read("src/test/data/test.pgm");
    CU_ASSERT(pgm_is_approx_equal(read, expected, epsilon_pgm));
    pgm_destroy(&expected);
    pgm_destroy(&read);
}

void test_pgm_write(){
    pgm read, reread;
    read = pgm_read("src/test/data/test.pgm");
    CU_ASSERT(pgm_write("src/test/data/testwrite.pgm", read)==1);
    reread = pgm_read("src/test/data/testwrite.pgm");
    CU_ASSERT(pgm_is_approx_equal(read, reread, epsilon_pgm));
    remove("src/test/data/testwrite.pgm");
    pgm_destroy(&read);
    pgm_destroy(&reread);
}

void test_pgm_destroy(){
    pgm read;
    read = pgm_read("src/test/data/test.pgm");
    pgm_destroy(&read);
    CU_ASSERT(read.mat.data==NULL);
    CU_ASSERT(read.max==-1);
}
