#include "cilinder.h"

#include "composite_sampler.h"

const Attribute &Cilinder::ATTRIBUTE(void)
{
    static const Attribute attr = ParametricModel::ATTRIBUTE() \
                                  | Attribute(Cilinder::MAXATTR,
                                              {Cilinder::ATTRI});
    return attr;
}

Cilinder::Cilinder(const Vector3<double> &normal, const Point3<double> &center,
                   double length, double radius)
{
    this->tube = std::make_shared<Tube>(normal, center, length, radius);
    Vector3<double> v = normal.normalised();
    length /= 2;
    this->top = std::make_shared<Disk>(center + v * (length), v, radius);
    this->bottom = std::make_shared<Disk>(center + v * (-length), -v, radius);

    this->sampler = std::make_shared<CompositeSampler>();

    this->sampler->append(&this->tube->getSampler());
    this->sampler->append(&this->top->getSampler());
    this->sampler->append(&this->bottom->getSampler());
}

Cilinder::~Cilinder() {}

bool Cilinder::intersectBounding(const Ray3<double> &ray) const
{
    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);

    return this->tube->intersectBounding(tmp);
}


double Cilinder::area(void) const
{
    return this->tube->area() + this->top->area() + this->bottom->area();
}

const ShapeSampler &Cilinder::getSampler(void) const
{
    return *this->sampler;
}

const Attribute &Cilinder::getAttribute(void) const
{
    return Cilinder::ATTRIBUTE();
}

Intersection Cilinder::intersect(const Ray3<double> &ray) const
{
    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);
    Intersection out, current;

    out = this->tube->intersect(tmp);
    current = this->top->intersect(tmp);

    if (current && (!out || out.getT() > current.getT()))
        out = current;

    current = this->bottom->intersect(tmp);

    if (current && (!out || out.getT() > current.getT()))
        out = current;

    if (out)
        out = Intersection(this, out.getPoint(), out.getNormal(), out.getT(),
                           *this->transform_global);

    return out;
}

void Cilinder::apply(const Transform<double, 3> &transform)
{
    this->tube->apply(transform);
    this->top->apply(transform);
    this->bottom->apply(transform);
}

void Cilinder::undo(const Transform<double, 3> &transform)
{
    this->tube->undo(transform);
    this->top->undo(transform);
    this->bottom->undo(transform);
}


