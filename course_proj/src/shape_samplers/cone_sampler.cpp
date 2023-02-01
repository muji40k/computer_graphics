#include "cone_sampler.h"

ConeSampler::ConeSampler(const Vector3<double> &normal,
                         const Point3<double> &center,
                         double length, double radius)
{
    this->normal = normal.normalised();
    this->base = center + this->normal * length / 2;
    this->length = length;
    this->radius = radius;

    this->resetXY();
}

ConeSampler::~ConeSampler(void) {}

bool ConeSampler::isSamplabel(void) const { return true; }

Point3<double> ConeSampler::get(void) const
{
    double l = (double)std::rand() / RAND_MAX,
           a = 2 * M_PI * (double)std::rand() / RAND_MAX;

    double r = l * this->radius;
    l = (1 - l) * this->length;

    return this->base + r * (this->x * cos(a) + this->y * sin(a)) \
           + l * this->normal;
}

void ConeSampler::append(const ShapeSampler *) {}

void ConeSampler::apply(const Transform<double, 3> &transform)
{
    this->base.apply(transform);
    this->normal.apply(transform);

    this->resetXY();
}

void ConeSampler::undo(const Transform<double, 3> &transform)
{
    this->base.undo(transform);
    this->normal.undo(transform);

    this->resetXY();
}

void ConeSampler::resetXY(void)
{
    Vector3<double> n (this->normal);

    this->x = (n * Vector3<double>({1, 0, 0})).normalised();
    this->y = (n * x).normalised();
}

