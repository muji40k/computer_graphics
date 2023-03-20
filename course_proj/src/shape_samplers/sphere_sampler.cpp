#include "sphere_sampler.h"
#include <cmath>

SphereSampler::SphereSampler(double radius)
{
    this->radius = radius;
    this->rsqr = radius * radius;
    this->transform = std::make_shared<Transform<double, 3>>();
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

    out.apply(*this->transform);

    return out;
}

void SphereSampler::append(const ShapeSampler *) {}

void SphereSampler::apply(const Transform<double, 3> &transform)
{
    *this->transform += transform;
}

void SphereSampler::undo(const Transform<double, 3> &transform)
{
    *this->transform += transform.inversed();
}

