#ifndef _LINE_TEST_H_
#define _LINE_TEST_H_

#include <cstdlib>
#include "ellipse_algorithms.h"

#define TEST_REPEAT 1000
#define MAX_TEST_CORD 3000

#define TEST_AMOUNT 4

double test_time_canon(const point_t<int> center, const int a, const int b);
double test_time_parametric(const point_t<int> center, const int a, const int b);
double test_time_Bresenham(const point_t<int> center, const int a, const int b);
double test_time_middle_point(const point_t<int> center, const int a, const int b);

typedef double (*test_time_func_t)(const point_t<int> center, const int a, const int b);
const test_time_func_t test_time_func_array[TEST_AMOUNT] = {test_time_canon,
                                                            test_time_parametric,
                                                            test_time_Bresenham,
                                                            test_time_middle_point};

#endif

