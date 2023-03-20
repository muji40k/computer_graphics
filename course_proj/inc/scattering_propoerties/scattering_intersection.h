#ifndef _SCATTERING_INTERSECTION_H_
#define _SCATTERING_INTERSECTION_H_

#include "scattering_property.h"

#include "intersection.h"

class ScatteringIntersection : public ScatteringProperty
{
    public:
        static const size_t ATTRI = 2;
        static const Attribute &ATTRIBUTE(void);

    public:
        ScatteringIntersection(const Intersection &inter);
        virtual ~ScatteringIntersection(void) override;
        const Intersection &getIntersection(void);
        virtual const Attribute &getAttribute(void) const override;

    private:
        std::shared_ptr<Intersection> intersection;

};

#endif

