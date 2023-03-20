#include "plane_sampler.h"

PlaneSampler::PlaneSampler(double lx, double ly)
{
    this->x = Vector3<double>({1, 0, 0}) * (double) lx / 2;
    this->y = Vector3<double>({0, 0, 1}) * (double) ly / 2;
    this->transform = std::make_shared<Transform<double, 3>>();
}

PlaneSampler::~PlaneSampler(void) {}

bool PlaneSampler::isSamplabel(void) const { return true; }

Point3<double> PlaneSampler::get(void) const
{
    double a = (double)1 - 2 * (double)std::rand() / RAND_MAX,
           b = (double)1 - 2 * (double)std::rand() / RAND_MAX;

    Point3<double> out = Point3<double>() + (a * this->x + b * this->y);
    out.apply(*this->transform);

    return out;
}

void PlaneSampler::append(const ShapeSampler *) {}

void PlaneSampler::apply(const Transform<double, 3> &transform)
{
    *this->transform += transform;
}

void PlaneSampler::undo(const Transform<double, 3> &transform)
{
    *this->transform += transform.inversed();
}


