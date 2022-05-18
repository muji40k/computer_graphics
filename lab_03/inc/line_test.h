#ifndef _LINE_TEST_H_
#define _LINE_TEST_H_

#include <cstdlib>
#include "line_algorithms.h"

#define TEST_REPEAT 10000
#define MAX_TEST_CORD 3000

#define TEST_AMOUNT 5

double test_time_dda(const point_t<int> start, const point_t<int> end);
double test_time_BRHM(const point_t<int> start, const point_t<int> end);
double test_time_BRHMI(const point_t<int> start, const point_t<int> end);
double test_time_BRHMA(const point_t<int> start, const point_t<int> end);
double test_time_WU(const point_t<int> start, const point_t<int> end);

typedef double (*test_time_func_t)(const point_t<int>, const point_t<int>);
const test_time_func_t test_time_func_array[TEST_AMOUNT] = {test_time_dda,
                                                            test_time_BRHM,
                                                            test_time_BRHMI,
                                                            test_time_BRHMA,
                                                            test_time_WU};

size_t test_stairs_dda(const point_t<int> start, const point_t<int> end);
size_t test_stairs_BRHM(const point_t<int> start, const point_t<int> end);
size_t test_stairs_BRHMI(const point_t<int> start, const point_t<int> end);
size_t test_stairs_BRHMA(const point_t<int> start, const point_t<int> end);
size_t test_stairs_WU(const point_t<int> start, const point_t<int> end);

typedef size_t (*test_stairs_func_t)(const point_t<int>, const point_t<int>);
const test_stairs_func_t test_stairs_func_array[TEST_AMOUNT] = {test_stairs_dda,
                                                                test_stairs_BRHM,
                                                                test_stairs_BRHMI,
                                                                test_stairs_BRHMA,
                                                                test_stairs_WU};

#endif

