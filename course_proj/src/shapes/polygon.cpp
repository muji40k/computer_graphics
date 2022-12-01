#include <math.h>
#include <float.h>
#include "polygon.h"
#include "vector.h"

const Attribute &Polygon::ATTRIBUTE(void)
{
    static const Attribute attr = ObjectPrimitive::ATTRIBUTE() \
                                  | Attribute(Polygon::MAXATTR,
                                              {Polygon::ATTRI});
    return attr;
}

Polygon::~Polygon(void) {}

Polygon::Polygon(const Point3<double> &a, const Point3<double> &b,
                 const Point3<double> &c, const Normal3<double> &normal)
{
    Vector3 tmp1 = a < b, tmp2 = c < b;
    Vector3 n = tmp1 * tmp2;

    if (FLT_EPSILON > fabs(n.length()))
        throw CALL_EX(DegeneratePolygonException);

    this->center = std::make_shared<Point3<double>>(((a + b) / 2 + c) / 2);

    for (size_t i = 0; 3 > i; i++)
        this->normals[i] = std::make_shared<Vector3<double>>();

    double t;
    Vector3<double> vcur;
    Vector3<double> vside;

    vcur = a > *(this->center);
    vside = a > b;
    t = (vcur & vside) / vside.lengthSqr();
    *(this->normals[0]) = *(this->center) > (a + vside * t);
    this->lnormalssqr[0] = this->normals[0]->lengthSqr();

    vcur = b > *(this->center);
    vside = b > c;
    t = (vcur & vside) / vside.lengthSqr();
    *(this->normals[1]) = *(this->center) > (b + vside * t);
    this->lnormalssqr[1] = this->normals[1]->lengthSqr();

    vcur = c > *(this->center);
    vside = c > a;
    t = (vcur & vside) / vside.lengthSqr();
    *(this->normals[2]) = *(this->center) > (c + vside * t);
    this->lnormalssqr[2] = this->normals[2]->lengthSqr();

    // this->a = std::make_shared<Point3<double>>(a);
    // this->b = std::make_shared<Point3<double>>(b);
    // this->c = std::make_shared<Point3<double>>(c);

    this->normal_in = std::make_shared<Normal3<double>>(normal);

    if (0 > (n & normal))
        n *= -1;

    this->normal = std::make_shared<Normal3<double>>(n);
}

const Attribute &Polygon::getAttribute(void) const
{
    return Polygon::ATTRIBUTE();
}

Intersection Polygon::intersect(const Ray3<double> &ray) const
{
    Intersection out = this->ObjectPrimitive::intersect(ray);

    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);
    double t = ((tmp.getOrigin() > *(this->center)) & *(this->normal)) \
               / (tmp.getDirection() & *(this->normal));
    // double t = ((tmp.getOrigin() > *(this->a)) & *(this->normal))
    //            / (tmp.getDirection() & *(this->normal));

    if (out && (FLT_EPSILON > t || out.getT() < t))
        return out;

    Point3<double> point = tmp(t);

    Vector3<double> dir = *this->center > point;
    bool valid = true;

    for (size_t i = 0; valid && 3 > i; i++)
        if (((*this->normals[i]) & dir) > this->lnormalssqr[i])
            valid = false;

    // Vector3<double> r = this->sideO(0) > point;
    // Vector3<double> v = this->sideV(0);
    // bool sign = 0 > ((r * v) & *(this->normal)), valid = true;
    // double res;
    //  
    // for (size_t i = 1; valid && 3 > i; i++)
    // {
    //     r = this->sideO(i) > point;
    //     v = this->sideV(i);
    //     res = ((r * v) & *(this->normal));
    //  
    //     if ((!sign && 0 > res) || (sign && 0 < res))
    //         valid = false;
    // }

    if (valid)
        out = Intersection(this, point, *(this->normal_in), t,
                           *this->transform_global);

    return out;
}

void Polygon::apply(const Transform<double, 3> &transform)
{
    this->ObjectPrimitive::apply(transform);

    this->center->apply(transform);

    for (size_t i = 0; 3 > i; i++)
    {
        this->normals[i]->apply(transform);
        this->lnormalssqr[i] = this->normals[i]->lengthSqr();
    }

    // a->apply(transform);
    // b->apply(transform);
    // c->apply(transform);

    normal_in->apply(transform);
    normal->apply(transform);
}

void Polygon::undo(const Transform<double, 3> &transform)
{
    this->ObjectPrimitive::undo(transform);

    for (size_t i = 0; 3 > i; i++)
    {
        this->normals[i]->apply(transform);
        this->lnormalssqr[i] = this->normals[i]->lengthSqr();
    }

    // a->undo(transform);
    // b->undo(transform);
    // c->undo(transform);

    normal_in->undo(transform);
    normal->undo(transform);
}

// Vector3<double> Polygon::sideV(size_t i) const
// {
//     i %= 3;
//  
//     if (0 == i)
//         return *(this->a) > *(this->b);
//  
//     if (1 == i)
//         return *(this->b) > *(this->c);
//  
//     return *(this->c) > *(this->a);
// }
//  
// const Point3<double> &Polygon::sideO(size_t i) const
// {
//     i %= 3;
//  
//     if (0 == i)
//         return *(this->a);
//  
//     if (1 == i)
//         return *(this->b);
//  
//     return *(this->c);
// }

