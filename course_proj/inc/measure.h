#ifndef _MEASURE_H_
#define _MEASURE_H_

#include <stdlib.h>
#include <memory>
#include <string>
#include <list>
#include <initializer_list>

#include "scene.h"
#include "renderer.h"

#include "display_transform_strategy.h"

typedef struct _preset_t
{
    std::shared_ptr<Scene> scene = nullptr;
    std::shared_ptr<Renderer> renderer = nullptr;
    std::string info;
    std::string name;
    size_t width;
    size_t height;
} preset_t;

class Measurement
{
    public:
        using Stat = struct
        {
            std::string name;
            double time;
            std::string description;
        };

        virtual ~Measurement(void) = 0;
        virtual std::list<Stat> measure(const preset_t &pres) = 0;
};

class PlainMeasurement : public Measurement
{
    public:
        PlainMeasurement(size_t rep);
        virtual ~PlainMeasurement(void) override;
        virtual std::list<Stat> measure(const preset_t &pres) override;

    private:
        size_t rep;
};

class ParallelMeasurements : public Measurement
{
    public:
        ParallelMeasurements(size_t rep, size_t split_x,
                             size_t split_y,
                             std::initializer_list<size_t> lst_threads);
        virtual ~ParallelMeasurements(void) override;
        virtual std::list<Stat> measure(const preset_t &pres) override;

    private:
        std::list<size_t> n_threads;
        size_t rep;
        size_t split_x;
        size_t split_y;
};

#endif

