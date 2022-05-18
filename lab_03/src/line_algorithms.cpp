#include <cstdlib>
#include <cmath>
#include "line_algorithms.h"

#define EPS 1e-8

template <typename T>
static int sign(T value)
{
    if (0 <= value)
        return 1;

    return -1;
}

template <typename T>
static bool point_is_same(const point_t<T> start, const point_t<T> end)
{
    return (end[0] == start[0] && end[1] == start[1]);
}

// dda
int dda_line_handle_init(dda_line_handle_t &handle,
                         const point_t<int> start, 
                         const point_t<int> end)
{
    if (point_is_same(start, end))
        return ERROR_DEGENERATE_LINE;

    for (size_t i = 0; POINT_AMOUNT > i; i++)
        handle.point[i] = start[i];

    double adx = abs(end[0] - start[0]),
           ady = abs(end[1] - start[1]);

    handle.length = adx > ady ? adx : ady;
    handle.dx = (double)(end[0] - start[0]) / handle.length;
    handle.dy = (double)(end[1] - start[1]) / handle.length;

    return EXIT_SUCCESS;
}

int dda_line_handle_step(dda_line_handle_t &handle)
{
    int rc = CONTINUE_DRAW;

    if (0 == handle.length)
        rc = FINISHED_DRAW;

    if (CONTINUE_DRAW == rc)
    {
        handle.point[0] += handle.dx;
        handle.point[1] += handle.dy;
        handle.length--;
    }

    return rc;
}

void dda_line_handle_get(dda_line_handle_t &handle, point_t<int> &point)
{
    for (size_t i = 0; POINT_AMOUNT > i; i++)
        point[i] = round(handle.point[i]);
}

// Bresenham
int BRHM_line_handle_init(BRHM_line_handle_t &handle,
                          const point_t<int> start, 
                          const point_t<int> end)
{
    if (point_is_same(start, end))
        return ERROR_DEGENERATE_LINE;

    for (size_t i = 0; POINT_AMOUNT > i; i++)
        handle.point[i] = start[i];

    double dx = end[0] - start[0],
           dy = end[1] - start[1];

    handle.sx = sign(dx);
    handle.sy = sign(dy);

    dx = fabs(dx);
    dy = fabs(dy);

    if (dx < dy)
    {
        handle.length = dy;
        handle.swap = true;
        handle.tangent = (double)dx / dy;
    }
    else
    {
        handle.length = dx;
        handle.swap = false;
        handle.tangent = (double)dy / dx;
    }

    handle.error = handle.tangent - 0.5;

    return EXIT_SUCCESS;
}

int BRHM_line_handle_step(BRHM_line_handle_t &handle)
{
    int rc = CONTINUE_DRAW;

    if (0 == handle.length)
        rc = FINISHED_DRAW;

    if (CONTINUE_DRAW == rc)
    {
        if (0 <= handle.error)
        {
            if (handle.swap)
                handle.point[0] += handle.sx;
            else
                handle.point[1] += handle.sy;

            handle.error -= 1;
        }

        if (handle.swap)
            handle.point[1] += handle.sy;
        else
            handle.point[0] += handle.sx;

        handle.error += handle.tangent;
        handle.length--;
    }

    return rc;
}

void BRHM_line_handle_get(BRHM_line_handle_t &handle, point_t<int> &point)
{
    for (size_t i = 0; POINT_AMOUNT > i; i++)
        point[i] = handle.point[i];
}

// Bresenham Integer
int BRHMI_line_handle_init(BRHMI_line_handle_t &handle,
                           const point_t<int> start, 
                           const point_t<int> end)
{
    if (point_is_same(start, end))
        return ERROR_DEGENERATE_LINE;

    for (size_t i = 0; POINT_AMOUNT > i; i++)
        handle.point[i] = start[i];

    handle.dx = end[0] - start[0];
    handle.dy = end[1] - start[1];

    handle.sx = sign(handle.dx);
    handle.sy = sign(handle.dy);
    handle.dx = abs(handle.dx);
    handle.dy = abs(handle.dy);

    if (handle.dx >= handle.dy)
        handle.swap = false;
    else
    {
        int tmp = handle.dy;
        handle.dy = handle.dx;
        handle.dx = tmp;
        handle.swap = true;
    }

    handle.length = handle.dx;
    handle.dy *= 2;
    handle.error = handle.dy - handle.dx;
    handle.dx *= 2;

    return EXIT_SUCCESS;
}

int BRHMI_line_handle_step(BRHMI_line_handle_t &handle)
{
    int rc = CONTINUE_DRAW;

    if (0 == handle.length)
        rc = FINISHED_DRAW;

    if (CONTINUE_DRAW == rc)
    {
        if (0 <= handle.error)
        {
            if (handle.swap)
                handle.point[0] += handle.sx;
            else
                handle.point[1] += handle.sy;

            handle.error -= handle.dx;
        }

        if (handle.swap)
            handle.point[1] += handle.sy;
        else
            handle.point[0] += handle.sx;

        handle.error += handle.dy;
        handle.length--;
    }

    return rc;
}

void BRHMI_line_handle_get(BRHMI_line_handle_t &handle, point_t<int> &point)
{
    for (size_t i = 0; POINT_AMOUNT > i; i++)
        point[i] = handle.point[i];
}

// Bresenham smoothing
int BRHMA_line_handle_init(BRHMA_line_handle_t &handle,
                           const point_t<int> start, 
                           const point_t<int> end)
{
    if (point_is_same(start, end))
        return ERROR_DEGENERATE_LINE;

    for (size_t i = 0; POINT_AMOUNT > i; i++)
        handle.point[i] = start[i];

    double dx = end[0] - start[0],
           dy = end[1] - start[1];

    handle.sx = sign(dx);
    handle.sy = sign(dy);

    dx = fabs(dx);
    dy = fabs(dy);

    if (dx < dy)
    {
        handle.length = dy;
        handle.swap = true;
        handle.tangent = (double)dx / dy;
    }
    else
    {
        handle.length = dx;
        handle.swap = false;
        handle.tangent = (double)dy / dx;
    }

    handle.error = 0.5;
    handle.error_limit = 1 - handle.tangent;

    return EXIT_SUCCESS;
}

int BRHMA_line_handle_step(BRHMA_line_handle_t &handle)
{
    int rc = CONTINUE_DRAW;

    if (0 == handle.length)
        rc = FINISHED_DRAW;

    if (CONTINUE_DRAW == rc)
    {
        if (handle.error_limit <= handle.error)
        {
            if (handle.swap)
                handle.point[0] += handle.sx;
            else
                handle.point[1] += handle.sy;

            handle.error -= handle.error_limit;
        }
        else
            handle.error += handle.tangent;

        if (handle.swap)
            handle.point[1] += handle.sy;
        else
            handle.point[0] += handle.sx;

        handle.length--;
    }

    return rc;
}

void BRHMA_line_handle_get(BRHMA_line_handle_t &handle, BRHMA_result_t &point)
{
    for (size_t i = 0; POINT_AMOUNT > i; i++)
        point.dot[i] = handle.point[i];

    point.alpha = handle.error;
}

// Wu
int WU_line_handle_init(WU_line_handle_t &handle,
                        const point_t<int> start, 
                        const point_t<int> end)
{
    if (point_is_same(start, end))
        return ERROR_DEGENERATE_LINE;

    for (size_t i = 0; POINT_AMOUNT > i; i++)
        handle.point[i] = start[i];

    double adx = abs(end[0] - start[0]),
           ady = abs(end[1] - start[1]);

    handle.length = adx > ady ? adx : ady;
    handle.dx = (double)(end[0] - start[0]) / handle.length;
    handle.dy = (double)(end[1] - start[1]) / handle.length;
    handle.tangent = SMOOTH;

    if (EPS > fabs(handle.dx))
        handle.tangent = VERTICAL;
    else if (EPS > fabs(handle.dy))
        handle.tangent = HORIZONTAL;
    else if (fabs(handle.dy) > fabs(handle.dx))
        handle.tangent = STEAP;

    return EXIT_SUCCESS;
}

int WU_line_handle_step(WU_line_handle_t &handle)
{
    int rc = CONTINUE_DRAW;

    if (0 == handle.length)
        rc = FINISHED_DRAW;

    if (CONTINUE_DRAW == rc)
    {
        handle.point[0] += handle.dx;
        handle.point[1] += handle.dy;
        handle.length--;
    }

    return rc;
}

void WU_line_handle_get(WU_line_handle_t &handle, WU_result_t &point)
{
    point.amount = 2;

    if (VERTICAL == handle.tangent || HORIZONTAL == handle.tangent)
    {
        point.amount = 1;
        point.start[0] = round(handle.point[0]);
        point.start[1] = round(handle.point[1]);
        point.alpha_start = 1;
    }
    else if (SMOOTH == handle.tangent)
    {
        point.start[0] = round(handle.point[0]);
        point.end[0]   = round(handle.point[0]);
        point.start[1] = floor(handle.point[1]);
        point.end[1]   = floor(handle.point[1]) + 1;

        double base = floor(handle.point[1]);
        point.alpha_start = 1 - (handle.point[1] - base);
    }
    else
    {
        point.start[1] = round(handle.point[1]);
        point.end[1]   = round(handle.point[1]);
        point.start[0] = floor(handle.point[0]);
        point.end[0]   = floor(handle.point[0]) + 1;

        double base = floor(handle.point[0]);
        point.alpha_start = 1 - (handle.point[0] - base);
    }

    point.alpha_end = 1 - point.alpha_start;
}

