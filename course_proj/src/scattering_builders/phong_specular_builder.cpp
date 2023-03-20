#include "phong_specular_builder.h"

#include "phong_specular_function.h"
#include "scattering_scale.h"
#include "scattering_intersection.h"
#include "scattering_phong_alpha.h"

const Attribute &PhongSpecularBuilder::ATTRIBUTE(void)
{
    static Attribute attr = DifusionBuilder::ATTRIBUTE() \
                            | Attribute(PhongSpecularBuilder::MAXATTR,
                                        {PhongSpecularBuilder::ATTRI});
    return attr;
}

PhongSpecularBuilder::~PhongSpecularBuilder(void) {}

const Attribute &PhongSpecularBuilder::getAttribute(void) const
{
    return PhongSpecularBuilder::ATTRIBUTE();
}

std::shared_ptr<ScatteringFunction> PhongSpecularBuilder::build(const ScatteringInfo &info) const
{
    std::shared_ptr<ScatteringScale> scale = \
        std::static_pointer_cast<ScatteringScale>(info.getProperty(ScatteringScale::ATTRIBUTE()));
    std::shared_ptr<ScatteringIntersection> intersection = \
        std::static_pointer_cast<ScatteringIntersection>(info.getProperty(ScatteringIntersection::ATTRIBUTE()));
    std::shared_ptr<ScatteringPhongAlpha> alpha = \
        std::static_pointer_cast<ScatteringPhongAlpha>(info.getProperty(ScatteringPhongAlpha::ATTRIBUTE()));

    if (nullptr == scale)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringScale));

    if (nullptr == intersection)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringIntersection));

    if (nullptr == alpha)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringPhongAlpha));

    return std::make_shared<PhongSpecularFunction>(scale->getScale(),
                                                   intersection->getIntersection(),
                                                   alpha->getAlpha());
}

