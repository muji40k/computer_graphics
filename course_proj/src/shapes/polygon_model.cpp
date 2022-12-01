#include <algorithm>
#include "polygon_model.h"

const Attribute &PolygonModel::ATTRIBUTE(void)
{
    static const Attribute attr = Object::ATTRIBUTE() \
                                  | Attribute(PolygonModel::MAXATTR,
                                              {PolygonModel::ATTRI});
    return attr;
}

PolygonModel::~PolygonModel(void) {}

const Attribute &PolygonModel::getAttribute(void) const
{
    return PolygonModel::ATTRIBUTE();
}

Intersection PolygonModel::intersect(const Ray3<double> &ray) const
{
    Intersection out = this->Object::intersect(ray);
    Intersection current;
    bool changed = false;

    for (Polygon *pol: this->lst)
    {
        current = pol->intersect(ray);

        if (current && out.getT() > current.getT())
        {
            changed = true;
            out = current;
        }
    }

    if (changed)
        out.apply(*this->transform_global);

    return out;
}

void PolygonModel::apply(const Transform<double, 3> &transform)
{
    this->Object::apply(transform);

    for (Polygon *pol: this->lst)
        pol->apply(transform);
}

void PolygonModel::undo(const Transform<double, 3> &transform)
{
    this->Object::undo(transform);

    for (Polygon *pol: this->lst)
        pol->undo(transform);
}

void PolygonModel::add(Polygon *shape)
{
    if (nullptr == shape)
        throw CALL_EX(NullPointerPolygonModelException);

    this->lst.push_back(shape);
}

void PolygonModel::remove(Polygon *shape)
{
    if (nullptr == shape)
        throw CALL_EX(NullPointerPolygonModelException);

    const size_t lim = this->lst.size();
    size_t i = 0;
    auto it = this->lst.begin();

    for (; shape != *it && lim > i; i++, it++);

    if (lim != i)
        this->lst.erase(it);
}

void PolygonModel::remove(const size_t index)
{
    if (this->lst.size() <= index)
        throw CALL_EX(IndexViolationShapeException);

    auto it = this->lst.begin();

    for (size_t i = 0; index > i; i++, it++);

    this->lst.erase(it);
}

void PolygonModel::remove(iterator &it)
{
    auto _it = std::find(this->begin(), this->end(), *it);

    if (_it != this->end())
        it = this->lst.erase(it);
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


