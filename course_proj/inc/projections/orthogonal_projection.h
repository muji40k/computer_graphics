#ifndef _ORTHOGONAL_PROJECTION_H_
#define _ORTHOGONAL_PROJECTION_H_

#include "base_exception.h"

#include "shape.h"
#include "projection.h"
#include "base_display_adapter.h"

#include "point.h"
#include "vector.h"

class OrthogonalProjection : public Projection
{
    public:
        OrthogonalProjection(const BaseDisplayAdapter &display,
                             const Shape &shape);
        virtual ~OrthogonalProjection(void) override;

        virtual Ray3<double> spawnRay(size_t i, size_t j) const override;
        virtual Ray3<double> sampleRay(size_t i, size_t j) const override;

    private:
        size_t lim_x;
        size_t lim_y;
        Vector3<double> direction;
        Point3<double> base_point;
        Vector3<double> x;
        Vector3<double> y;
        double pixel_width;
        double pixel_height;
};

class IndexViolationPProjectionException: public BaseException
{
    public:
        IndexViolationPProjectionException(void) = default;
        IndexViolationPProjectionException(const char *filename, const size_t line,
                                            const char *function,
                                            const char *message = "Index out of projection range")
            : BaseException(filename, line, function, message) {};
        ~IndexViolationPProjectionException(void) = default;
};

#endif

