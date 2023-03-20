#include "scene.h"

#include <algorithm>

void Scene::add(std::shared_ptr<Shape> shape)
{
    if (nullptr == shape)
        throw CALL_EX(NullPointerSceneException);

    for (auto ptr : this->shapes)
        if (ptr == shape)
            throw CALL_EX(DuplicateSceneException);

    this->shapes.push_back(shape);
}

void Scene::remove(std::shared_ptr<Shape> shape)
{
    if (nullptr == shape)
        throw CALL_EX(NullPointerSceneException);

    const size_t lim = this->shapes.size();
    size_t i = 0;
    auto it = this->shapes.begin();

    for (; shape != *it && lim > i; i++, it++);

    if (lim != i)
    {
        this->removePropertiesForShape(*it);
        this->shapes.erase(it);
    }
}

void Scene::remove(const size_t index)
{
    if (this->shapes.size() <= index)
        throw CALL_EX(IndexViolationSceneException);

    auto it = this->shapes.begin();

    for (size_t i = 0; index > i; i++, it++);

    this->removePropertiesForShape(*it);
    this->shapes.erase(it);
}

void Scene::remove(Scene::iterator &it)
{
    auto _it = std::find(this->shapes.begin(), this->shapes.end(), *it);

    if (_it != this->end())
    {
        this->removePropertiesForShape(*it);
        it = this->shapes.erase(it);
    }
}

std::shared_ptr<Shape> Scene::get(const size_t index)
{
    if (this->shapes.size() <= index)
        throw CALL_EX(IndexViolationSceneException);

    auto it = this->shapes.begin();

    for (size_t i = 0; index > i; i++, it++);

    return *it;
}

std::shared_ptr<const Shape> Scene::get(const size_t index) const
{
    if (this->shapes.size() <= index)
        throw CALL_EX(IndexViolationSceneException);

    auto it = this->shapes.begin();

    for (size_t i = 0; index > i; i++, it++);

    return *it;
}

size_t Scene::getAmount(void) const
{
    return this->shapes.size();
}

void Scene::addProperty(std::shared_ptr<ShapeProperty> propetry)
{
    if (nullptr == propetry)
        throw CALL_EX(NullPointerSceneException);

    this->properties.push_back(propetry);
}

std::list<std::shared_ptr<ShapeProperty>> Scene::getProperties(const Attribute &attr)
{
    std::list<std::shared_ptr<ShapeProperty>> out;

    for (std::shared_ptr<ShapeProperty> prop : this->properties)
        if (attr <= prop->getAttribute())
            out.push_back(prop);

    return out;
}

std::list<std::shared_ptr<ShapeProperty>> Scene::getProperties(const Shape *const shape)
{
    std::list<std::shared_ptr<ShapeProperty>> out;

    for (std::shared_ptr<ShapeProperty> prop : this->properties)
        if (&(prop->getTarget()) == shape)
            out.push_back(prop);

    return out;
}

std::list<std::shared_ptr<Shape>> Scene::getShapes(const Attribute &attr)
{
    std::list<std::shared_ptr<Shape>> out;

    for (std::shared_ptr<Shape> shape : this->shapes)
        if (attr <= shape->getAttribute())
            out.push_back(shape);

    return out;
}

void Scene::removeProperty(std::shared_ptr<ShapeProperty> &property)
{
    auto it = this->properties.begin();

    for (; it != this->properties.end() && *it != property; it++);

    if (it == this->properties.end())
        CALL_EX(NoPropertyToRemoveSceneException);

    this->properties.erase(it);
}

std::list<std::shared_ptr<const ShapeProperty>> Scene::getProperties(const Attribute &attr) const
{
    std::list<std::shared_ptr<const ShapeProperty>> out;

    for (std::shared_ptr<const ShapeProperty> prop : this->properties)
        if (attr <= prop->getAttribute())
            out.push_back(prop);

    return out;
}

std::list<std::shared_ptr<const ShapeProperty>> Scene::getProperties(const Shape *const shape) const
{
    std::list<std::shared_ptr<const ShapeProperty>> out;

    for (std::shared_ptr<const ShapeProperty> prop : this->properties)
        if (&(prop->getTarget()) == shape)
            out.push_back(prop);

    return out;
}

std::list<std::shared_ptr<const Shape>> Scene::getShapes(const Attribute &attr) const
{
    std::list<std::shared_ptr<const Shape>> out;

    for (std::shared_ptr<const Shape> shape : this->shapes)
        if (attr <= shape->getAttribute())
            out.push_back(shape);

    return out;
}

Scene::iterator Scene::begin(void)
{
    return this->shapes.begin();
}

Scene::iterator Scene::end(void)
{
    return this->shapes.end();
}

Scene::const_iterator Scene::begin(void) const
{
    return this->shapes.cbegin();
}

Scene::const_iterator Scene::end(void) const
{
    return this->shapes.cend();
}

Scene::const_iterator Scene::cbegin(void) const
{
    return this->shapes.cbegin();
}

Scene::const_iterator Scene::cend(void) const
{
    return this->shapes.cend();
}

void Scene::removePropertiesForShape(std::shared_ptr<Shape> &shape)
{
    auto it = this->properties.begin();

    for (; it != this->properties.end(); it++)
        if (&((*it)->getTarget()) == shape.get())
            this->properties.erase(it);
}

