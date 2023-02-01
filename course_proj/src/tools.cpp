#include "tools.h"
#include <float.h>
#include <cmath>

tools::sqr_eq_res_t tools::solve_sqr(double a, double b, double c)
{
    sqr_eq_res_t out = {0, {0, 0}};
    double d = b * b - 4 * a * c;

    if (-FLT_EPSILON > d)
        return out;

    if (FLT_EPSILON > d)
    {
        out.n = 1;
        out.x[0] = -b / (2 * a);
    }

    d = sqrt(d);

    out.n = 2;
    double i2a = 1 / (2 * a);
    out.x[0] = (-b - d) * i2a;
    out.x[1] = (-b + d) * i2a;

    return out;
}

