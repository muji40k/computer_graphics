#include "tube_sampler.h"

#include "tools.h"

TubeSampler::TubeSampler(double length, double radius)
{
    this->length = length;
    this->radius = radius;
    this->transform = std::make_shared<Transform<double, 3>>();
}

TubeSampler::~TubeSampler(void) {}

bool TubeSampler::isSamplabel(void) const { return true; }

Point3<double> TubeSampler::get(void) const
{
    double l = this->length * (double)std::rand() / RAND_MAX,
           a = 2 * M_PI * (double)std::rand() / RAND_MAX;

    Point3<double> center;
    Vector3<double> x ({1, 0, 0}), y ({0, 0, 1}), dir ({0, 1, 0});

    Point3<double> out = center + this->radius * (x * cos(a) + y * sin(a)) \
                         + l * dir;
    out.apply(*this->transform);

    return out;
}

void TubeSampler::append(const ShapeSampler *) {}

void TubeSampler::apply(const Transform<double, 3> &transform)
{
    *this->transform += transform;
}

void TubeSampler::undo(const Transform<double, 3> &transform)
{
    *this->transform += transform.inversed();
}

