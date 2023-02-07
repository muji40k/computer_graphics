#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "vector.h"

#include <vector>
#include <string>

namespace tools
{

typedef struct 
{
    int n;
    double x[2];
} sqr_eq_res_t;

sqr_eq_res_t solve_sqr(double a, double b, double c);

template<typename Type>
Vector3<Type> get_orthogonal_vector(const Vector3<Type> vec)
{
    size_t i = 0;

    for (; vec.size() > i && FLT_EPSILON > abs(vec[i]); i++);

    if (vec.size() == i)
        return vec;

    Vector3<Type> out = vec;
    Type sum_sqr = Type();

    for (size_t j = 0; vec.size() > j; j++)
        if (i != j)
            sum_sqr += vec[j] * vec[j];

    if (FLT_EPSILON < double(sum_sqr))
        out[i] = -sum_sqr / vec[i];
    else
    {
        out[i + 1] = vec[i];
        out[i] = vec[i + 1];
    }

    return out;
}

std::vector<std::string> split(const std::string &target, const char delimiter,
                               const bool concat_delim = true);

}

#endif

