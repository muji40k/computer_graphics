#include <algorithm>
#include "polygon_model.h"

#include "composite_sampler.h"
#include "bounding_sphere.h"

const Attribute &PolygonModel::ATTRIBUTE(void)
{
    static const Attribute attr = Object::ATTRIBUTE() \
                                  | Attribute(PolygonModel::MAXATTR,
                                              {PolygonModel::ATTRI});
    return attr;
}

PolygonModel::PolygonModel(void)
{
    this->sampler = std::make_shared<CompositeSampler>();
    this->bounding = nullptr;
}

PolygonModel::~PolygonModel(void) {}

bool PolygonModel::intersectBounding(const Ray3<double> &ray) const
{
    // bool v = false;
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);

    return this->bounding->intersect(tmp);

    // for (auto it = this->lst.begin(); !v && this->lst.end() != it; it++)
    //     v = (*it)->intersectBounding(tmp);
    //  
    // return v;
}

double PolygonModel::area(void) const
{
    double sum = 0;

    for (auto polygon : this->lst)
        sum += polygon->area();

    return sum;
}

const ShapeSampler &PolygonModel::getSampler(void) const
{
    return *this->sampler;
}

const Attribute &PolygonModel::getAttribute(void) const
{
    return PolygonModel::ATTRIBUTE();
}

Intersection PolygonModel::intersect(const Ray3<double> &ray) const
{
    Intersection out = Intersection();
    Intersection current;
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);

    for (std::shared_ptr<Polygon> pol: this->lst)
        if (pol->intersectBounding(tmp))
        {
            current = pol->intersect(tmp);

            if (current && (!out || out.getT() > current.getT()))
                out = current;
        }

    if (out)
        out = Intersection(this, out.getPoint(), out.getNormal(), out.getT(),
                           *this->transform_global);

    return out;
}

void PolygonModel::apply(const Transform<double, 3> &transform)
{
    for (std::shared_ptr<Polygon> pol: this->lst)
        pol->apply(transform);

    this->bounding->apply(transform);
}

void PolygonModel::undo(const Transform<double, 3> &transform)
{
    for (std::shared_ptr<Polygon> pol: this->lst)
        pol->undo(transform);

    this->bounding->undo(transform);
}

void PolygonModel::add(const Point3<double>  &a, const Point3<double>  &b,
                       const Point3<double>  &c, const Normal3<double> &normal)
{
    this->lst.push_back(std::make_shared<Polygon>(a, b, c, normal));
    this->sampler->append(&this->lst.back()->getSampler());

    this->expandBounding(a, b, c);
}

void PolygonModel::remove(const size_t index)
{
    if (this->lst.size() <= index)
        throw CALL_EX(IndexViolationShapeException);

    auto it = this->lst.begin();

    for (size_t i = 0; index > i; i++, it++);

    this->lst.erase(it);
}

Polygon &PolygonModel::get(const size_t index)
{
    if (this->lst.size() <= index)
        throw CALL_EX(IndexViolationPolygonModelException);

    auto it = this->lst.begin();

    for (size_t i = 0; index > i; i++, it++);

    return **it;
}

const Polygon &PolygonModel::get(const size_t index) const
{
    if (this->lst.size() <= index)
        throw CALL_EX(IndexViolationPolygonModelException);

    auto it = this->lst.begin();

    for (size_t i = 0; index > i; i++, it++);

    return **it;
}

size_t PolygonModel::getAmount(void) const
{
    return this->lst.size();
}

void PolygonModel::expandBounding(const Point3<double>  &a, const Point3<double>  &b,
                                  const Point3<double>  &c)
{
    if (!this->bounding)
        this->bounding = std::make_shared<BoundingSphere>(a);

    const Point3<double> *points[] = {&a, &b, &c};

    for (size_t i = 0; 3 > i; i++)
        if (!this->bounding->isInside(*points[i]))
            this->bounding->expand(*points[i]);
}

