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
    double i2a = (double)1 / (2 * a);
    out.x[0] = (-b - d) * i2a;
    out.x[1] = (-b + d) * i2a;

    return out;
}

tools::intersection_res_t tools::intersect_plane(const Point3<double> &center,
                                                 const Normal3<double> &normal,
                                                 const Ray3<double> &ray)
{
    intersection_res_t res = {0, false};
    double denominator = ray.getDirection() & normal;

    if (FLT_EPSILON > fabs(denominator))
        return res;

    res.t = ((ray.getOrigin() > center) & normal) / denominator;
    res.valid = true;

    return res;
}

Vector3<double> get_orthogonal_vector(const Vector3<double> vec)
{
    size_t i = 0;

    for (; vec.size() > i && FLT_EPSILON > abs(vec[i]); i++);

    if (vec.size() == i)
        return vec;

    Vector3<double> out = vec;
    double sum_sqr = 0;

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

Vector3<double> tools::get_reflection(const Normal3<double> &normal,
                                      const Vector3<double> &vec)
{
    Vector3<double> norm (normal);
    double ilnormsqr = (double)1 / norm.lengthSqr();

    if (FLT_EPSILON > (norm & vec))
        norm *= -1;

    return 2 * (norm & vec) * ilnormsqr * norm - vec;
}

tools::transmission_res_t tools::get_transmission(const Normal3<double> &normal,
                                                  const Vector3<double> &vec,
                                                  double n1, double n2)
{
    transmission_res_t out = {Vector3<double>(), false};
    Vector3<double> norm (normal);

    if (0 > (norm & vec))
        norm *= -1;

    if (FLT_EPSILON > fabs((norm & vec) - 1))
        return {-vec, true};

    double lnorm = norm.length();
    double lvec = vec.length();
    double ilnormsqr = (double)1 / (lnorm * lnorm);
    double ilnorm = (double)1 / lnorm;
    double ilnormvec = (double)1 / (lnorm * lvec);

    double disc = n2 * n2 - n1 * n1 * (1 - pow((norm & vec) * ilnormvec, 2));
    n2 = (double)1 / n2;

    if (-FLT_EPSILON > disc)
        return out;

    out.valid = true;
    out.vector = n1 * n2 * ((norm & vec) * ilnormsqr * norm - vec);

    if (FLT_EPSILON < disc)
        out.vector += -lvec * sqrt(disc) * ilnorm * n2 * norm;

    return out;
}

double tools::fresnel_dielectric(const Vector3<double> &in,
                                 const Normal3<double> &normal,
                                 double n1, double n2)
{
    Normal3<double> norm (normal);

    if (0 > (norm & in))
        norm *= -1;

    transmission_res_t res = get_transmission(norm, in, n1, n2);

    if (!res.valid)
        return 1;

    double il_sqr = (double)1 / (in.length() * norm.length());
    double cos_in = fabs(in & norm) * il_sqr,
           cos_out = fabs(res.vector & norm) * il_sqr;
    double r_parallel = (n2 * cos_in - n1 * cos_out) \
                        / (n2 * cos_in + n1 * cos_out),
           r_perpend  = (n1 * cos_in - n2 * cos_out) \
                        / (n1 * cos_in + n2 * cos_out);

    return (r_parallel * r_parallel + r_perpend * r_perpend) / 2;
}

double tools::fresnel_conductor(const Vector3<double> &in, const Normal3<double> &normal,
                                double n1, std::complex<double> n2)
{
    if (FLT_EPSILON > (normal & in))
        return 0;

    double n = n2.real() / n1, k = n2.imag() / n1;
    double cos_in = (in & normal) / (in.length() * normal.length());

    double cos_sqr = cos_in * cos_in;
    double sin_sqr = 1 - cos_sqr;
    double sin_quad = sin_sqr * sin_sqr;

    double nn = n * n, kk = k * k;
    double nksin = nn - kk - sin_sqr;
    double aabb = sqrt(nksin * nksin + 4 * nn * kk);
    double a2cos = sqrt((aabb + nksin) * 2) * cos_in;
    double a2cos_sin_sqr = a2cos * sin_sqr;
    double aabb_cos_sqr = aabb * cos_sqr;

    double r_perpend  = (aabb - a2cos + cos_sqr) \
                        / (aabb + a2cos + cos_sqr);
    double r_parallel = (aabb_cos_sqr - a2cos_sin_sqr + sin_quad)   \
                        / (aabb_cos_sqr + a2cos_sin_sqr + sin_quad) \
                        * r_perpend;

    return (r_parallel * r_parallel + r_perpend * r_perpend) / 2;
}

std::vector<std::string> tools::split(const std::string &target, const char delimiter,
                                      const bool concat_delim)
{
    std::vector<std::string> out;
    size_t i = 0, s = 0, is_token = 0;

    for (; target.size() > i; i++)
    {
        if (delimiter == target[i])
        {
            if (is_token)
            {
                out.push_back(target.substr(s, i - s));
                is_token = 0;
            }
            else if (!concat_delim)
                out.push_back("");
        }
        else if (!is_token)
        {
            is_token = 1;
            s = i;
        }
    }

    if (is_token)
        out.push_back(target.substr(s, i - s));

    return out;
}

