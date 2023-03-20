#include "plane.h"

#include "bounding_sphere.h"
#include "plane_sampler.h"

#include "tools.h"

const Attribute &Plane::ATTRIBUTE(void)
{
    static const Attribute attr = ObjectPrimitive::ATTRIBUTE() \
                                  | Attribute(Plane::MAXATTR,
                                              {Plane::ATTRI});
    return attr;
}

Plane::~Plane(void) {}

Plane::Plane(double lx, double lz, bool flip_normal)
{
    if (0 > lx || 0 > lz)
        throw CALL_EX(DegeneratePlaneException);

    Vector3<double> x ({1, 0, 0});
    Vector3<double> z ({0, 0, 1});
    Point3<double> center;

    this->lx = lx / 2;
    this->lz = lz / 2;
    this->flip = flip_normal;

    this->transform_local = std::make_shared<Transform<double, 3>>();

    this->bounding = std::make_shared<BoundingSphere>(center);
    this->bounding->expand(center + (x * lx + z * lz) / 2);
    this->bounding->expand(center + (x * lx + (-z * lz)) / 2);
    this->bounding->expand(center + ((-x * lx) + z * lz) / 2);
    this->bounding->expand(center + ((-x * lx) + (-z * lz)) / 2);

    this->sampler = std::make_shared<PlaneSampler>(lx, lz);
}

bool Plane::intersectBounding(const Ray3<double> &ray) const
{
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);

    return this->bounding->intersect(tmp);
}

double Plane::area(void) const
{
    return this->space;
}

const ShapeSampler &Plane::getSampler(void) const
{
    return *this->sampler;
}

const Attribute &Plane::getAttribute(void) const
{
    return Plane::ATTRIBUTE();
}

Intersection Plane::intersect(const Ray3<double> &ray) const
{
    Intersection out = Intersection();

    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);

    Normal3<double> normal ({0, 1, 0});

    if (this->flip)
        normal.y = -1;

    Point3<double> center;

    tools::intersection_res_t res = tools::intersect_plane(center, normal, tmp);

    if (!res.valid || FLT_EPSILON > res.t)
        return out;

    Point3<double> point = tmp(res.t);
    const Vector3<double> dir = center > point;
    double lcosxd = dir.x;
    double lcoszd = dir.z;

    if (this->lz > fabs(lcoszd) && this->lx > fabs(lcosxd))
        out = Intersection(this, point,
                           Point2<double>({(this->lx + lcosxd) / (2 * this->lx),
                                           (this->lz - lcoszd) / (2 * this->lz)}),
                           normal, res.t,
                           *this->transform_local + *this->transform_global);

    return out;
}

void Plane::apply(const Transform<double, 3> &transform)
{
    this->sampler->apply(transform);
    *this->transform_local += transform;
}

void Plane::undo(const Transform<double, 3> &transform)
{
    this->sampler->undo(transform);
    *this->transform_local += transform.inversed();
}

