#ifndef _PINHOLE_PROJECTION_H_
#define _PINHOLE_PROJECTION_H_

#include "base_exception.h"

#include "shape.h"
#include "projection.h"
#include "base_display_adapter.h"

#include "point.h"
#include "vector.h"

class PinholeProjection : public Projection
{
    public:
        PinholeProjection(const BaseDisplayAdapter &display,
                          const Shape &shape, const double pin_offset);
        virtual ~PinholeProjection(void) override;

        virtual Ray3<double> spawnRay(size_t i, size_t j) const override;
        virtual Ray3<double> sampleRay(size_t i, size_t j) const override;

    private:
        size_t lim_x;
        size_t lim_y;
        Vector3<double> x;
        Vector3<double> y;
        double pixel_width;
        double pixel_height;
        Point3<double> base_point;
        Point3<double> pin;
};

class IndexViolationOProjectionException: public BaseException
{
    public:
        IndexViolationOProjectionException(void) = default;
        IndexViolationOProjectionException(const char *filename, const size_t line,
                                            const char *function,
                                            const char *message = "Index out of projection range")
            : BaseException(filename, line, function, message) {};
        ~IndexViolationOProjectionException(void) = default;
};

#endif
