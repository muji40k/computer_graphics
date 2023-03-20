#include "disk_sampler.h"
#include "transform_strategies.h"

#include "tools.h"

DiskSampler::DiskSampler(double radius)
{
    this->radius = radius;
    this->transform = std::make_shared<Transform<double, 3>>();
}

DiskSampler::~DiskSampler(void) {}

bool DiskSampler::isSamplabel(void) const { return true; }

Point3<double> DiskSampler::get(void) const
{
    double r = this->radius * sqrt((double)std::rand() / RAND_MAX),
           a = 2 * M_PI * (double)std::rand() / RAND_MAX;

    Point3<double> center;
    Vector3<double> x ({1, 0, 0}), y ({0, 0, 1});

    Point3<double> out = center + r * cos(a) * x + r * sin(a) * y;
    out.apply(*this->transform);

    return out;
}

void DiskSampler::append(const ShapeSampler *) {}

void DiskSampler::apply(const Transform<double, 3> &transform)
{
    *this->transform += transform;
}

void DiskSampler::undo(const Transform<double, 3> &transform)
{
    *this->transform += transform.inversed();
}

