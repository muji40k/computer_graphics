#ifndef _GAMMA_DISPLAY_TRANSFORM_H_
#define _GAMMA_DISPLAY_TRANSFORM_H_

#include "display_transform_strategy.h"

class GammaDisplayTransform : public DisplayTransformStrategy
{
    public:
        GammaDisplayTransform(double gamma);
        virtual ~GammaDisplayTransform(void) override;
        virtual void transform(const Matrix<Intensity<>> &hdr,
                               BaseDisplayAdapter &adapter) const override;

    private:
        double igamma;
};

#endif

