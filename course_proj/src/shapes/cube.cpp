#include "cube.h"

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
}

const Attribute &Cube::getAttribute(void) const
{
    return Cube::ATTRIBUTE();
}

Intersection Cube::intersect(const Ray3<double> &ray) const
{
    Intersection out = this->ParametricModel::intersect(ray), current;
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);
    bool c = false;

    for (std::shared_ptr<Plane> p : this->lst)
    {
        current = p->intersect(tmp);

        if (current && (!out || current.getT() < out.getT()))
        {
            c = true;
            out = current;
        }
    }

    if (c)
        out.apply(*transform_global);

    return out;
}

void Cube::apply(const Transform<double, 3> &transform)
{
    this->ParametricModel::apply(transform);

    for (std::shared_ptr<Plane> p : this->lst)
        p->apply(transform);
}

void Cube::undo(const Transform<double, 3> &transform)
{
    this->ParametricModel::undo(transform);

    for (std::shared_ptr<Plane> p : this->lst)
        p->undo(transform);
}

