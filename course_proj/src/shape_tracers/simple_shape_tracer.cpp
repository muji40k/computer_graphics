#include "simple_shape_tracer.h"

#include <list>

typedef struct
{
    const Shape *shape;
    Ray3<double> ray;
} tracing_unit_t;

SimpleShapeTracer::~SimpleShapeTracer() {}

Intersection SimpleShapeTracer::trace(const Shape &shape, const Ray3<double> ray) const
{
    Intersection out = Intersection(), cout;
    std::list<tracing_unit_t> queue = {{&shape, ray}};
    tracing_unit_t &cunit = queue.front();
    Ray3<double> tmp;

    while (0 != queue.size())
    {
        cunit = queue.front();

        if (cunit.shape->intersectBounding(cunit.ray))
        {
            cout = cunit.shape->intersect(cunit.ray);

            if (cout && (!out || cout.getT() < out.getT()))
                out = cout;
        }

        tmp = cunit.ray;
        tmp.undo(cunit.shape->getBasisTransform());

        for (Shape *shape : *cunit.shape)
            queue.push_back({shape, tmp});

        queue.pop_front();
    }

    if (out)
        for (const Shape *current = out.getShape()->getParent();
             nullptr != current;
             current = current->getParent())
            out.apply(current->getBasisTransform());

    return out;
}

