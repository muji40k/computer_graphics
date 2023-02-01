#include "bounding_sphere.h"
#include "vector.h"

BoundingSphere::BoundingSphere(const Point3<double> &start)
    : center(start), radius(0) {}

BoundingSphere::BoundingSphere(const BoundingSphere &bounding)
    : center(bounding.center), radius(bounding.radius) {}

BoundingSphere::BoundingSphere(BoundingSphere &&bounding)
    : center(bounding.center), radius(bounding.radius) {}

BoundingSphere::~BoundingSphere(void) {}

void BoundingSphere::expand(const Point3<double> &point)
{
    if (this->isInside(point))
        return;

    Vector3<double> expand_direction = this->center > point;
    double new_radius = (expand_direction.length() + this->radius) / 2;
    expand_direction = expand_direction.normalised() * (new_radius - this->radius);
    this->center = this->center + expand_direction;
    this->radius = new_radius;
    this->radiussqr = this->radius * this->radius;
}

void BoundingSphere::expand(const std::list<Point3<double>> &points)
{
    for (const Point3<double> &point : points)
        this->expand(point);
}

bool BoundingSphere::isInside(const Point3<double> &point) const
{
    return this->radius > distance(point, this->center);
}

bool BoundingSphere::intersect(const Ray3<double> &ray) const
{
    Vector3<double> vtmp = this->center > ray.getOrigin();
    double origin_center = vtmp.length();
    double origin_center_ray = vtmp & ray.getDirection();
    double ray_length = ray.getDirection().length();
    double ray_length_sqr = ray_length * ray_length;

    double discriminant = origin_center_ray * origin_center_ray \
                          - ray_length_sqr \
                            * (origin_center * origin_center - this->radiussqr);

    if (-FLT_EPSILON > discriminant)
        return false;

    return true;
}

void BoundingSphere::apply(const Transform<double, 3> &transform)
{
    this->center.apply(transform);

    double current = 0, l;
    Vector3<double> cv;

    for (size_t i = 0; 3 > i; i++)
    {
        cv[(i - 1) % 3] = 0;
        cv[i] = this->radius;

        cv.apply(transform);
        l = cv.length();

        if (l > current)
            current = l;
    }

    this->radius = current;
    this->radiussqr = this->radius * this->radius;
}

void BoundingSphere::undo(const Transform<double, 3> &transform)
{
    this->center.undo(transform);

    double current = 0, l;
    Vector3<double> cv;

    for (size_t i = 0; 3 > i; i++)
    {
        cv[(i - 1) % 3] = 0;
        cv[i] = this->radius;

        cv.undo(transform);
        l = cv.length();

        if (l > current)
            current = l;
    }

    this->radius = current;
    this->radiussqr = this->radius * this->radius;
}

