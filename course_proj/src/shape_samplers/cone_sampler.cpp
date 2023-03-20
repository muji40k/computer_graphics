#include "cone_sampler.h"

#include "tools.h"

ConeSampler::ConeSampler(double length, double radius)
{
    this->length = length;
    this->radius = radius;
    this->transform = std::make_shared<Transform<double, 3>>();
}

ConeSampler::~ConeSampler(void) {}

bool ConeSampler::isSamplabel(void) const { return true; }

Point3<double> ConeSampler::get(void) const
{
    double l = (double)std::rand() / RAND_MAX,
           a = 2 * M_PI * (double)std::rand() / RAND_MAX;

    double r = l * this->radius;
    l = (1 - l) * this->length;
    Point3<double> center;
    Vector3<double> x ({1, 0, 0}), y ({0, 0, 1}), dir ({0, 1, 0});

    Point3<double> out = center + r * (x * cos(a) + y * sin(a)) + l * dir;
    out.apply(*this->transform);

    return out;
}

void ConeSampler::append(const ShapeSampler *) {}

void ConeSampler::apply(const Transform<double, 3> &transform)
{
    *this->transform += transform;
}

void ConeSampler::undo(const Transform<double, 3> &transform)
{
    *this->transform += transform.inversed();
}

