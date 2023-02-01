#include "polygon_sampler.h"
#include <cmath>

PolygonSampler::PolygonSampler(const Point3<double> &a, const Point3<double> &b,
                               const Point3<double> &c)
{
    this->base = a;
    this->a = a > b;
    this->b = a > c;
}

PolygonSampler::~PolygonSampler(void) {}

bool PolygonSampler::isSamplabel(void) const { return true; }

Point3<double> PolygonSampler::get(void) const
{
    double k1 = sqrt((double)std::rand() / RAND_MAX),
           k2 = (double)std::rand() / RAND_MAX;

    return this->base + (((double)1 - k1) * this->a + k1 * k2 * this->b);
}

void PolygonSampler::append(const ShapeSampler *) {}

void PolygonSampler::apply(const Transform<double, 3> &transform)
{
    this->base.apply(transform);
    this->a.apply(transform);
    this->b.apply(transform);
}

void PolygonSampler::undo(const Transform<double, 3> &transform)
{
    this->base.undo(transform);
    this->a.undo(transform);
    this->b.undo(transform);
}


