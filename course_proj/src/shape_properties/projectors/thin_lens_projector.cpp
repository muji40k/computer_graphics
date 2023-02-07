#include "thin_lens_projector.h"
#include "thin_lens_projection.h"

ThinLensProjector::ThinLensProjector(Shape *target, const double focus,
                                     const double aperture)
    : Projector(target)
{
    if (0 > focus)
        throw CALL_EX(NegativeFocusLProjectionException);

    if (0 > aperture)
        throw CALL_EX(NegativeApertureLProjectionException);

    this->f = focus;
    this->a = aperture;
}

ThinLensProjector::~ThinLensProjector(void) {}

std::shared_ptr<Projection> ThinLensProjector::project(const BaseDisplayAdapter &display) const
{
    return std::shared_ptr<Projection>(new ThinLensProjection(display,
                                                              this->getTarget(),
                                                              this->a,
                                                              this->f));
}

double ThinLensProjector::getFocusDistance(void)
{
    return this->f;
}

void ThinLensProjector::setFocusDistance(const double focus)
{
    if (0 > focus)
        throw CALL_EX(NegativeFocusLProjectionException);

    this->f = focus;
}

double ThinLensProjector::getAperture(void)
{
    return this->a;
}

void ThinLensProjector::setAperture(const double aperture)
{
    if (0 > aperture)
        throw CALL_EX(NegativeApertureLProjectionException);

    this->a = aperture;
}

const Attribute &ThinLensProjector::ATTRIBUTE(void)
{
    static const Attribute attr = Projector::ATTRIBUTE() \
                                  | Attribute(ThinLensProjector::MAXATTR,
                                              {ThinLensProjector::ATTRI});
    return attr;
}

const Attribute &ThinLensProjector::getAttribute(void) const
{
    return ThinLensProjector::ATTRIBUTE();
}

