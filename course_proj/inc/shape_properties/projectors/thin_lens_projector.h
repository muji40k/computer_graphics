#ifndef _THIN_LENS_PROJECTOR_H_
#define _THIN_LENS_PROJECTOR_H_

#include "base_exception.h"

#include "projector.h"
#include "scene.h"

class ThinLensProjector : public Projector
{
    public:
        static const size_t ATTRI = 12;
        static const Attribute &ATTRIBUTE(void);

    public:
        ThinLensProjector(Shape *target, const Scene &scene,
                          const double focus, const double aperture,
                          const bool autofocus=false);
        virtual ~ThinLensProjector(void) override;

        double getFocusDistance(void);
        void setFocusDistance(const double focus);

        double getAperture(void);
        void setAperture(const double aperture);

        void setAutofocus(const bool state);

        virtual std::shared_ptr<Projection> project(const BaseDisplayAdapter &display) const override;

        virtual const Attribute &getAttribute(void) const override;

    private:
        const Scene &scene;
        bool autofocus;
        double f;
        double a;
};

DEF_EX(CommonThinLensProjectorException, CommonProjectorException,
       "General thin-lens projector exception");
DEF_EX(NegativeFocusLProjectionException, CommonThinLensProjectorException,
       "Given focus distance for thin lens is negative");
DEF_EX(NegativeApertureLProjectionException, CommonThinLensProjectorException,
       "Given aperture for thin lens is negative");

#endif

