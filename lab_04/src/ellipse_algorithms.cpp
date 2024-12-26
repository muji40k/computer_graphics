#include <cstdlib>
#include <cmath>
#include "ellipse_algorithms.h"

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

static void point_unpack(const point_t<int> &point, unpacked_dot_t &result)
{
    result.points[0][0] =  point[0];
    result.points[0][1] =  point[1];
    result.points[1][0] = -point[0];
    result.points[1][1] =  point[1];
    result.points[2][0] =  point[0];
    result.points[2][1] = -point[1];
    result.points[3][0] = -point[0];
    result.points[3][1] = -point[1];
}

template <typename Type>
static void point_copy(point_t<Type> &a, const point_t<Type> &b)
{
    for (size_t i = 0; POINT_AMOUNT > i; i++)
        a[i] = b[i];
}

template <typename Type>
static void add_points(point_t<Type> &a, const point_t<Type> &b)
{
    for (size_t i = 0; POINT_AMOUNT > i; i++)
        a[i] += b[i];
}

static void unpack(unpacked_dot_t &result, const point_t<int> &point, 
                   const point_t<int> &center)
{
    point_unpack(point, result);

    for (size_t i = 0; DIMENSIONS > i; i++)
        add_points(result.points[i], center);
}

// Canon
int canon_ellipse_handle_init(canon_ellipse_handle_t &handle,
                              const point_t<int> center, const int a,
                              const int b)
{
    if (0 == a && 0 == b)
        return ERROR_DEGENERATE_ELLIPSE;

    double _a = a, _b = b;

    for (size_t i = 0; POINT_AMOUNT > i; i++)
        handle.center[i] = center[i];

    handle.stage = 0;
    handle.ab_sqr = _a * _a * _b * _b;

    if (b > a)
    {
        handle.a_sqr = _b * _b;
        handle.b_sqr = _a * _a;
        handle.y = _a;
        handle.swap = true;
    }
    else
    {
        handle.a_sqr = _a * _a;
        handle.b_sqr = _b * _b;
        handle.y = _b;
        handle.swap = false;
    }

    handle.limit = round(handle.a_sqr / sqrt(handle.a_sqr + handle.b_sqr));

    handle.x = 0;

    return EXIT_SUCCESS;
}

int canon_ellipse_handle_step(canon_ellipse_handle_t &handle)
{
    int rc = CONTINUE_DRAW;

    if (STAGES_CANON == handle.stage && handle.x == handle.limit + 1)
        rc = FINISHED_DRAW;

    if (CONTINUE_DRAW == rc)
    {
        if (handle.x == handle.limit + 1)
        {
            handle.swap = !handle.swap;
            handle.stage++;
            handle.x = -1;
            unsigned int tmp = handle.a_sqr;
            handle.a_sqr = handle.b_sqr;
            handle.b_sqr = tmp;
            handle.limit = round(handle.a_sqr / sqrt(handle.a_sqr + handle.b_sqr));
        }

        handle.x++;
        handle.y = sqrt((handle.ab_sqr - handle.b_sqr * handle.x * handle.x) \
                        / handle.a_sqr);
    }

    return rc;
}

void canon_ellipse_handle_get(const canon_ellipse_handle_t &handle,
                              unpacked_dot_t &result)
{
    point_t<int> current;

    if (!handle.swap)
    {
        current[0] = handle.x;
        current[1] = round(handle.y);
    }
    else
    {
        current[0] = round(handle.y);
        current[1] = handle.x;
    }

    unpack(result, current, handle.center);
}

// Parametric
int parametric_ellipse_handle_init(parametric_ellipse_handle_t &handle,
                              const point_t<int> center, const int a,
                              const int b)
{
    if (0 == a && 0 == b)
        return ERROR_DEGENERATE_ELLIPSE;

    for (size_t i = 0; POINT_AMOUNT > i; i++)
        handle.center[i] = center[i];

    handle.a = abs(a);
    handle.b = abs(b);

    handle.angle = 0;
    handle.x = handle.a;
    handle.y = 0;

    if (handle.a > handle.b)
        handle.step = (double)1 / handle.a;
    else
        handle.step = (double)1 / handle.b;

    return EXIT_SUCCESS;
}

int parametric_ellipse_handle_step(parametric_ellipse_handle_t &handle)
{
    int rc = CONTINUE_DRAW;

    if (handle.angle > M_PI / 2 + EPS)
        rc = FINISHED_DRAW;

    if (CONTINUE_DRAW == rc)
    {
        handle.angle += handle.step;
        handle.x = round(cos(handle.angle) * handle.a);
        handle.y = round(sin(handle.angle) * handle.b);
    }

    return rc;
}

void parametric_ellipse_handle_get(const parametric_ellipse_handle_t &handle,
                                   unpacked_dot_t &result)
{
    point_t<int> current;
    current[0] = handle.x;
    current[1] = handle.y;

    unpack(result, current, handle.center);
}

// Bresenham

typedef enum
{
    HORIZONTAL,
    DIAGONAL,
    VERTICAL
} Bresenham_step_t;

int Bresenham_ellipse_handle_init(Bresenham_ellipse_handle_t &handle,
                              const point_t<int> center, const int a,
                              const int b)
{
    if (0 == a && 0 == b)
        return ERROR_DEGENERATE_ELLIPSE;

    for (size_t i = 0; POINT_AMOUNT > i; i++)
        handle.center[i] = center[i];

    handle.a_sqr = a * a;
    handle.b_sqr = b * b;
    handle.ab_sqr = handle.a_sqr * handle.b_sqr;

    handle.f = (long long)(handle.b_sqr + handle.a_sqr) \
               - 2 * handle.a_sqr * b;
    handle.x = 0;
    handle.y = b;

    return EXIT_SUCCESS;
}

int Bresenham_ellipse_handle_step(Bresenham_ellipse_handle_t &handle)
{
    int rc = CONTINUE_DRAW;

    if (0 >= handle.y)
        rc = FINISHED_DRAW;

    if (CONTINUE_DRAW == rc)
    {
        Bresenham_step_t step = DIAGONAL;
        long long delta = 0;

        if (0 > handle.f)
        {
            delta = 2 * handle.f + (long long)handle.a_sqr * (2 * handle.y - 1);

            if (delta < 0)
                step = HORIZONTAL;
        }
        else if (0 < handle.f)
        {
            delta = 2 * handle.f + (long long)handle.b_sqr * (1 - 2 * handle.x);

            if (delta > 0)
                step = VERTICAL;
        }

        if (DIAGONAL == step)
        {
            handle.f += (long long)2 * ((long long)handle.b_sqr * handle.x \
                                        - handle.a_sqr * handle.y)         \
                        + 3 * (handle.a_sqr + handle.b_sqr);
            handle.x++;
            handle.y--;
        }
        else if (HORIZONTAL == step)
        {
            handle.f += handle.b_sqr * (2 * handle.x + 3);
            handle.x++;
        }
        else
        {
            handle.f += (long long)handle.a_sqr * (3 - 2 * handle.y);
            handle.y--;
        }
    }

    return rc;
}

void Bresenham_ellipse_handle_get(const Bresenham_ellipse_handle_t &handle,
                                   unpacked_dot_t &result)
{
    point_t<int> current;
    current[0] = handle.x;
    current[1] = handle.y;

    unpack(result, current, handle.center);
}

// Middle point
int middle_point_ellipse_handle_init(middle_point_ellipse_handle_t &handle,
                              const point_t<int> center, const int a,
                              const int b)
{
    if (0 == a && 0 == b)
        return ERROR_DEGENERATE_ELLIPSE;

    for (size_t i = 0; POINT_AMOUNT > i; i++)
        handle.center[i] = center[i];

    handle.a_sqr = a * a;
    handle.b_sqr = b * b;
    handle.da = 2 * handle.a_sqr;
    handle.db = 2 * handle.b_sqr;
    handle.dx = 0;
    handle.dy = -handle.da * b;

    handle.bend = round((double)handle.a_sqr / sqrt(handle.a_sqr + handle.b_sqr));

    double _a = a, _b = b;

    handle.f = _b * _b - _a * _a * _b + _a * _a / 4;
    handle.x = 0;
    handle.y = abs(b);

    return EXIT_SUCCESS;
}

int middle_point_ellipse_handle_step(middle_point_ellipse_handle_t &handle)
{
    int rc = CONTINUE_DRAW;

    if (0 >= handle.y)
        rc = FINISHED_DRAW;

    if (CONTINUE_DRAW == rc)
    {
        if (handle.x < handle.bend)
        {
            if (-EPS < handle.f)
            {
                handle.y--;
                handle.dy += handle.da;
                handle.f += handle.dy;
            }

            handle.x++;
            handle.dx += handle.db;
            handle.f  += (long long)handle.b_sqr + handle.dx;

            if (handle.x == handle.bend)
                handle.f -= (double)(handle.dx - handle.dy) / 2 \
                            + (double)3 / 4 * ((double)handle.b_sqr - handle.a_sqr);
        }
        else
        {
            if (EPS > handle.f)
            {
                handle.x++;
                handle.dx += handle.db;
                handle.f += handle.dx;
            }

            handle.y--;
            handle.dy += handle.da;
            handle.f  += (long long)handle.a_sqr + handle.dy;
        }
    }

    return rc;
}

void middle_point_ellipse_handle_get(const middle_point_ellipse_handle_t &handle,
                                   unpacked_dot_t &result)
{
    point_t<int> current;
    current[0] = handle.x;
    current[1] = handle.y;

    unpack(result, current, handle.center);
}

