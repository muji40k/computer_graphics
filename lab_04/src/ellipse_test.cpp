#include <sys/time.h>
#include <cmath>
#include "ellipse_test.h"

#define GET_MILLIS(tv) ((tv).tv_sec * 1e3 + (tv).tv_usec / 1e3)

double test_time_canon(const point_t<int> center, const int a, const int b)
{
    struct timeval timeval;
    double result = 0;

    int rc =  EXIT_SUCCESS;
    canon_ellipse_handle_t handle;
    unpacked_dot_t points;

    double time;

    for (size_t i = 0; EXIT_SUCCESS == rc && TEST_REPEAT > i; i++)
    {
        gettimeofday(&timeval, NULL);
        time = GET_MILLIS(timeval);

        int rc = canon_ellipse_handle_init(handle, center, a, b);

        if (EXIT_SUCCESS == rc)
            do
                canon_ellipse_handle_get(handle, points);
            while (CONTINUE_DRAW == canon_ellipse_handle_step(handle));

        gettimeofday(&timeval, NULL);
        result += GET_MILLIS(timeval) - time;
    }

    result /= TEST_REPEAT;

    return result;
}

double test_time_parametric(const point_t<int> center, const int a, const int b)
{
    struct timeval timeval;
    double result = 0;

    int rc =  EXIT_SUCCESS;
    parametric_ellipse_handle_t handle;
    unpacked_dot_t points;

    double time;

    for (size_t i = 0; EXIT_SUCCESS == rc && TEST_REPEAT > i; i++)
    {
        gettimeofday(&timeval, NULL);
        time = GET_MILLIS(timeval);

        int rc = parametric_ellipse_handle_init(handle, center, a, b);

        if (EXIT_SUCCESS == rc)
            do
                parametric_ellipse_handle_get(handle, points);
            while (CONTINUE_DRAW == parametric_ellipse_handle_step(handle));

        gettimeofday(&timeval, NULL);
        result += GET_MILLIS(timeval) - time;
    }

    result /= TEST_REPEAT;

    return result;
}

double test_time_Bresenham(const point_t<int> center, const int a, const int b)
{
    struct timeval timeval;
    double result = 0;

    int rc =  EXIT_SUCCESS;
    Bresenham_ellipse_handle_t handle;
    unpacked_dot_t points;

    double time;

    for (size_t i = 0; EXIT_SUCCESS == rc && TEST_REPEAT > i; i++)
    {
        gettimeofday(&timeval, NULL);
        time = GET_MILLIS(timeval);

        int rc = Bresenham_ellipse_handle_init(handle, center, a, b);

        if (EXIT_SUCCESS == rc)
            do
                Bresenham_ellipse_handle_get(handle, points);
            while (CONTINUE_DRAW == Bresenham_ellipse_handle_step(handle));

        gettimeofday(&timeval, NULL);
        result += GET_MILLIS(timeval) - time;
    }

    result /= TEST_REPEAT;

    return result;
}

double test_time_middle_point(const point_t<int> center, const int a, const int b)
{
    struct timeval timeval;
    double result = 0;

    int rc =  EXIT_SUCCESS;
    middle_point_ellipse_handle_t handle;
    unpacked_dot_t points;

    double time;

    for (size_t i = 0; EXIT_SUCCESS == rc && TEST_REPEAT > i; i++)
    {
        gettimeofday(&timeval, NULL);
        time = GET_MILLIS(timeval);

        int rc = middle_point_ellipse_handle_init(handle, center, a, b);

        if (EXIT_SUCCESS == rc)
            do
                middle_point_ellipse_handle_get(handle, points);
            while (CONTINUE_DRAW == middle_point_ellipse_handle_step(handle));

        gettimeofday(&timeval, NULL);
        result += GET_MILLIS(timeval) - time;
    }

    result /= TEST_REPEAT;

    return result;
}

