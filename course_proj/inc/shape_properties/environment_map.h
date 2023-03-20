#ifndef _ENVIRONMENT_MAP_H_
#define _ENVIRONMENT_MAP_H_

#include <memory>

#include "common_property.h"
#include "texture.h"
#include "intensity.h"
#include "ray.h"

class EnvironmentMap : public CommonProperty
{
    public:
        static const size_t ATTRI = 6;
        static const Attribute &ATTRIBUTE(void);

    public:
        EnvironmentMap(const std::shared_ptr<Texture<Intensity<>>> &texture,
                       const double &size);
        virtual ~EnvironmentMap(void) = 0;

        virtual const Attribute &getAttribute(void) const override;

        void setTexture(const std::shared_ptr<Texture<Intensity<>>> &texture);
        void setSize(const double &size);

        virtual Intensity<> map(const Ray3<double> &ray) const = 0;

    protected:
        std::shared_ptr<Texture<Intensity<>>> texture;
        double size;
};

DEF_EX(CommonEnvironmentMapException, CommonCommonPropertyException,
       "General environmental map exception");

#endif

