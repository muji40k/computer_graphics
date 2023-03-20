#ifndef _LINEAR_DISPLAY_TRANSFORM_H_
#define _LINEAR_DISPLAY_TRANSFORM_H_

#include "display_transform_strategy.h"

class LinearDisplayTransform : public DisplayTransformStrategy
{
    public:
        virtual ~LinearDisplayTransform(void) override;
        virtual void transform(const Matrix<Intensity<>> &hdr,
                               BaseDisplayAdapter &adapter) const override;
};

#endif

