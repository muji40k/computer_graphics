#include "disk_sampler.h"
#include "transform_strategies.h"

#include "tools.h"

DiskSampler::DiskSampler(const Point3<double> &center,
                         const Vector3<double> &normal,
                         double radius)
{
    this->center = center;
    this->normal = normal;
    this->radius = radius;

    this->resetXY();
}

DiskSampler::~DiskSampler(void) {}

bool DiskSampler::isSamplabel(void) const { return true; }

Point3<double> DiskSampler::get(void) const
{
    double r = this->radius * sqrt((double)std::rand() / RAND_MAX),
           a = 2 * M_PI * (double)std::rand() / RAND_MAX;

    return this->center + r * cos(a) * this->x + r * sin(a) * this->y;
}

void DiskSampler::append(const ShapeSampler *) {}

void DiskSampler::apply(const Transform<double, 3> &transform)
{
    this->center.apply(transform);
    this->normal.apply(transform);

    this->resetXY();
}

void DiskSampler::undo(const Transform<double, 3> &transform)
{
    this->center.undo(transform);
    this->normal.undo(transform);

    this->resetXY();
}

void DiskSampler::resetXY(void)
{
    Vector3<double> &n = this->normal;
    this->x = tools::get_orthogonal_vector(n).normalised();
    this->y = (n * this->x).normalised();
}

