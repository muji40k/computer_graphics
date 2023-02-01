#include "plane.h"

#include "bounding_sphere.h"
#include "plane_sampler.h"

const Attribute &Plane::ATTRIBUTE(void)
{
    static const Attribute attr = ObjectPrimitive::ATTRIBUTE() \
                                  | Attribute(Plane::MAXATTR,
                                              {Plane::ATTRI});
    return attr;
}

Plane::~Plane(void) {}

Plane::Plane(const Point3<double> &center, const Vector3<double> &x,
             const Vector3<double> &y, double lx, double ly)
{
    if (0 > lx || 0 > ly)
        throw CALL_EX(DegeneratePlaneException);

    this->x = std::make_shared<Vector3<double>>(x.normalised());
    this->y = std::make_shared<Vector3<double>>(y.normalised());

    this->center = std::make_shared<Point3<double>>(center);
    this->normal = std::make_shared<Normal3<double>>(*this->x * *this->y);
    this->normal_in = std::make_shared<Normal3<double>>(*this->normal);
    this->space = lx * ly * this->normal->length();

    this->vnormal = std::make_shared<Vector3<double>>(*this->normal);
    this->lx = lx / 2;
    this->ly = ly / 2;
    this->ix = 1 / this->x->length();
    this->iy = 1 / this->y->length();

    this->bounding = std::make_shared<BoundingSphere>(center);
    this->bounding->expand(center + (*this->x * lx + *this->y * ly) / 2);
    this->bounding->expand(center + (*this->x * lx + (- *this->y * ly)) / 2);
    this->bounding->expand(center + ((- *this->x * lx) + *this->y * ly) / 2);
    this->bounding->expand(center + ((- *this->x * lx) + (- *this->y * ly)) / 2);

    this->sampler = std::make_shared<PlaneSampler>(center, x, y, lx, ly);
}

Plane::Plane(const Normal3<double> &normal, const Point3<double> &center,
             const Vector3<double> &x, const Vector3<double> &y, double lx,
             double ly)
    : Plane(center, x, y, lx, ly)
{
    if (FLT_EPSILON > fabs(*this->normal & normal))
        throw CALL_EX(DegeneratePlaneException);

    this->normal_in = std::make_shared<Normal3<double>>(normal);
}

bool Plane::intersectBounding(const Ray3<double> &ray) const
{
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);

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
    double t = ((tmp.getOrigin() > *(this->center)) & *(this->normal)) \
               / (tmp.getDirection() & *(this->normal));

    if (FLT_EPSILON > t)
        return out;

    Point3<double> point = tmp(t);
    const Vector3<double> dir = *this->center > point;
    double lcosxd = fabs((*this->x & dir) * this->ix);
    double lcosyd = fabs((*this->y & dir) * this->iy);

    if (this->ly > lcosyd && this->lx > lcosxd)
        out = Intersection(this, point, *(this->normal_in), t,
                           *this->transform_global);

    return out;
}

void Plane::apply(const Transform<double, 3> &transform)
{
    Vector3<double> tmp = this->x->normalised() * this->lx;
    tmp.apply(transform);
    this->lx = tmp.length();

    tmp = this->y->normalised() * this->ly;
    tmp.apply(transform);
    this->ly = tmp.length();

    this->center->apply(transform);
    this->normal->apply(transform);
    *this->vnormal = *this->normal;
    this->x->apply(transform);
    this->y->apply(transform);
    this->ix = 1 / this->x->length();
    this->iy = 1 / this->y->length();

    this->bounding->apply(transform);
    this->sampler->apply(transform);
}

void Plane::undo(const Transform<double, 3> &transform)
{
    Vector3<double> tmp = this->x->normalised() * this->lx;
    tmp.undo(transform);
    this->lx = tmp.length();

    tmp = this->y->normalised() * this->ly;
    tmp.undo(transform);
    this->ly = tmp.length();

    this->center->undo(transform);
    this->normal->undo(transform);
    *this->vnormal = *this->normal;
    this->x->undo(transform);
    this->y->undo(transform);
    this->ix = 1 / this->x->length();
    this->iy = 1 / this->y->length();

    this->bounding->undo(transform);
    this->sampler->undo(transform);
}

