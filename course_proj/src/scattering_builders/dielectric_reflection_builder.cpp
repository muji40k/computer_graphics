#include "dielectric_reflection_builder.h"

#include "dielectric_reflection_function.h"

#include "scattering_scale.h"
#include "scattering_intersection.h"
#include "scattering_refraction_index_in.h"
#include "scattering_refraction_index_out.h"

const Attribute &DielectricReflectionBuilder::ATTRIBUTE(void)
{
    static Attribute attr = FresnelReflectionBuilder::ATTRIBUTE() \
                            | Attribute(DielectricReflectionBuilder::MAXATTR,
                                        {DielectricReflectionBuilder::ATTRI});
    return attr;
}

DielectricReflectionBuilder::~DielectricReflectionBuilder(void) {}

const Attribute &DielectricReflectionBuilder::getAttribute(void) const
{
    return DielectricReflectionBuilder::ATTRIBUTE();
}

std::shared_ptr<ScatteringFunction> DielectricReflectionBuilder::build(const ScatteringInfo &info) const
{
    std::shared_ptr<ScatteringScale> scale = \
        std::static_pointer_cast<ScatteringScale>(info.getProperty(ScatteringScale::ATTRIBUTE()));
    std::shared_ptr<ScatteringIntersection> inter = \
        std::static_pointer_cast<ScatteringIntersection>(info.getProperty(ScatteringIntersection::ATTRIBUTE()));
    std::shared_ptr<ScatteringRefractionIndexIn> n1 = \
        std::static_pointer_cast<ScatteringRefractionIndexIn>(info.getProperty(ScatteringRefractionIndexIn::ATTRIBUTE()));
    std::shared_ptr<ScatteringRefractionIndexOut> n2 = \
        std::static_pointer_cast<ScatteringRefractionIndexOut>(info.getProperty(ScatteringRefractionIndexOut::ATTRIBUTE()));


    if (nullptr == scale)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringScale));

    if (nullptr == inter)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringIntersection));

    if (nullptr == n1)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringRefractionIndexIn));

    if (nullptr == n2)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringRefractionIndexOut));

    return std::make_shared<DielectricReflectionFunction>(scale->getScale(),
                                                          inter->getIntersection(),
                                                          n1->getRefractionIndex(),
                                                          n2->getRefractionIndex());
}

