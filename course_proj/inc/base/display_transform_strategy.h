#ifndef _DISPLAY_TRANSFORM_STRATEGY_H_
#define _DISPLAY_TRANSFORM_STRATEGY_H_

#include "base_display_adapter.h"
#include "matrix.h"

class DisplayTransformStrategy
{
    public:
        virtual ~DisplayTransformStrategy(void) = 0;
        virtual void transform(const Matrix<Intensity<>> &hdr,
                               BaseDisplayAdapter &adapter) const = 0;
};

#endif

