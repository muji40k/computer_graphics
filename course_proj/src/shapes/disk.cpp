#include <float.h>
#include "disk.h"
#include "vector.h"

#include "bounding_sphere.h"

#include "disk_sampler.h"

#include "tools.h"

const Attribute &Disk::ATTRIBUTE(void)
{
    static const Attribute attr = ObjectPrimitive::ATTRIBUTE() \
                                  | Attribute(Disk::MAXATTR, {Disk::ATTRI});
    return attr;
}

Disk::~Disk(void) {}

Disk::Disk(double radius, bool flip_normal)
{
    if (0 > radius)
        throw CALL_EX(NegativeRadiusDiskException);

    this->radius = radius;
    this->rsqr = radius * radius;
    this->flip = flip_normal;

    this->bounding = std::make_shared<BoundingSphere>(Point3<double>());
    this->bounding->expand(Point3<double>() + Vector3<double>({radius, 0, 0}));
    this->bounding->expand(Point3<double>() + Vector3<double>({-radius, 0, 0}));
    this->transform_local = std::make_shared<Transform<double, 3>>();

    this->sampler = std::make_shared<DiskSampler>(radius);
}

bool Disk::intersectBounding(const Ray3<double> &ray) const
{
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);

    return this->bounding->intersect(tmp);
}

const Attribute &Disk::getAttribute(void) const
{
    return Disk::ATTRIBUTE();
}

Intersection Disk::intersect(const Ray3<double> &ray) const
{
    Intersection out = Intersection();

    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);

    Point3<double> center;
    Normal3<double> normal {0, 1, 0};

    if (this->flip)
        normal.y = -1;

    tools::intersection_res_t res = tools::intersect_plane(center, normal, tmp);

    if (!res.valid || FLT_EPSILON > res.t)
        return out;

    Point3<double> point = tmp(res.t);
    Vector3<double> k (center > point);
    double distance = k.length();

    if (this->radius > distance)
    {
        double idistance = (double)1 / distance;

        double cosx = k.z * idistance;
        double cosy = k.x * idistance;

        double u = ((cosy > -FLT_EPSILON) ? acos(cosx) : 2 * M_PI - acos(cosx)) \
                   / (2 * M_PI);
        double v = distance / this->radius;

        out = Intersection(this, point, Point2<double>(u, v),
                           Normal3<double>(normal), res.t,
                           *this->transform_local + *this->transform_global);
    }

    return out;
}

double Disk::area(void) const
{
    return M_PI * this->rsqr;
}

const ShapeSampler &Disk::getSampler(void) const
{
    return *this->sampler;
}

void Disk::apply(const Transform<double, 3> &transform)
{
    *(this->transform_local) += transform;
    this->sampler->apply(transform);
}

void Disk::undo(const Transform<double, 3> &transform)
{
    *(this->transform_local) += transform.inversed();
    this->sampler->undo(transform);
}

