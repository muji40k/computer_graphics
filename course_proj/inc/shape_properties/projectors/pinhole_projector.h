#ifndef _PINHOLE_PROJECTOR_H_
#define _PINHOLE_PROJECTOR_H_

#include "base_exception.h"

#include "projector.h"

class PinholeProjector : public Projector
{
    public:
        static const size_t ATTRI = 11;
        static const Attribute &ATTRIBUTE(void);

    public:
        PinholeProjector(Shape *target, const double pin_offset);
        virtual ~PinholeProjector(void) override;

        double getPinOffset(void);
        void setPinOffset(const double offset);

        virtual std::shared_ptr<Projection> project(const BaseDisplayAdapter &display) const override;

        virtual const Attribute &getAttribute(void) const override;

    private:
        double f;
};

DEF_EX(CommonPProjectorException, CommonProjectorException,
       "General pinhole projector exception");
DEF_EX(NegativeOffsetPProjectorException, CommonPProjectorException,
       "Given offset for pinhole is negative");

#endif
