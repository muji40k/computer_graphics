#include "conductor_reflection_builder.h"

#include "conductor_reflection_function.h"

#include "scattering_scale.h"
#include "scattering_intersection.h"
#include "scattering_refraction_index_in.h"
#include "scattering_refraction_index_out.h"

const Attribute &ConductorReflectionBuilder::ATTRIBUTE(void)
{
    static Attribute attr = FresnelReflectionBuilder::ATTRIBUTE() \
                            | Attribute(ConductorReflectionBuilder::MAXATTR,
                                        {ConductorReflectionBuilder::ATTRI});
    return attr;
}

ConductorReflectionBuilder::~ConductorReflectionBuilder(void) {}

const Attribute &ConductorReflectionBuilder::getAttribute(void) const
{
    return ConductorReflectionBuilder::ATTRIBUTE();
}

std::shared_ptr<ScatteringFunction> ConductorReflectionBuilder::build(const ScatteringInfo &info) const
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

    return std::make_shared<ConductorReflectionFunction>(scale->getScale(),
                                                         inter->getIntersection(),
                                                         n1->getRefractionIndex(),
                                                         n2->getRefractionIndex());
}

