#include "thin_lens_projection.h"

#include <cmath>

ThinLensProjection::ThinLensProjection(const BaseDisplayAdapter &display,
                                       const Shape &shape, const double radius,
                                       const double focus)
{
    this->x = Vector3<double>({display.realWidth(), 0, 0});
    this->y = Vector3<double>({0, display.realHeight(), 0});
    this->center = Point3<double>();
    this->base = Point3<double>({-display.offsetX(), -display.offsetY(), 2 * focus});

    Transform<double, 3> res;

    for (const Shape *current = &shape;
         nullptr != current;
         current = current->getParent())
        res += current->getBasisTransform();

    this->base.apply(res);
    this->center.apply(res);
    this->x.apply(res);
    this->y.apply(res);

    double width = this->x.length(), height = this->y.length();
    this->x /= width;
    this->y /= height;

    this->lim_x = display.width();
    this->lim_y = display.height();

    this->pixel_width = width / (display.width() - 1);
    this->pixel_height = height / (display.height() - 1);

    this->radius = radius;
}

ThinLensProjection::~ThinLensProjection(void) {}

Ray3<double> ThinLensProjection::spawnRay(size_t i, size_t j) const
{
    if (i >= this->lim_x || j >= this->lim_y)
        throw CALL_EX(IndexViolationLProjectionException);

    Point3<double> spoint = this->base + (-this->pixel_width * i * x) \
                                       + this->pixel_height * j * y;

    return Ray3<double>(this->center, (spoint > this->center).normalised());
}

Ray3<double> ThinLensProjection::sampleRay(size_t i, size_t j) const
{
    if (i >= this->lim_x || j >= this->lim_y)
        throw CALL_EX(IndexViolationLProjectionException);

    double r = this->radius * ((double) std::rand() / RAND_MAX),
           a = 2 * M_PI * ((double) std::rand() / RAND_MAX);

    Point3<double> spoint = this->base + (-this->pixel_width * i * x) \
                                       + this->pixel_height * j * y;

    Point3<double> lpoint = this->center + this->x * r * cos(a) \
                                         + this->y * r * sin(a);

    return Ray3<double>(lpoint,
                        (lpoint > (this->center + ((spoint > lpoint) / 2))).normalised());
}

