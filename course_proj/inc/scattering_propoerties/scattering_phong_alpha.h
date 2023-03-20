#ifndef _SCATTERING_PHONG_ALPHA_H_
#define _SCATTERING_PHONG_ALPHA_H_

#include "scattering_property.h"

class ScatteringPhongAlpha : public ScatteringProperty
{
    public:
        static const size_t ATTRI = 6;
        static const Attribute &ATTRIBUTE(void);

    public:
        ScatteringPhongAlpha(double alpha);
        virtual ~ScatteringPhongAlpha(void) override;
        const double &getAlpha(void);
        virtual const Attribute &getAttribute(void) const override;

    private:
        double alpha;

};

#endif

