#ifndef _TOOLS_H_
#define _TOOLS_H_

namespace tools
{

typedef struct 
{
    int n;
    double x[2];
} sqr_eq_res_t;

sqr_eq_res_t solve_sqr(double a, double b, double c);

}

#endif

