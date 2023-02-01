#include "composite_sampler.h"

CompositeSampler::~CompositeSampler(void) {}

bool CompositeSampler::isSamplabel(void) const { return true; }

Point3<double> CompositeSampler::get(void) const
{
    size_t i = std::rand() % this->samplers.size();
    auto iter = this->samplers.begin();

    for (; i; i--, iter++);

    return (*iter)->get();
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

void CompositeSampler::apply(const Transform<double, 3> &) {}
void CompositeSampler::undo(const Transform<double, 3> &) {}

