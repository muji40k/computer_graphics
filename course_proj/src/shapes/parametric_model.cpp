#include "parametric_model.h"

const Attribute &ParametricModel::ATTRIBUTE(void)
{
    static const Attribute attr = Object::ATTRIBUTE() \
                                  | Attribute(ParametricModel::MAXATTR,
                                              {ParametricModel::ATTRI});
    return attr;
}

ParametricModel::~ParametricModel(void) {}

const Attribute &ParametricModel::getAttribute(void) const
{
    return ParametricModel::ATTRIBUTE();
}

