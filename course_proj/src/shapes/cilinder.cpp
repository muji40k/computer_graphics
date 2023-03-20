#include "cilinder.h"

#include "composite_sampler.h"
#include "transform_strategies.h"

const Attribute &Cilinder::ATTRIBUTE(void)
{
    static const Attribute attr = ParametricModel::ATTRIBUTE() \
                                  | Attribute(Cilinder::MAXATTR,
                                              {Cilinder::ATTRI});
    return attr;
}

Cilinder::Cilinder(double length, double radius)
{
    this->tube = std::make_shared<Tube>(length, radius);

    length /= 2;

    Transform<double, 3> trans;
    trans.accept(MoveStrategy<double, 3>({0, length, 0}));
    this->top = std::make_shared<Disk>(radius);
    this->top->apply(trans);

    trans.accept(MoveStrategy<double, 3>({0, -length, 0}));
    trans.accept(RotateStrategyOZ<double>(M_PI));
    trans.accept(MoveStrategy<double, 3>({0, -length, 0}));
    this->bottom = std::make_shared<Disk>(radius);
    this->bottom->apply(trans);

    this->sampler = std::make_shared<CompositeSampler>();

    this->sampler->append(&this->tube->getSampler());
    this->sampler->append(&this->top->getSampler());
    this->sampler->append(&this->bottom->getSampler());

    this->transform_local = std::make_shared<Transform<double, 3>>();
}

Cilinder::~Cilinder() {}

bool Cilinder::intersectBounding(const Ray3<double> &ray) const
{
    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);

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
    tmp.undo(*this->transform_local);
    Intersection out, current;

    out = this->tube->intersect(tmp);
    current = this->top->intersect(tmp);

    if (current && (!out || out.getT() > current.getT()))
        out = current;

    current = this->bottom->intersect(tmp);

    if (current && (!out || out.getT() > current.getT()))
        out = current;

    if (out)
    {
        Point3<double> tpoint = out.getPoint();;
        Normal3<double> tnormal = out.getNormal();

        tpoint.apply(out.toGlobal());
        tnormal.apply(out.toGlobal());

        out = Intersection(this, tpoint, out.getPointUV(),
                           tnormal, out.getT(),
                           *transform_local + *this->transform_global);
    }

    return out;
}

void Cilinder::apply(const Transform<double, 3> &transform)
{
    *this->transform_local += transform;
    this->sampler->apply(transform);
}

void Cilinder::undo(const Transform<double, 3> &transform)
{
    *this->transform_local += transform.inversed();
    this->sampler->undo(transform);
}


