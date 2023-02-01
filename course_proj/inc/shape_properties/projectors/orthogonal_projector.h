#ifndef _ORTHOGONAL_PROJECTOR_H_
#define _ORTHOGONAL_PROJECTOR_H_

#include "projector.h"

class OrthogonalProjector : public Projector
{
    public:
        static const size_t ATTRI = 10;
        static const Attribute &ATTRIBUTE(void);

    public:
        OrthogonalProjector(Shape *target);
        virtual ~OrthogonalProjector(void) override;

        virtual std::shared_ptr<Projection> project(const BaseDisplayAdapter &display) const override;

        virtual const Attribute &getAttribute(void) const override;
};

#endif

