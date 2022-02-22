#include "test_filter.h"
#include "../filter.h"
#include "../pgm.h"
#include "CUnit/Basic.h"
#include "CUnit/Automated.h"

void test_filter_sharpen_in_place(){
    pgm image = pgm_read("src/test/data/coffee_square_small.pgm");
    pgm expected = pgm_read("src/test/data/sharpen.pgm");
    filter_sharpen_in_place(&image.mat);
    pgm_write("src/test/data/test_filter.pgm", image);
    pgm_destroy(&image);
    image = pgm_read("src/test/data/test_filter.pgm");
    remove("src/test/data/test_filter.pgm");
    CU_ASSERT(pgm_is_approx_equal(image, expected, 0.01));
    pgm_destroy(&image);
    pgm_destroy(&expected);
}

void test_filter_blur_in_place(){
  pgm image = pgm_read("src/test/data/coffee_square_small.pgm");
  pgm expected = pgm_read("src/test/data/blur.pgm");
  filter_blur_in_place(&image.mat);
  pgm_write("src/test/data/test_filter.pgm", image);
  pgm_destroy(&image);
  image = pgm_read("src/test/data/test_filter.pgm");
  remove("src/test/data/test_filter.pgm");
  CU_ASSERT(pgm_is_approx_equal(image, expected, 0.01));
  pgm_destroy(&image);
  pgm_destroy(&expected);
}

void test_filter_edge_enhance_in_place(){
    pgm image = pgm_read("src/test/data/coffee_square_small.pgm");
    pgm expected = pgm_read("src/test/data/edge_enhance.pgm");
    filter_edge_enhance_in_place(&image.mat);
    pgm_write("src/test/data/test_filter.pgm", image);
    pgm_destroy(&image);
    image = pgm_read("src/test/data/test_filter.pgm");
    remove("src/test/data/test_filter.pgm");
    CU_ASSERT(pgm_is_approx_equal(image, expected, 0.01));
    pgm_destroy(&image);
    pgm_destroy(&expected);
}

void test_filter_edge_detect_in_place(){
    pgm image = pgm_read("src/test/data/coffee_square_small.pgm");
    pgm expected = pgm_read("src/test/data/edge_detect.pgm");
    filter_edge_detect_in_place(&image.mat);
    pgm_write("src/test/data/test_filter.pgm", image);
    pgm_destroy(&image);
    image = pgm_read("src/test/data/test_filter.pgm");
    remove("src/test/data/test_filter.pgm");
    CU_ASSERT(pgm_is_approx_equal(image, expected, 0.01));
    pgm_destroy(&image);
    pgm_destroy(&expected);
}

void test_filter_emboss_in_place(){
    pgm image = pgm_read("src/test/data/coffee_square_small.pgm");
    pgm expected = pgm_read("src/test/data/emboss.pgm");
    filter_emboss_in_place(&image.mat);
    pgm_write("src/test/data/test_filter.pgm", image);
    pgm_destroy(&image);
    image = pgm_read("src/test/data/test_filter.pgm");
    remove("src/test/data/test_filter.pgm");
    CU_ASSERT(pgm_is_approx_equal(image, expected, 0.01));
    pgm_destroy(&image);
    pgm_destroy(&expected);
}

void test_filter_sharpen(){
    pgm image = pgm_read("src/test/data/coffee_square_small.pgm");
    pgm expected = pgm_read("src/test/data/sharpen.pgm");
    pgm res;
    res.max = image.max;
    res.mat = filter_sharpen(image.mat);
    pgm_write("src/test/data/test_filter.pgm", res);
    pgm_destroy(&res);
    res = pgm_read("src/test/data/test_filter.pgm");
    remove("src/test/data/test_filter.pgm");
    CU_ASSERT(pgm_is_approx_equal(res, expected, 0.01));
    pgm_destroy(&image);
    pgm_destroy(&expected);
    pgm_destroy(&res);
}

void test_filter_blur(){
    pgm image = pgm_read("src/test/data/coffee_square_small.pgm");
    pgm expected = pgm_read("src/test/data/blur.pgm");
    pgm res;
    res.max = image.max;
    res.mat = filter_blur(image.mat);
    pgm_write("src/test/data/test_filter.pgm", res);
    pgm_destroy(&res);
    res = pgm_read("src/test/data/test_filter.pgm");
    remove("src/test/data/test_filter.pgm");
    CU_ASSERT(pgm_is_approx_equal(res, expected, 0.01));
    pgm_destroy(&image);
    pgm_destroy(&expected);
    pgm_destroy(&res);
}

void test_filter_edge_enhance(){
    pgm image = pgm_read("src/test/data/coffee_square_small.pgm");
    pgm expected = pgm_read("src/test/data/edge_enhance.pgm");
    pgm res;
    res.max = image.max;
    res.mat = filter_edge_enhance(image.mat);
    pgm_write("src/test/data/test_filter.pgm", res);
    pgm_destroy(&res);
    res = pgm_read("src/test/data/test_filter.pgm");
    remove("src/test/data/test_filter.pgm");
    CU_ASSERT(pgm_is_approx_equal(res, expected, 0.01));
    pgm_destroy(&image);
    pgm_destroy(&expected);
    pgm_destroy(&res);
}

void test_filter_edge_detect(){
    pgm image = pgm_read("src/test/data/coffee_square_small.pgm");
    pgm expected = pgm_read("src/test/data/edge_detect.pgm");
    pgm res;
    res.max = image.max;
    res.mat = filter_edge_detect(image.mat);
    pgm_write("src/test/data/test_filter.pgm", res);
    pgm_destroy(&res);
    res = pgm_read("src/test/data/test_filter.pgm");
    remove("src/test/data/test_filter.pgm");
    CU_ASSERT(pgm_is_approx_equal(res, expected, 0.01));
    pgm_destroy(&image);
    pgm_destroy(&expected);
    pgm_destroy(&res);
}

void test_filter_emboss(){
    pgm image = pgm_read("src/test/data/coffee_square_small.pgm");
    pgm expected = pgm_read("src/test/data/emboss.pgm");
    pgm res;
    res.max = image.max;
    res.mat = filter_emboss(image.mat);
    pgm_write("src/test/data/test_filter.pgm", res);
    pgm_destroy(&res);
    res = pgm_read("src/test/data/test_filter.pgm");
    remove("src/test/data/test_filter.pgm");
    CU_ASSERT(pgm_is_approx_equal(res, expected, 0.01));
    pgm_destroy(&image);
    pgm_destroy(&expected);
    pgm_destroy(&res);
}
