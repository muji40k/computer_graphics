#include "thin_lens_projection.h"

#include "simple_scene_tracer.h"

#include <cmath>

ThinLensProjection::ThinLensProjection(const BaseDisplayAdapter &display,
                                       const Shape &shape, const double radius,
                                       const double focus)
{
    Transform<double, 3> res = this->getTransform(shape);
    this->init(display, res, radius, focus);
}

ThinLensProjection::ThinLensProjection(const BaseDisplayAdapter &display,
                                       const Shape &shape, const Scene &scene,
                                       const double radius)
{
    Transform<double, 3> res = this->getTransform(shape);

    double focus = 0;
    SimpleSceneTracer tracer;
    Point3<double> center;
    Vector3<double> vector ({0, 0, -1});
    center.apply(res);
    vector.apply(res);
    Ray3<double> ray (center, vector);

    Intersection inter = tracer.trace(scene, ray);

    if (inter)
    {
        Point3<double> tmp = inter.getPoint();
        tmp.apply(inter.toGlobal());
        Vector3<double> vtmp (center, tmp);
        vtmp.undo(res);
        focus = vtmp.length() / 2;
    }

    this->init(display, res, radius, focus);
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

void ThinLensProjection::init(const BaseDisplayAdapter &display,
                              const Transform<double> &trans,
                              const double radius,
                              const double focus)
{
    this->x = Vector3<double>({display.realWidth(), 0, 0});
    this->y = Vector3<double>({0, display.realHeight(), 0});
    this->center = Point3<double>();
    this->base = Point3<double>({-display.offsetX(), -display.offsetY(), 2 * focus});

    this->base.apply(trans);
    this->center.apply(trans);
    this->x.apply(trans);
    this->y.apply(trans);

    double width = this->x.length(), height = this->y.length();
    this->x /= width;
    this->y /= height;

    this->lim_x = display.width();
    this->lim_y = display.height();

    this->pixel_width = width / (display.width() - 1);
    this->pixel_height = height / (display.height() - 1);

    this->radius = radius;
}

Transform<double, 3> ThinLensProjection::getTransform(const Shape &shape)
{
    Transform<double, 3> res;

    for (const Shape *current = &shape;
         nullptr != current;
         current = current->getParent())
        res += current->getBasisTransform();

    return res;
}

