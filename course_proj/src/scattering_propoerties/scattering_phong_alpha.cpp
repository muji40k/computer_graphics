#include "scattering_phong_alpha.h"

const Attribute &ScatteringPhongAlpha::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringProperty::ATTRIBUTE() \
                            | Attribute(ScatteringPhongAlpha::MAXATTR,
                                        {ScatteringPhongAlpha::ATTRI});
    return attr;
}

ScatteringPhongAlpha::ScatteringPhongAlpha(double alpha)
    : alpha(alpha) {}

ScatteringPhongAlpha::~ScatteringPhongAlpha(void) {}

const double &ScatteringPhongAlpha::getAlpha(void)
{
    return this->alpha;
}

const Attribute &ScatteringPhongAlpha::getAttribute(void) const
{
    return ScatteringPhongAlpha::ATTRIBUTE();
}

