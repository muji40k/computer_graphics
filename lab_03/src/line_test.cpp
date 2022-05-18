#include <sys/time.h>
#include <cmath>
#include "line_test.h"

#define GET_MILLIS(tv) ((tv).tv_sec * 1e3 + (tv).tv_usec / 1e3)

double test_time_dda(const point_t<int> start, const point_t<int> end)
{
    struct timeval timeval;
    double result = 0;

    int rc =  EXIT_SUCCESS;
    dda_line_handle_t handle;
    point_t<int> point;

    double time;

    for (size_t i = 0; EXIT_SUCCESS == rc && TEST_REPEAT > i; i++)
    {
        gettimeofday(&timeval, NULL);
        time = GET_MILLIS(timeval);

        int rc = dda_line_handle_init(handle, start, end);

        if (EXIT_SUCCESS == rc)
            do
                dda_line_handle_get(handle, point);
            while (CONTINUE_DRAW == dda_line_handle_step(handle));

        gettimeofday(&timeval, NULL);
        result += GET_MILLIS(timeval) - time;
    }

    result /= TEST_REPEAT;

    return result;
}

double test_time_BRHM(const point_t<int> start, const point_t<int> end)
{
    struct timeval timeval;
    double result = 0;

    int rc =  EXIT_SUCCESS;
    BRHM_line_handle_t handle;
    point_t<int> point;

    double time;

    for (size_t i = 0; EXIT_SUCCESS == rc && TEST_REPEAT > i; i++)
    {
        gettimeofday(&timeval, NULL);
        time = GET_MILLIS(timeval);

        int rc = BRHM_line_handle_init(handle, start, end);

        if (EXIT_SUCCESS == rc)
            do
                BRHM_line_handle_get(handle, point);
            while (CONTINUE_DRAW == BRHM_line_handle_step(handle));

        gettimeofday(&timeval, NULL);
        result += GET_MILLIS(timeval) - time;
    }

    result /= TEST_REPEAT;

    return result;
}

double test_time_BRHMI(const point_t<int> start, const point_t<int> end)
{
    struct timeval timeval;
    double result = 0;

    int rc =  EXIT_SUCCESS;
    BRHMI_line_handle_t handle;
    point_t<int> point;

    double time;

    for (size_t i = 0; EXIT_SUCCESS == rc && TEST_REPEAT > i; i++)
    {
        gettimeofday(&timeval, NULL);
        time = GET_MILLIS(timeval);

        int rc = BRHMI_line_handle_init(handle, start, end);

        if (EXIT_SUCCESS == rc)
            do
                BRHMI_line_handle_get(handle, point);
            while (CONTINUE_DRAW == BRHMI_line_handle_step(handle));

        gettimeofday(&timeval, NULL);
        result += GET_MILLIS(timeval) - time;
    }

    result /= TEST_REPEAT;

    return result;
}

double test_time_BRHMA(const point_t<int> start, const point_t<int> end)
{
    struct timeval timeval;
    double result = 0;

    int rc =  EXIT_SUCCESS;
    BRHMA_line_handle_t handle;
    BRHMA_result_t point;

    double time;

    for (size_t i = 0; EXIT_SUCCESS == rc && TEST_REPEAT > i; i++)
    {
        gettimeofday(&timeval, NULL);
        time = GET_MILLIS(timeval);

        int rc = BRHMA_line_handle_init(handle, start, end);

        if (EXIT_SUCCESS == rc)
            do
                BRHMA_line_handle_get(handle, point);
            while (CONTINUE_DRAW == BRHMA_line_handle_step(handle));

        gettimeofday(&timeval, NULL);
        result += GET_MILLIS(timeval) - time;
    }

    result /= TEST_REPEAT;

    return result;
}

double test_time_WU(const point_t<int> start, const point_t<int> end)
{
    struct timeval timeval;
    double result = 0;

    int rc =  EXIT_SUCCESS;
    WU_line_handle_t handle;
    WU_result_t point;

    double time;

    for (size_t i = 0; EXIT_SUCCESS == rc && TEST_REPEAT > i; i++)
    {
        gettimeofday(&timeval, NULL);
        time = GET_MILLIS(timeval);

        int rc = WU_line_handle_init(handle, start, end);

        if (EXIT_SUCCESS == rc)
            do
                WU_line_handle_get(handle, point);
            while (CONTINUE_DRAW == WU_line_handle_step(handle));

        gettimeofday(&timeval, NULL);
        result += GET_MILLIS(timeval) - time;
    }

    result /= TEST_REPEAT;

    return result;
}

// Stairs

size_t test_stairs_dda(const point_t<int> start, const point_t<int> end)
{
    size_t result = 0;

    dda_line_handle_t handle;
    point_t<int> point, previous;

    for (size_t i = 0; 2 > i; i++)
    {
        point[i] = start[i];
        previous[i] = start[i];
    }

    if (EXIT_SUCCESS == dda_line_handle_init(handle, start, end))
        do
        {
            dda_line_handle_get(handle, point);

            if (1 == abs(point[0] - previous[0])
                && 1 == abs(point[1] - previous[1]))
                result++;

            for (size_t i = 0; 2 > i; i++)
                previous[i] = point[i];
        }
        while (CONTINUE_DRAW == dda_line_handle_step(handle));

    return result;
}

size_t test_stairs_BRHM(const point_t<int> start, const point_t<int> end)
{
    size_t result = 0;

    BRHM_line_handle_t handle;
    point_t<int> point, previous;

    for (size_t i = 0; 2 > i; i++)
    {
        point[i] = start[i];
        previous[i] = start[i];
    }

    if (EXIT_SUCCESS == BRHM_line_handle_init(handle, start, end))
        do
        {
            BRHM_line_handle_get(handle, point);

            if (1 == abs(point[0] - previous[0])
                && 1 == abs(point[1] - previous[1]))
                result++;

            for (size_t i = 0; 2 > i; i++)
                previous[i] = point[i];
        }
        while (CONTINUE_DRAW == BRHM_line_handle_step(handle));

    return result;
}

size_t test_stairs_BRHMI(const point_t<int> start, const point_t<int> end)
{
    size_t result = 0;

    BRHMI_line_handle_t handle;
    point_t<int> point, previous;

    for (size_t i = 0; 2 > i; i++)
    {
        point[i] = start[i];
        previous[i] = start[i];
    }

    if (EXIT_SUCCESS == BRHMI_line_handle_init(handle, start, end))
        do
        {
            BRHMI_line_handle_get(handle, point);

            if (1 == abs(point[0] - previous[0])
                && 1 == abs(point[1] - previous[1]))
                result++;

            for (size_t i = 0; 2 > i; i++)
                previous[i] = point[i];
        }
        while (CONTINUE_DRAW == BRHMI_line_handle_step(handle));

    return result;
}

size_t test_stairs_BRHMA(const point_t<int> start, const point_t<int> end)
{
    size_t result = 0;

    BRHMA_line_handle_t handle;
    BRHMA_result_t point;
    point_t<int> previous;

    for (size_t i = 0; 2 > i; i++)
    {
        point.dot[i] = start[i];
        previous[i] = start[i];
    }

    if (EXIT_SUCCESS == BRHMA_line_handle_init(handle, start, end))
        do
        {
            BRHMA_line_handle_get(handle, point);

            if (1 == abs(point.dot[0] - previous[0])
                && 1 == abs(point.dot[1] - previous[1]))
                result++;

            for (size_t i = 0; 2 > i; i++)
                previous[i] = point.dot[i];
        }
        while (CONTINUE_DRAW == BRHMA_line_handle_step(handle));

    return result;
}

size_t test_stairs_WU(const point_t<int> start, const point_t<int> end)
{
    size_t result = 0;

    WU_line_handle_t handle;
    WU_result_t point;
    point_t<int> previous;

    for (size_t i = 0; 2 > i; i++)
    {
        point.start[i] = start[i];
        previous[i] = start[i];
    }

    if (EXIT_SUCCESS == WU_line_handle_init(handle, start, end))
        do
        {
            WU_line_handle_get(handle, point);

            if (1 == abs(point.start[0] - previous[0])
                && 1 == abs(point.start[1] - previous[1]))
                result++;

            for (size_t i = 0; 2 > i; i++)
                previous[i] = point.start[i];
        }
        while (CONTINUE_DRAW == WU_line_handle_step(handle));

    return result;
}
