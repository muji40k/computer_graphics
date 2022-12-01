#include "plane.h"

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

    this->center = std::make_shared<Point3<double>>(center);
    this->normal = std::make_shared<Normal3<double>>(x * y);
    this->normal_in = std::make_shared<Normal3<double>>(*this->normal);

    this->vnormal = std::make_shared<Vector3<double>>(*this->normal);
    this->x = std::make_shared<Vector3<double>>(x);
    this->y = std::make_shared<Vector3<double>>(y);
    this->lx = lx / 2;
    this->ly = ly / 2;
    this->ix = 1 / this->x->length();
    this->iy = 1 / this->y->length();
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

const Attribute &Plane::getAttribute(void) const
{
    return Plane::ATTRIBUTE();
}

Intersection Plane::intersect(const Ray3<double> &ray) const
{
    Intersection out = this->ObjectPrimitive::intersect(ray);

    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);
    double t = ((tmp.getOrigin() > *(this->center)) & *(this->normal)) \
               / (tmp.getDirection() & *(this->normal));

    if (out && (FLT_EPSILON > t || out.getT() < t))
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
    this->ObjectPrimitive::apply(transform);
    this->center->apply(transform);
    this->normal->apply(transform);
    *this->vnormal = *this->normal;
    this->x->apply(transform);
    this->y->apply(transform);
    this->ix = 1 / this->x->length();
    this->iy = 1 / this->y->length();
}

void Plane::undo(const Transform<double, 3> &transform)
{
    this->ObjectPrimitive::undo(transform);
    this->center->undo(transform);
    this->normal->undo(transform);
    *this->vnormal = *this->normal;
    this->x->undo(transform);
    this->y->undo(transform);
    this->ix = 1 / this->x->length();
    this->iy = 1 / this->y->length();
}


