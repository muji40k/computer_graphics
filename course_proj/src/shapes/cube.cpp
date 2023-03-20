#include "cube.h"

#include "transform_strategies.h"
#include "bounding_sphere.h"
#include "composite_sampler.h"

#include <float.h>

const Attribute &Cube::ATTRIBUTE(void)
{
    static const Attribute attr = ParametricModel::ATTRIBUTE() \
                                  | Attribute(Cube::MAXATTR,
                                              {Cube::ATTRI});
    return attr;
}

Cube::~Cube(void) {}

Cube::Cube(double lx, double ly, double lz)
{
    if (0 > lx || 0 > ly || 0 > lz)
        throw CALL_EX(DegenerateCubeException);

    Transform<double, 3> trans;

    trans.accept(MoveStrategy<double, 3>({0, ly / 2, 0}));
    this->lst.push_back(std::make_shared<Plane>(lx, lz));
    this->lst.back()->apply(trans);

    trans.accept(RotateStrategyOX<double>(M_PI));
    this->lst.push_back(std::make_shared<Plane>(lx, lz));
    this->lst.back()->apply(trans);

    trans += trans.inversed();
    trans.accept(RotateStrategyOX<double>(M_PI / 2));
    trans.accept(MoveStrategy<double>({0, 0, lz / 2}));
    this->lst.push_back(std::make_shared<Plane>(lx, ly));
    this->lst.back()->apply(trans);

    trans.accept(RotateStrategyOY<double>(M_PI));
    this->lst.push_back(std::make_shared<Plane>(lx, ly));
    this->lst.back()->apply(trans);

    trans += trans.inversed();
    trans.accept(RotateStrategyOY<double>(-M_PI / 2));
    trans.accept(RotateStrategyOZ<double>(M_PI / 2));
    trans.accept(MoveStrategy<double>({-lx / 2, 0, 0}));
    this->lst.push_back(std::make_shared<Plane>(lz, ly));
    this->lst.back()->apply(trans);

    trans.accept(RotateStrategyOY<double>(M_PI));
    this->lst.push_back(std::make_shared<Plane>(lz, ly));
    this->lst.back()->apply(trans);

    this->bounding = std::make_shared<BoundingSphere>(Point3<double>{0, 0, 0});
    double diff = sqrt(lx * lx + ly * ly + lz * lz) / 2;
    this->bounding->expand(Point3<double>(diff, 0, 0));
    this->bounding->expand(Point3<double>(-diff, 0, 0));

    this->sampler = std::make_shared<CompositeSampler>();

    for (auto item : this->lst)
        this->sampler->append(&item->getSampler());

    this->transform_local = std::make_shared<Transform<double, 3>>();
}

bool Cube::intersectBounding(const Ray3<double> &ray) const
{
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);

    return this->bounding->intersect(tmp);
}

double Cube::area(void) const
{
    double sum = 0;

    for (auto plane : this->lst)
        sum += plane->area();

    return sum;
}

const ShapeSampler &Cube::getSampler(void) const
{
    return *this->sampler;
}

const Attribute &Cube::getAttribute(void) const
{
    return Cube::ATTRIBUTE();
}

Intersection Cube::intersect(const Ray3<double> &ray) const
{
    Intersection out = Intersection(), current;
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);

    for (std::shared_ptr<Plane> p : this->lst)
    {
        current = p->intersect(tmp);

        if (current && (!out || current.getT() < out.getT()))
            out = current;
    }

    if (out)
    {
        Point3<double> tpoint = out.getPoint();;
        Normal3<double> tnormal = out.getNormal();

        tpoint.apply(out.toGlobal());
        tnormal.apply(out.toGlobal());

        out = Intersection(this, tpoint, out.getPointUV(),
                           tnormal, out.getT(),
                           *transform_local + *transform_global);
    }

    return out;
}

void Cube::apply(const Transform<double, 3> &transform)
{
    *this->transform_local += transform;
    this->sampler->apply(transform);
}

void Cube::undo(const Transform<double, 3> &transform)
{
    *this->transform_local += transform.inversed();
    this->sampler->undo(transform);
}

