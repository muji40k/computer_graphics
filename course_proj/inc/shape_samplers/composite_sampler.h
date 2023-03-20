#ifndef _COMPOSITE_SAMPLER_H_
#define _COMPOSITE_SAMPLER_H_

#include <list>
#include <memory>

#include "base_exception.h"

#include "shape_sampler.h"

#include "transform.h"

class CompositeSampler : public ShapeSampler
{
    public:
        CompositeSampler(void);
        virtual ~CompositeSampler(void) override;
        virtual bool isSamplabel(void) const override;
        virtual Point3<double> get(void) const override;
        virtual void append(const ShapeSampler *sampler) override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        std::shared_ptr<Transform<double, 3>> transform;
        std::list<const ShapeSampler *> samplers;
};


#endif

