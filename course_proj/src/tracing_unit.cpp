#include "tracing_unit.h"

TracingUnit::TracingUnit(const Intersection &intersection,
                         const Ray3<double> &in,
                         std::complex<double> outer_r_index)
{
    this->in = std::make_shared<Ray3<double>>(in);
    this->intersection = std::make_shared<Intersection>(intersection);

    this->emission = std::make_shared<Intensity<>>();
    this->base = std::make_shared<Intensity<>>();

    this->cache_point = std::make_shared<Point3<double>>(intersection.getPoint());
    this->cache_point->apply(intersection.toGlobal());

    this->outer_r_index = outer_r_index;

    this->terminate = false;
}

TracingUnit::TracingUnit(const Ray3<double> &in,
                         std::complex<double> outer_r_index)
{
    this->terminate = true;
    this->emission = std::make_shared<Intensity<>>(Intensity<>({1, 1, 1}));
    this->base = std::make_shared<Intensity<>>();
    this->in = std::make_shared<Ray3<double>>(in);

    this->outer_r_index = outer_r_index;

    this->cache_point = nullptr;
}

bool TracingUnit::isTerminate(void) const
{
    return this->terminate;
}

void TracingUnit::makeTerminate(void)
{
    this->terminate = true;
}

const Intersection &TracingUnit::getIntersection(void) const
{
    if (this->terminate)
        throw CALL_EX(TerminateTracingUnitException);

    return *this->intersection;
}

const Vector3<double> TracingUnit::getInVector(void) const
{
    return this->in->getDirection();
}

const Ray3<double> &TracingUnit::getInRay(void) const
{
    return *this->in;
}

void TracingUnit::setBaseIntensity(const Intensity<> &intensity)
{
    *this->base = intensity;
}

const Intensity<> &TracingUnit::getBaseIntensity(void) const
{
    return *this->base;
}

const Intensity<> &TracingUnit::getEmission(void) const
{
    return *this->emission;
}

void TracingUnit::accumulate(const Intensity<> &emission)
{
    if (this->terminate)
        throw CALL_EX(TerminateTracingUnitException);

    *this->emission += emission;
}

void TracingUnit::accumulate(const TracingUnit::const_iterator &iter)
{
    if (this->terminate)
        throw CALL_EX(TerminateTracingUnitException);

    const std::shared_ptr<ScatteringUnit> &unit = *iter;

    for (const std::shared_ptr<TracingUnit> &target : *unit)
    {
        Intensity<> emission = target->getBaseIntensity() \
                               * target->getEmission();

        if (!target->terminate)
        {
            double distanse = distanceSqr(*this->cache_point, *target->cache_point);
            emission /= distanse * unit->getRefractionIndex().real();
        }

        for (std::shared_ptr<const ScatteringFunction> func : unit->getFunctions())
            *this->emission += emission * func->apply(-target->in->getDirection(),
                                                      this->in->getDirection());
    }
}

void TracingUnit::add(const std::shared_ptr<ScatteringUnit> &unit)
{
    this->scattering.push_back(unit);
}

const std::complex<double> TracingUnit::getOuterRefractionIndex(void)
{
    return this->outer_r_index;
}

TracingUnit::iterator TracingUnit::begin(void)
{
    return this->scattering.begin();
}

TracingUnit::iterator TracingUnit::end(void)
{
    return this->scattering.end();
}

TracingUnit::const_iterator TracingUnit::begin(void) const
{
    return this->scattering.cbegin();
}

TracingUnit::const_iterator TracingUnit::end(void) const
{
    return this->scattering.cend();
}

TracingUnit::const_iterator TracingUnit::cbegin(void) const
{
    return this->scattering.cbegin();
}

TracingUnit::const_iterator TracingUnit::cend(void) const
{
    return this->scattering.cend();
}

