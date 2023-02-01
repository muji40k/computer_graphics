#include "pinhole_projection.h"

PinholeProjection::PinholeProjection(const BaseDisplayAdapter &display,
                                     const Shape &shape, const double pin_offset)
{
    this->x = Vector3<double>({display.realWidth(), 0, 0});
    this->y = Vector3<double>({0, display.realHeight(), 0});
    this->pin = Point3<double>({0, 0, pin_offset});

    this->base_point = Point3<double>({display.offsetX(), display.offsetY(), 0});

    Transform<double, 3> res;

    for (const Shape *current = &shape;
         nullptr != current;
         current = current->getParent())
        res += current->getBasisTransform();

    this->base_point.apply(res);
    this->pin.apply(res);
    x.apply(res);
    y.apply(res);

    double width = this->x.length(), height = this->y.length();
    this->x /= width;
    this->y /= height;

    this->lim_x = display.width();
    this->lim_y = display.height();

    this->pixel_width = width / (display.width() - 1);
    this->pixel_height = height / (display.height() - 1);
}

PinholeProjection::~PinholeProjection(void) {}

Ray3<double> PinholeProjection::spawnRay(size_t i, size_t j) const
{
    if (i >= this->lim_x || j >= this->lim_y)
        throw CALL_EX(IndexViolationOProjectionException);

    Point3<double> spoint = this->base_point + this->pixel_width * i * x
                                             + (-this->pixel_height * j * y);
    Vector3<double> dir = (pin > spoint).normalised();

    return Ray3<double>(spoint, dir);
}

Ray3<double> PinholeProjection::sampleRay(size_t i, size_t j) const
{
    if (i >= this->lim_x || j >= this->lim_y)
        throw CALL_EX(IndexViolationOProjectionException);

    double offset_x = 1 - 2 * ((double) std::rand() / RAND_MAX);
    double offset_y = 1 - 2 * ((double) std::rand() / RAND_MAX);

    Point3<double> spoint = this->base_point + this->pixel_width * (offset_x + i) * x
                                             + (-this->pixel_height * (offset_y + j) * y);
    Vector3<double> dir = (pin > spoint).normalised();

    return Ray3<double>(spoint, dir);
}
