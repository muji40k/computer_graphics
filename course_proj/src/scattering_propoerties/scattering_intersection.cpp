#include "scattering_intersection.h"

const Attribute &ScatteringIntersection::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringProperty::ATTRIBUTE() \
                            | Attribute(ScatteringIntersection::MAXATTR,
                                        {ScatteringIntersection::ATTRI});
    return attr;
}

ScatteringIntersection::ScatteringIntersection(const Intersection &inter)
    : intersection(std::make_shared<Intersection>(inter)) {}

ScatteringIntersection::~ScatteringIntersection(void) {}

const Intersection &ScatteringIntersection::getIntersection(void)
{
    return *this->intersection;
}

const Attribute &ScatteringIntersection::getAttribute(void) const
{
    return ScatteringIntersection::ATTRIBUTE();
}

