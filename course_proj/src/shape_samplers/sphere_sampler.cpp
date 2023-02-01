#include "sphere_sampler.h"
#include <cmath>

SphereSampler::SphereSampler(const Point3<double> &center, double radius)
{
    this->center = center;
    this->radius = radius;
    this->rsqr = radius * radius;
}

SphereSampler::~SphereSampler(void) {}

bool SphereSampler::isSamplabel(void) const { return true; }

Point3<double> SphereSampler::get(void) const
{
    Point3<double> out;

    double r = this->radius * sqrt((double)std::rand() / RAND_MAX),
           a = 2 * M_PI * (double)std::rand() / RAND_MAX;

    out.x = r * cos(a);
    out.y = r * sin(a);
    out.z = (1 - 2 * (std::rand() % 2)) \
            * sqrt(this->rsqr - out.x * out.x - out.y * out.y);

    return out + this->center;
}

void SphereSampler::append(const ShapeSampler *) {}

void SphereSampler::apply(const Transform<double, 3> &transform)
{
    this->center.apply(transform);
}

void SphereSampler::undo(const Transform<double, 3> &transform)
{
    this->center.undo(transform);
}

