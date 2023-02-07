#ifndef _THIN_LENS_PROJECTION_H_
#define _THIN_LENS_PROJECTION_H_

#include "base_exception.h"

#include "shape.h"
#include "projection.h"
#include "base_display_adapter.h"

#include "point.h"
#include "vector.h"

class ThinLensProjection : public Projection
{
    public:
        ThinLensProjection(const BaseDisplayAdapter &display,
                           const Shape &shape, const double radius,
                           const double focus);
        virtual ~ThinLensProjection(void) override;

        virtual Ray3<double> spawnRay(size_t i, size_t j) const override;
        virtual Ray3<double> sampleRay(size_t i, size_t j) const override;

    private:
        size_t lim_x;
        size_t lim_y;

        Point3<double> center;
        Point3<double> base;

        Vector3<double> x;
        Vector3<double> y;
        double pixel_width;
        double pixel_height;

        double radius;
};

class IndexViolationLProjectionException: public BaseException
{
    public:
        IndexViolationLProjectionException(void) = default;
        IndexViolationLProjectionException(const char *filename, const size_t line,
                                            const char *function,
                                            const char *message = "Index out of projection range")
            : BaseException(filename, line, function, message) {};
        ~IndexViolationLProjectionException(void) = default;
};

#endif

