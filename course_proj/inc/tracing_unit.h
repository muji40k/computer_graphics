#ifndef _TRACING_UNIT_H_
#define _TRACING_UNIT_H_

#include <memory>
#include <list>

#include "base_exception.h"

#include "intensity.h"

#include "shape.h"

class TracingUnit;

#include "scattering_unit.h"
#include "light_tracer.h"

class TracingUnit
{
    public:
        using iterator = std::list<std::shared_ptr<ScatteringUnit>>::iterator;
        using const_iterator = std::list<std::shared_ptr<ScatteringUnit>>::const_iterator;

        TracingUnit(const Intersection &intersection, const Ray3<double> &in,
                    std::complex<double> outer_r_index = std::complex<double>(1, 0));
        TracingUnit(const Ray3<double> &in,
                    std::complex<double> outer_r_index = std::complex<double>(1, 0));

        bool isTerminate(void) const;
        void makeTerminate(void);
        const Intersection &getIntersection(void) const;
        const Vector3<double> getInVector(void) const;
        const Ray3<double> &getInRay(void) const;

        void setBaseIntensity(const Intensity<> &intensity);
        const Intensity<> &getBaseIntensity(void) const;

        const Intensity<> &getEmission(void) const;
        void accumulate(const Intensity<> &emission);
        void accumulate(const const_iterator &iter);

        void add(const std::shared_ptr<ScatteringUnit> &unit);

        const std::complex<double> getOuterRefractionIndex(void);

        iterator begin(void);
        iterator end(void);
        const_iterator begin(void) const;
        const_iterator end(void) const;
        const_iterator cbegin(void) const;
        const_iterator cend(void) const;

    private:
        bool terminate;
        std::shared_ptr<Ray3<double>> in;
        std::shared_ptr<Intersection> intersection;
        std::shared_ptr<Point3<double>> cache_point;

        std::complex<double> outer_r_index;

        std::shared_ptr<Intensity<>> base;
        std::shared_ptr<Intensity<>> emission;

        std::list<std::shared_ptr<ScatteringUnit>> scattering;
};

DEF_EX(CommonTracingUnitException, BaseException,
       "General tracing_unit exception");
DEF_EX(TerminateTracingUnitException, CommonTracingUnitException,
       "Attempt to operate with terminate tracing unit");

#endif

