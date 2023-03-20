#ifndef _SCENE_H_
#define _SCENE_H_

#include <list>
#include <memory>

#include "base_exception.h"

#include "attribute.h"
#include "shape.h"
#include "shape_property.h"

class Scene
{
    public:
        using iterator = list<std::shared_ptr<Shape>>::iterator;
        using const_iterator = list<std::shared_ptr<Shape>>::const_iterator;

        Scene(void) = default;

        void add(std::shared_ptr<Shape> shape);
        void remove(std::shared_ptr<Shape> shape);
        void remove(const size_t index);
        void remove(iterator &it);
        std::shared_ptr<Shape> get(const size_t index);
        std::shared_ptr<const Shape> get(const size_t index) const;
        size_t getAmount(void) const;

        void addProperty(std::shared_ptr<ShapeProperty> propetry);

        std::list<std::shared_ptr<ShapeProperty>> getProperties(const Attribute &attr);
        std::list<std::shared_ptr<ShapeProperty>> getProperties(const Shape *const shape);
        std::list<std::shared_ptr<Shape>> getShapes(const Attribute &attr);
        void removeProperty(std::shared_ptr<ShapeProperty> &property);

        std::list<std::shared_ptr<const ShapeProperty>> getProperties(const Attribute &attr) const;
        std::list<std::shared_ptr<const ShapeProperty>> getProperties(const Shape *const shape) const;
        std::list<std::shared_ptr<const Shape>> getShapes(const Attribute &attr) const;

        iterator begin(void);
        iterator end(void);
        const_iterator begin(void) const;
        const_iterator end(void) const;
        const_iterator cbegin(void) const;
        const_iterator cend(void) const;

    private:
        void removePropertiesForShape(std::shared_ptr<Shape> &shape);

    private:
        std::list<std::shared_ptr<Shape>> shapes;
        std::list<std::shared_ptr<ShapeProperty>> properties;
};

class NullPointerSceneException: public BaseException
{
    public:
        NullPointerSceneException(void) = default;
        NullPointerSceneException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Null pointer to a scene")
            : BaseException(filename, line, function, message) {};
        ~NullPointerSceneException(void) = default;
};

class DuplicateSceneException: public BaseException
{
    public:
        DuplicateSceneException(void) = default;
        DuplicateSceneException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Duplicate of shape in scene")
            : BaseException(filename, line, function, message) {};
        ~DuplicateSceneException(void) = default;
};

class IndexViolationSceneException: public BaseException
{
    public:
        IndexViolationSceneException(void) = default;
        IndexViolationSceneException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Requested shape index is above container size")
            : BaseException(filename, line, function, message) {};
        ~IndexViolationSceneException(void) = default;
};

class NoPropertyToRemoveSceneException: public BaseException
{
    public:
        NoPropertyToRemoveSceneException(void) = default;
        NoPropertyToRemoveSceneException(const char *filename, const size_t line,
                                         const char *function,
                                         const char *message = "Given property isn't presented in scene")
            : BaseException(filename, line, function, message) {};
        ~NoPropertyToRemoveSceneException(void) = default;
};

#endif

