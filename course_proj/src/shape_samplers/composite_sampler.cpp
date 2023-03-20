#include "composite_sampler.h"

CompositeSampler::CompositeSampler(void)
{
    this->transform = std::make_shared<Transform<double, 3>>();
}

CompositeSampler::~CompositeSampler(void) {}

bool CompositeSampler::isSamplabel(void) const { return true; }

Point3<double> CompositeSampler::get(void) const
{
    size_t i = std::rand() % this->samplers.size();
    auto iter = this->samplers.begin();

    for (; i; i--, iter++);

    Point3<double> out = (*iter)->get();
    out.apply(*this->transform);

    return out;
}

void CompositeSampler::append(const ShapeSampler *sampler)
{
    bool in = false;
    auto iter = this->samplers.begin();

    for (; !in && iter != this->samplers.end(); iter++)
        if (sampler == *iter)
            in = true;

    if (!in)
        this->samplers.push_back(sampler);
}

void CompositeSampler::apply(const Transform<double, 3> &transform)
{
    *this->transform += transform;
}

void CompositeSampler::undo(const Transform<double, 3> &transform)
{
    *this->transform += transform.inversed();
}

