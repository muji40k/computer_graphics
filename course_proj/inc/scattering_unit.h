#ifndef _SCATTERING_UNIT_H_
#define _SCATTERING_UNIT_H_

#include <memory>
#include <list>
#include <complex>

#include "base_exception.h"

class ScatteringUnit;

#include "scene_tracer.h"
#include "scene.h"
#include "environment_map.h"
#include "tracing_unit.h"
#include "scattering_function.h"
#include "shape_sampler.h"
#include "point.h"
#include "vector.h"
#include "ray.h"

class ScatteringUnit
{
    public:
        using iterator = std::list<std::shared_ptr<TracingUnit>>::iterator;
        using const_iterator = std::list<std::shared_ptr<TracingUnit>>::const_iterator;

        ScatteringUnit(const Scene &scene,
                       const std::list<std::shared_ptr<const ScatteringFunction>> &functions,
                       const Ray3<double> &ray,
                       std::complex<double> r_index = std::complex<double>(1, 0));
        ScatteringUnit(const Scene &scene,
                       const std::list<std::shared_ptr<const ScatteringFunction>> &functions,
                       const std::shared_ptr<const ShapeSampler> &sampler,
                       const Point3<double> &origin,
                       const size_t n_samples,
                       std::complex<double> r_index = std::complex<double>(1, 0));
        ScatteringUnit(const Scene &scene,
                       const std::list<std::shared_ptr<const ScatteringFunction>> &functions,
                       const std::shared_ptr<const ShapeSampler> &sampler,
                       const Vector3<double> &direction,
                       const size_t n_samples,
                       std::complex<double> r_index = std::complex<double>(1, 0));

        const std::list<std::shared_ptr<const ScatteringFunction>> &getFunctions(void);

        std::complex<double> getRefractionIndex(void);

        void scatter(const SceneTracer &tracer);

        iterator begin(void);
        iterator end(void);
        const_iterator begin(void) const;
        const_iterator end(void) const;
        const_iterator cbegin(void) const;
        const_iterator cend(void) const;

    private:
        void main_scatter(const SceneTracer &tracer, const Ray3<double> &ray);
        void sample_point(const SceneTracer &tracer);
        void sample_direction(const SceneTracer &tracer);

    private:
        const Scene &scene;

        std::list<std::shared_ptr<TracingUnit>> targets;

        std::list<std::shared_ptr<const ScatteringFunction>> functions;

        std::shared_ptr<const ShapeSampler> sampler;
        std::shared_ptr<const Point3<double>> point;
        std::shared_ptr<const Vector3<double>> vector;
        size_t samples;

        std::complex<double> r_index;
};

DEF_EX(CommonScatteringUnitException, BaseException,
       "General scattering unit exception");

#endif

