#ifndef _THIN_LENS_PROJECTOR_H_
#define _THIN_LENS_PROJECTOR_H_

#include "base_exception.h"

#include "projector.h"

class ThinLensProjector : public Projector
{
    public:
        static const size_t ATTRI = 12;
        static const Attribute &ATTRIBUTE(void);

    public:
        ThinLensProjector(Shape *target, const double focus, const double aperture);
        virtual ~ThinLensProjector(void) override;

        double getFocusDistance(void);
        void setFocusDistance(const double focus);

        double getAperture(void);
        void setAperture(const double aperture);

        virtual std::shared_ptr<Projection> project(const BaseDisplayAdapter &display) const override;

        virtual const Attribute &getAttribute(void) const override;

    private:
        double f;
        double a;
};

class NegativeFocusLProjectionException: public BaseException
{
    public:
        NegativeFocusLProjectionException(void) = default;
        NegativeFocusLProjectionException(const char *filename, const size_t line,
                                            const char *function,
                                            const char *message = "Given focus distance for thin lens is negative")
            : BaseException(filename, line, function, message) {};
        ~NegativeFocusLProjectionException(void) = default;
};

class NegativeApertureLProjectionException: public BaseException
{
    public:
        NegativeApertureLProjectionException(void) = default;
        NegativeApertureLProjectionException(const char *filename, const size_t line,
                                            const char *function,
                                            const char *message = "Given aperture for thin lens is negative")
            : BaseException(filename, line, function, message) {};
        ~NegativeApertureLProjectionException(void) = default;
};

#endif

