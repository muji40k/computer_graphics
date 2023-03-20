#include "phong_specular_function.h"

#include "tools.h"

PhongSpecularFunction::PhongSpecularFunction(const Intensity<> &value,
                                             const Intersection &inter,
                                             const double alpha)
{
    this->value = std::make_shared<Intensity<>>(value);
    this->intersection = std::make_shared<Intersection>(inter);
    this->alpha = alpha;
}

Intensity<> PhongSpecularFunction::apply(const Vector3<double> &in,
                                         const Vector3<double> &out) const
{
    Normal3<double> normal = this->intersection->getNormal();
    normal.apply(this->intersection->toGlobal());

    Vector3<double> ref = tools::get_reflection(normal, in);
    double l = 1 / (out.length() * ref.length());
    double fracs = pow((out & ref) * l, this->alpha);

    return *this->value * fracs;
}

PhongSpecularFunction::~PhongSpecularFunction(void) {}

