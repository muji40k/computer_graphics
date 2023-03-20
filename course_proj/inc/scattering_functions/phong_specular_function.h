#ifndef _PHONG_SPECULAR_FUNCTION_H_
#define _PHONG_SPECULAR_FUNCTION_H_

#include <memory>

#include "difusion_function.h"
#include "intersection.h"

class PhongSpecularFunction : public DifusionFunction
{
    public:
        PhongSpecularFunction(const Intensity<> &value,
                              const Intersection &inter,
                              const double alpha);
        virtual ~PhongSpecularFunction(void) override;
        virtual Intensity<> apply(const Vector3<double> &in,
                                  const Vector3<double> &out) const override;

    private:
        std::shared_ptr<Intensity<>> value;
        std::shared_ptr<Intersection> intersection;
        double alpha;
};

#endif

