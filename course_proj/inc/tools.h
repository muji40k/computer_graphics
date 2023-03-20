#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "point.h"
#include "vector.h"
#include "normal.h"
#include "ray.h"

#include <vector>
#include <string>
#include <complex>

namespace tools
{

typedef struct 
{
    int n;
    double x[2];
} sqr_eq_res_t;

sqr_eq_res_t solve_sqr(double a, double b, double c);

typedef struct 
{
    double t;
    bool valid;
} intersection_res_t;

intersection_res_t intersect_plane(const Point3<double> &center,
                                   const Normal3<double> &normal,
                                   const Ray3<double> &ray);

Vector3<double> get_orthogonal_vector(const Vector3<double> vec);

Vector3<double> get_reflection(const Normal3<double> &normal,
                               const Vector3<double> &vec);

typedef struct 
{
    Vector3<double> vector;
    bool valid;
} transmission_res_t;

transmission_res_t get_transmission(const Normal3<double> &normal,
                                    const Vector3<double> &vec,
                                    double n1, double n2);

double fresnel_dielectric(const Vector3<double> &in, const Normal3<double> &normal,
                          double n1, double n2);

double fresnel_conductor(const Vector3<double> &in, const Normal3<double> &normal,
                         double n1, std::complex<double> n2);

std::vector<std::string> split(const std::string &target, const char delimiter,
                               const bool concat_delim = true);

}

#endif

