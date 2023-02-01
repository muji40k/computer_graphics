#ifndef _PINHOLE_PROJECTOR_H_
#define _PINHOLE_PROJECTOR_H_

#include "base_exception.h"

#include "projector.h"

class PinholeProjector : public Projector
{
    public:
        static const size_t ATTRI = 11;
        static const Attribute &ATTRIBUTE(void);

    public:
        PinholeProjector(Shape *target, const double pin_offset);
        virtual ~PinholeProjector(void) override;

        double getPinOffset(void);
        void setPinOffset(const double offset);

        virtual std::shared_ptr<Projection> project(const BaseDisplayAdapter &display) const override;

        virtual const Attribute &getAttribute(void) const override;

    private:
        double f;
};

class NegativeOffsetPProjectionException: public BaseException
{
    public:
        NegativeOffsetPProjectionException(void) = default;
        NegativeOffsetPProjectionException(const char *filename, const size_t line,
                                            const char *function,
                                            const char *message = "Given offset for pinhole is negative")
            : BaseException(filename, line, function, message) {};
        ~NegativeOffsetPProjectionException(void) = default;
};

#endif
