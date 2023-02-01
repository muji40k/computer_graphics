#include "cube.h"

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

    this->lst.push_back(std::make_shared<Plane>(Point3<double>({lx / 2, 0, 0}),
                                                Vector3<double>({0, 1, 0}),
                                                Vector3<double>({0, 0, 1}),
                                                ly, lz));
    this->lst.push_back(std::make_shared<Plane>(Point3<double>({-lx / 2, 0, 0}),
                                                Vector3<double>({0, -1, 0}),
                                                Vector3<double>({0, 0, 1}),
                                                ly, lz));
    this->lst.push_back(std::make_shared<Plane>(Point3<double>({0, ly / 2, 0}),
                                                Vector3<double>({1, 0, 0}),
                                                Vector3<double>({0, 0, 1}),
                                                lx, lz));
    this->lst.push_back(std::make_shared<Plane>(Point3<double>({0, -ly / 2, 0}),
                                                Vector3<double>({-1, 0, 0}),
                                                Vector3<double>({0, 0, 1}),
                                                lx, lz));
    this->lst.push_back(std::make_shared<Plane>(Point3<double>({0, 0, lz / 2}),
                                                Vector3<double>({1, 0, 0}),
                                                Vector3<double>({0, 1, 0}),
                                                lx, ly));
    this->lst.push_back(std::make_shared<Plane>(Point3<double>({0, 0, -lz / 2}),
                                                Vector3<double>({-1, 0, 0}),
                                                Vector3<double>({0, 1, 0}),
                                                lx, ly));

    this->bounding = std::make_shared<BoundingSphere>(Point3<double>{0, 0, 0});
    double diff = sqrt(lx * lx + ly * ly + lz * lz) / 2;
    this->bounding->expand(Point3<double>(diff, 0, 0));
    this->bounding->expand(Point3<double>(-diff, 0, 0));

    this->sampler = std::make_shared<CompositeSampler>();

    for (auto item : this->lst)
        this->sampler->append(&item->getSampler());
}

bool Cube::intersectBounding(const Ray3<double> &ray) const
{
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);

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

    for (std::shared_ptr<Plane> p : this->lst)
    {
        current = p->intersect(tmp);

        if (current && (!out || current.getT() < out.getT()))
            out = current;
    }

    if (out)
    {
        out = Intersection(this, out.getPoint(), out.getNormal(), out.getT(),
                           out.toGlobal());
        out.apply(*this->transform_global);
    }

    return out;
}

void Cube::apply(const Transform<double, 3> &transform)
{
    for (std::shared_ptr<Plane> p : this->lst)
        p->apply(transform);

    this->bounding->apply(transform);
}

void Cube::undo(const Transform<double, 3> &transform)
{
    for (std::shared_ptr<Plane> p : this->lst)
        p->undo(transform);

    this->bounding->undo(transform);
}

