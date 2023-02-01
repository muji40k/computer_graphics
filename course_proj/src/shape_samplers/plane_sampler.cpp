#include "plane_sampler.h"

PlaneSampler::PlaneSampler(const Point3<double> &center,
                           const Vector3<double> &x,
                           const Vector3<double> &y,
                           double lx, double ly)
{
    this->base = center;
    this->x = x * (double) lx / 2;
    this->y = y * (double) ly / 2;
}

PlaneSampler::~PlaneSampler(void) {}

bool PlaneSampler::isSamplabel(void) const { return true; }

Point3<double> PlaneSampler::get(void) const
{
    double a = (double)1 - 2 * (double)std::rand() / RAND_MAX,
           b = (double)1 - 2 * (double)std::rand() / RAND_MAX;

    return this->base + (a * this->x + b * this->y);
}

void PlaneSampler::append(const ShapeSampler *) {}

void PlaneSampler::apply(const Transform<double, 3> &transform)
{
    this->base.apply(transform);
    this->x.apply(transform);
    this->y.apply(transform);
}

void PlaneSampler::undo(const Transform<double, 3> &transform)
{
    this->base.undo(transform);
    this->x.undo(transform);
    this->y.undo(transform);
}


