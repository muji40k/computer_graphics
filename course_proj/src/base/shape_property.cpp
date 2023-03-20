#include "shape_property.h"

const Attribute &ShapeProperty::ATTRIBUTE(void)
{
    static const Attribute attr = Attribute(ShapeProperty::MAXATTR,
                                            {ShapeProperty::ATTRI});
    return attr;
}

ShapeProperty::ShapeProperty(Shape *target)
{
    this->target = target;
}

ShapeProperty::~ShapeProperty(void) {}

Shape &ShapeProperty::getTarget(void)
{
    return *this->target;
}

const Shape &ShapeProperty::getTarget(void) const
{
    return *this->target;
}

const Attribute &ShapeProperty::getAttribute(void) const
{
    return ShapeProperty::ATTRIBUTE();
}

