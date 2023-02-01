#ifndef _PROJECTOR_H_
#define _PROJECTOR_H_

#include <memory>

#include "shape_property.h"
#include "projection.h"
#include "base_display_adapter.h"

class Projector : public ShapeProperty
{
    public:
        static const size_t ATTRI = 1;
        static const Attribute &ATTRIBUTE(void);

    public:
        Projector(Shape *target);
        virtual ~Projector(void) = 0;
        virtual std::shared_ptr<Projection> project(const BaseDisplayAdapter &display) const = 0;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

