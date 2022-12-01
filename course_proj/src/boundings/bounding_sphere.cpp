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
    Vector3<double> expand_direction = this->center > point;
    double new_radius = (expand_direction.length() + radius) / 2;
    expand_direction = expand_direction.normalised() * (new_radius - radius);
    this->center = this->center + expand_direction;
    this->radius = new_radius;
}

void BoundingSphere::expand(const std::list<Point3<double>> &points)
{
    for (const Point3<double> &point : points)
    {
        if (this->isInside(point))
            return;

        Vector3<double> expand_direction = this->center > point;
        double new_radius = (expand_direction.length() + radius) / 2;
        expand_direction = expand_direction.normalised() * (new_radius - radius);
        this->center = this->center + expand_direction;
        this->radius = new_radius;
    }
}

std::list<Point3<double>> BoundingSphere::farest(const Point3<double> &point) const
{
    return std::list({this->center + (point > this->center).normalised() * this->radius});
}

std::list<Point3<double>> BoundingSphere::nearest(const Point3<double> &point) const
{
    return std::list({this->center + (this->center > point).normalised() * this->radius});
}

bool BoundingSphere::isInside(const Point3<double> &point) const
{
    return this->radius > distance(point, this->center);
}

bool BoundingSphere::intersect(const Ray3<double> &ray) const
{
    Vector3<double> d = this->center > ray.getOrigin();

    double discriminant = (pow((d & ray.getDirection()), 2)
                           - (d.lengthSqr()
                              - pow(this->radius, 2)) 
                             * ray.getDirection().lengthSqr()) * 4;

    if (0 > discriminant)
        return false;

    return true;
}

