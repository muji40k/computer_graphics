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

bool PolygonModel::intersectBounding(const Ray3<double> &ray) const
{
    bool v = false;
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);

    for (const_iterator it = this->begin(); !v && this->end() != it; it++)
        v = (*it)->intersectBounding(tmp);

    return v;
}

double PolygonModel::area(void) const
{
    double sum = 0;

    for (auto polygon : this->lst)
        sum += polygon->area();

    return sum;
}

const Attribute &PolygonModel::getAttribute(void) const
{
    return PolygonModel::ATTRIBUTE();
}

Intersection PolygonModel::intersect(const Ray3<double> &ray) const
{
    Intersection out = Intersection();
    Intersection current;

    for (Polygon *pol: this->lst)
    {
        current = pol->intersect(ray);

        if (current && (!out || out.getT() > current.getT()))
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

void PolygonModel::apply(const Transform<double, 3> &transform)
{
    for (Polygon *pol: this->lst)
        pol->apply(transform);
}

void PolygonModel::undo(const Transform<double, 3> &transform)
{
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

PolygonModel::iterator PolygonModel::begin(void)
{
    return this->lst.begin();
}

PolygonModel::iterator PolygonModel::end(void)
{
    return this->lst.end();
}

PolygonModel::const_iterator PolygonModel::begin(void) const
{
    return this->lst.cbegin();
}

PolygonModel::const_iterator PolygonModel::end(void) const
{
    return this->lst.cend();
}

PolygonModel::const_iterator PolygonModel::cbegin(void) const
{
    return this->lst.cbegin();
}

PolygonModel::const_iterator PolygonModel::cend(void) const
{
    return this->lst.cend();
}

