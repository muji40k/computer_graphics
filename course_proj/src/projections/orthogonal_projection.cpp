#include "orthogonal_projection.h"

OrthogonalProjection::OrthogonalProjection(const BaseDisplayAdapter &display,
                                           const Shape &shape)
{
    this->direction = Vector3<double>({0, 0, -1});
    this->x = Vector3<double>({display.realWidth(), 0, 0});
    this->y = Vector3<double>({0, display.realHeight(), 0});

    this->base_point = Point3<double>({display.offsetX(), display.offsetY(), 0});

    Transform<double, 3> res;

    for (const Shape *current = &shape;
         nullptr != current;
         current = current->getParent())
        res += current->getBasisTransform();

    this->base_point.apply(res);
    this->direction.apply(res);
    x.apply(res);
    y.apply(res);

    double width = this->x.length(), height = this->y.length();
    this->x /= width;
    this->y /= height;
    this->direction.normalise();

    this->lim_x = display.width();
    this->lim_y = display.height();

    this->pixel_width = width / (display.width() - 1);
    this->pixel_height = height / (display.height() - 1);
}

OrthogonalProjection::~OrthogonalProjection(void) {}

Ray3<double> OrthogonalProjection::spawnRay(size_t i, size_t j) const
{
    if (i >= this->lim_x || j >= this->lim_y)
        throw CALL_EX(IndexViolationPProjectionException);

    return Ray3<double>(this->base_point + this->pixel_width * i * x
                                         + (-this->pixel_height * j * y),
                        this->direction);
}

Ray3<double> OrthogonalProjection::sampleRay(size_t i, size_t j) const
{
    if (i >= this->lim_x || j >= this->lim_y)
        throw CALL_EX(IndexViolationPProjectionException);

    double offset_x = 1 - 2 * ((double) std::rand() / RAND_MAX);
    double offset_y = 1 - 2 * ((double) std::rand() / RAND_MAX);

    return Ray3<double>(this->base_point + this->pixel_width * (offset_x + i) * x
                                         + (-this->pixel_height * (offset_y + j) * y),
                        this->direction);
}

