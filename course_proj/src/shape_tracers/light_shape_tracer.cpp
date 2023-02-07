#include "light_shape_tracer.h"

#include <list>

typedef struct
{
    const Shape *shape;
    Ray3<double> ray;
} tracing_unit_t;

LightShapeTracer::LightShapeTracer() {}
LightShapeTracer::~LightShapeTracer() {}

Intersection LightShapeTracer::trace(const Shape &shape, const Ray3<double> ray)
{
    Intersection out = Intersection(), cout;
    std::list<tracing_unit_t> queue = {{&shape, ray}};
    tracing_unit_t &cunit = queue.front();
    Ray3<double> tmp;

    while (0 != queue.size() && !out)
    {
        cunit = queue.front();

        if (cunit.shape->intersectBounding(cunit.ray))
        {
            cout = cunit.shape->intersect(cunit.ray);

            if (cout && 1 - FLT_EPSILON > cout.getT() && FLT_EPSILON < cout.getT())
                out = cout;
        }

        tmp = cunit.ray;
        tmp.undo(cunit.shape->getBasisTransform());

        for (Shape *shape : *cunit.shape)
            queue.push_back({shape, tmp});

        queue.pop_front();
    }

    if (out)
        out = Intersection(out.getShape(), out.getPoint(), out.getNormal(),
                           out.getT(), Transform<double, 3>());

    return out;
}

