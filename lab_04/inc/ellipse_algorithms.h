#ifndef _LINE_ALGORITHMS_H_
#define _LINE_ALGORITHMS_H_

#include <cstdlib>

#define ERROR_DEGENERATE_ELLIPSE 100

#define CONTINUE_DRAW 0
#define FINISHED_DRAW 1

#define DIMENSIONS 4

#define POINT_AMOUNT 2

template <typename T>
using point_t = T[POINT_AMOUNT];

typedef struct
{
    point_t<int> points[DIMENSIONS];
} unpacked_dot_t;

// Canon
#define STAGES_CANON 2

typedef struct
{
    point_t<int> center;
    double ab_sqr;
    double a_sqr;
    double b_sqr;
    int x;
    double y;
    int limit;
    size_t stage;
    bool swap;
} canon_ellipse_handle_t;

int canon_ellipse_handle_init(canon_ellipse_handle_t &handle,
                              const point_t<int> center, const int a,
                              const int b);
int canon_ellipse_handle_step(canon_ellipse_handle_t &handle);
void canon_ellipse_handle_get(const canon_ellipse_handle_t &handle,
                              unpacked_dot_t &result);

// Parametric
typedef struct
{
    point_t<int> center;
    unsigned int a;
    unsigned int b;
    double angle;
    double step;
    int x;
    int y;
} parametric_ellipse_handle_t;

int parametric_ellipse_handle_init(parametric_ellipse_handle_t &handle,
                                   const point_t<int> center, const int a,
                                   const int b);
int parametric_ellipse_handle_step(parametric_ellipse_handle_t &handle);
void parametric_ellipse_handle_get(const parametric_ellipse_handle_t &handle,
                                   unpacked_dot_t &result);

// Bresenham
#define STAGES_MIDDLE_POINT 2
typedef struct
{
    point_t<int> center;
    unsigned long a_sqr;
    unsigned long b_sqr;
    unsigned long ab_sqr;
    long long f;
    int x;
    int y;
} Bresenham_ellipse_handle_t;

int Bresenham_ellipse_handle_init(Bresenham_ellipse_handle_t &handle,
                                     const point_t<int> center, const int a,
                                     const int b);
int Bresenham_ellipse_handle_step(Bresenham_ellipse_handle_t &handle);
void Bresenham_ellipse_handle_get(const Bresenham_ellipse_handle_t &handle,
                                     unpacked_dot_t &result);

// Middle point
#define STAGES_MIDDLE_POINT 2
typedef struct
{
    point_t<int> center;
    unsigned long a_sqr;
    unsigned long b_sqr;
    long long da;
    long long db;
    long long dx;
    long long dy;
    double f;
    int x;
    int y;
    int bend;
} middle_point_ellipse_handle_t;

int middle_point_ellipse_handle_init(middle_point_ellipse_handle_t &handle,
                                     const point_t<int> center, const int a,
                                     const int b);
int middle_point_ellipse_handle_step(middle_point_ellipse_handle_t &handle);
void middle_point_ellipse_handle_get(const middle_point_ellipse_handle_t &handle,
                                     unpacked_dot_t &result);

#endif

