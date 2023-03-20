#include "scattering_unit.h"

ScatteringUnit::ScatteringUnit(const Scene &scene,
                               const std::list<std::shared_ptr<const ScatteringFunction>> &functions,
                               const Ray3<double> &ray,
                               std::complex<double> r_index)
    : scene(scene), functions(functions), r_index(r_index)
{
    this->point = std::make_shared<Point3<double>>(ray.getOrigin());
    this->vector = std::make_shared<Vector3<double>>(ray.getDirection());
    this->sampler = nullptr;
}

ScatteringUnit::ScatteringUnit(const Scene &scene,
                               const std::list<std::shared_ptr<const ScatteringFunction>> &functions,
                               const std::shared_ptr<const ShapeSampler> &sampler,
                               const Point3<double> &origin,
                               const size_t n_samples,
                               std::complex<double> r_index)
    : scene(scene), functions(functions), samples(n_samples), r_index(r_index)
{
    this->point = std::make_shared<Point3<double>>(origin);
    this->vector = nullptr;
    this->sampler = sampler;
}

ScatteringUnit::ScatteringUnit(const Scene &scene,
                               const std::list<std::shared_ptr<const ScatteringFunction>> &functions,
                               const std::shared_ptr<const ShapeSampler> &sampler,
                               const Vector3<double> &direction,
                               const size_t n_samples,
                               std::complex<double> r_index)
    : scene(scene), functions(functions), samples(n_samples), r_index(r_index)
{
    this->point = nullptr;
    this->vector = std::make_shared<Vector3<double>>(direction);
    this->sampler = sampler;
}

const std::list<std::shared_ptr<const ScatteringFunction>> &ScatteringUnit::getFunctions(void)
{
    return this->functions;
}

std::complex<double> ScatteringUnit::getRefractionIndex(void)
{
    return this->r_index;
}

void ScatteringUnit::scatter(const SceneTracer &tracer)
{
    if (0 != this->targets.size())
        return;

    if (nullptr == this->sampler)
        this->main_scatter(tracer, Ray3<double>(*this->point, *this->vector));
    else if (nullptr == vector)
        this->sample_point(tracer);
    else
        this->sample_direction(tracer);
}

ScatteringUnit::iterator ScatteringUnit::begin(void)
{
    return this->targets.begin();
}

ScatteringUnit::iterator ScatteringUnit::end(void)
{
    return this->targets.end();
}

ScatteringUnit::const_iterator ScatteringUnit::begin(void) const
{
    return this->targets.cbegin();
}

ScatteringUnit::const_iterator ScatteringUnit::end(void) const
{
    return this->targets.cend();
}

ScatteringUnit::const_iterator ScatteringUnit::cbegin(void) const
{
    return this->targets.cbegin();
}

ScatteringUnit::const_iterator ScatteringUnit::cend(void) const
{
    return this->targets.cend();
}

void ScatteringUnit::main_scatter(const SceneTracer &tracer,
                                  const Ray3<double> &ray)
{
    Intersection inter = tracer.trace(this->scene, ray);
    Ray3<double> flip (ray.getOrigin(), -ray.getDirection());

    if (!inter)
        this->targets.push_back(std::make_shared<TracingUnit>(flip, this->r_index));
    else
        this->targets.push_back(std::make_shared<TracingUnit>(inter, flip, this->r_index));
}


void ScatteringUnit::sample_point(const SceneTracer &tracer)
{
    Ray3<double> ray (Point3<double>(), *this->vector);

    for (size_t i = 0; this->samples > i; i++)
    {
        ray.setOrigin(this->sampler->get());
        this->main_scatter(tracer, ray);
    }
}

void ScatteringUnit::sample_direction(const SceneTracer &tracer)
{
    Ray3<double> ray (*this->point, Vector3<double>());

    for (size_t i = 0; this->samples > i; i++)
    {
        ray.setDirection(*this->point > this->sampler->get());
        this->main_scatter(tracer, ray);
    }
}

