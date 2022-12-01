#include "shape.h"
#include <algorithm>

const Attribute &Shape::ATTRIBUTE(void)
{
    static const Attribute attr = Attribute(Shape::MAXATTR, {Shape::ATTRI});
    return attr;
}

Shape::Shape(Shape *parent)
    : structure(), parent(parent), transform_global()
{
    if (parent)
        parent->add(this);

    this->transform_global = std::make_shared<Transform<double, 3>>();
}

Shape::~Shape() = default;

void Shape::add(Shape *shape)
{
    if (nullptr == shape)
        throw CALL_EX(NullPointerShapeException);

    if (this == shape->parent)
        return;

    this->structure.push_back(shape);

    if (shape->parent)
        shape->parent->remove(shape);

    shape->parent = this;
}

void Shape::remove(Shape *shape)
{
    if (nullptr == shape)
        throw CALL_EX(NullPointerShapeException);

    if (this != shape->parent)
        return;

    const size_t lim = this->structure.size();
    size_t i = 0;
    auto it = this->structure.begin();

    for (; shape != *it && lim > i; i++, it++);

    if (lim != i)
    {
        this->structure.erase(it);
        shape->parent = nullptr;
    }
}

void Shape::remove(const size_t index)
{
    if (this->structure.size() <= index)
        throw CALL_EX(IndexViolationShapeException);

    auto it = this->structure.begin();

    for (size_t i = 0; index > i; i++, it++);

    (*it)->parent = nullptr;
    this->structure.erase(it);
}

void Shape::remove(Shape::iterator &it)
{
    auto _it = std::find(this->begin(), this->end(), *it);

    if (_it != this->end())
    {
        (*it)->parent = nullptr;
        it = this->structure.erase(it);
    }
}

Shape &Shape::get(const size_t index)
{
    if (this->structure.size() <= index)
        throw CALL_EX(IndexViolationShapeException);

    auto it = this->structure.begin();

    for (size_t i = 0; index > i; i++, it++);

    return **it;
}

const Shape &Shape::get(const size_t index) const
{
    if (this->structure.size() <= index)
        throw CALL_EX(IndexViolationShapeException);

    auto it = this->structure.begin();

    for (size_t i = 0; index > i; i++, it++);

    return **it;
}

size_t Shape::getAmount(void) const
{
    return this->structure.size();
}

const Attribute &Shape::getAttribute(void) const
{
    return Shape::ATTRIBUTE();
}

Intersection Shape::intersect(const Ray3<double> &ray) const
{
    Shape::const_iterator it = this->begin();
    Intersection out;

    if (this->end() == it)
        return out;

    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);
    out = (*it)->intersect(tmp);
    it++;

    for (Intersection current; this->end() != it; it++)
    {
        current = (*it)->intersect(tmp);

        if (current && (!out || current.getT() < out.getT()))
            out = current;
    }

    if (out)
        out.apply(*this->transform_global);

    return out;
}

void Shape::setParent(Shape *parent)
{
    if (!parent)
        this->parent = nullptr;
    else
        parent->add(this);
}

Shape &Shape::getParent(void)
{
    return *this->parent;
}

const Shape &Shape::getParent(void) const
{
    return *this->parent;
}

void Shape::apply(const Transform<double, 3> &transform)
{
    for (Shape *shape: this->structure)
        shape->apply(transform);
}

void Shape::undo(const Transform<double, 3> &transform)
{
    for (Shape *shape: this->structure)
        shape->undo(transform);
}

void Shape::applyBasis(const Transform<double, 3> &transform)
{
    *(this->transform_global) += transform;
}

void Shape::undoBasis(const Transform<double, 3> &transform)
{
    *(this->transform_global) += transform.inversed();
}

void Shape::resetBasis(void)
{
    *(this->transform_global) = Transform<double, 3>();
}

Shape::iterator Shape::begin(void)
{
    return this->structure.begin();
}

Shape::iterator Shape::end(void)
{
    return this->structure.end();
}

Shape::const_iterator Shape::begin(void) const
{
    return this->structure.cbegin();
}

Shape::const_iterator Shape::end(void) const
{
    return this->structure.cend();
}

Shape::const_iterator Shape::cbegin(void) const
{
    return this->structure.cbegin();
}

Shape::const_iterator Shape::cend(void) const
{
    return this->structure.cend();
}

