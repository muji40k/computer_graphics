#include "tube_sampler.h"

TubeSampler::TubeSampler(const Vector3<double> &normal,
                         const Point3<double> &center,
                         double length, double radius)
{
    this->normal = normal.normalised();
    this->base = center + this->normal * length / 2;
    this->length = length;
    this->radius = radius;

    this->resetXY();
}

TubeSampler::~TubeSampler(void) {}

bool TubeSampler::isSamplabel(void) const { return true; }

Point3<double> TubeSampler::get(void) const
{
    double l = this->length * (double)std::rand() / RAND_MAX,
           a = 2 * M_PI * (double)std::rand() / RAND_MAX;

    return this->base + this->radius * (this->x * cos(a) + this->y * sin(a)) \
           + l * this->normal;
}

void TubeSampler::append(const ShapeSampler *) {}

void TubeSampler::apply(const Transform<double, 3> &transform)
{
    this->base.apply(transform);
    this->normal.apply(transform);

    this->resetXY();
}

void TubeSampler::undo(const Transform<double, 3> &transform)
{
    this->base.undo(transform);
    this->normal.undo(transform);

    this->resetXY();
}

void TubeSampler::resetXY(void)
{
    Vector3<double> n (this->normal);

    this->x = (n * Vector3<double>({1, 0, 0})).normalised();
    this->y = (n * x).normalised();
}

