#include "measure.h"

#include <sys/time.h>

#include "empty_display_adapter.h"

#include "scene_active_projector.h"

#include "parallel_render_decorator.h"

Measurement::~Measurement(void) {}

PlainMeasurement::PlainMeasurement(size_t rep)
    : rep(rep) {}

PlainMeasurement::~PlainMeasurement(void) {}

std::list<Measurement::Stat> PlainMeasurement::measure(const preset_t &pres)
{
    EmptyDisplayAdapter adapter (pres.width, pres.height);

    double aspect = (double)pres.height / pres.width;
    adapter.setRealWidth(1);
    adapter.setOffset(-0.5, aspect * 0.5);

    struct timeval start, end;
    double sum = 0;

    for (size_t i = 0; this->rep > i; i++)
    {
        gettimeofday(&start, NULL);
        pres.renderer->render(*pres.scene, adapter);
        gettimeofday(&end, NULL);
        sum += (end.tv_sec - start.tv_sec) * 1e6 + end.tv_usec - start.tv_usec;
    }

    return {{pres.name, sum / (this->rep * 1e6), ""}};
}

ParallelMeasurements::~ParallelMeasurements(void) {}

ParallelMeasurements::ParallelMeasurements(size_t rep, size_t split_x,
                                           size_t split_y,
                                           std::initializer_list<size_t> lst_threads)
    : n_threads(lst_threads), rep(rep), split_x(split_x), split_y(split_y)
{}

std::list<Measurement::Stat> ParallelMeasurements::measure(const preset_t &pres)
{
    std::list<Stat> out;
    PlainMeasurement pmeasure (this->rep);
    preset_t inner = {pres.scene, nullptr, pres.info, pres.name, pres.width, pres.height};

    for (size_t thread : this->n_threads)
    {
        inner.renderer = \
            std::make_shared<ParallelRendererDecorator>(*pres.renderer,
                this->split_x, this->split_y, thread);

        for (Stat &stat : pmeasure.measure(inner))
        {
            stat.description = to_string(thread);
            out.push_back(stat);
        }
    }

    return out;
}

