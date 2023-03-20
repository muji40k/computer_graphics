#include <math.h>
#include <float.h>
#include "polygon.h"
#include "vector.h"

#include "bounding_sphere.h"

#include "polygon_sampler.h"

#include "tools.h"

const Attribute &Polygon::ATTRIBUTE(void)
{
    static const Attribute attr = ObjectPrimitive::ATTRIBUTE() \
                                  | Attribute(Polygon::MAXATTR,
                                              {Polygon::ATTRI});
    return attr;
}

Polygon::~Polygon(void) {}

Polygon::Polygon(const Point3<double> &a, const Point3<double> &b,
                 const Point3<double> &c, const Normal3<double> &normal,
                 const Point2<double> &uva, const Point2<double>  &uvb,
                 const Point2<double> &uvc)
{
    Vector3 tmp1 = a < b, tmp2 = c < b;
    Vector3 n = tmp1 * tmp2;
    this->space = n.length();

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

    this->normal_in = std::make_shared<Normal3<double>>(normal);

    if (0 > (n & normal))
        n *= -1;

    this->normal = std::make_shared<Normal3<double>>(n);

    Point3<double> center = (a + b + c) / 3;
    this->bounding = std::make_shared<BoundingSphere>(center);
    this->bounding->expand(a);
    this->bounding->expand(b);
    this->bounding->expand(c);

    for (size_t i = 0; 3 > i; i++)
    {
        this->points[i] = std::make_shared<Point3<double>>();
        this->pointsuv[i] = std::make_shared<Point2<double>>();
    }

    *this->points[0] = a;
    *this->points[1] = b;
    *this->points[2] = c;
    *this->pointsuv[0] = uva;
    *this->pointsuv[1] = uvb;
    *this->pointsuv[2] = uvc;

    this->sampler = std::make_shared<PolygonSampler>(a, b, c);
}

bool Polygon::intersectBounding(const Ray3<double> &ray) const
{
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);

    return this->bounding->intersect(tmp);
}

double Polygon::area(void) const
{
    return this->space;
}

const ShapeSampler &Polygon::getSampler(void) const
{
    return *this->sampler;
}

const Attribute &Polygon::getAttribute(void) const
{
    return Polygon::ATTRIBUTE();
}

Intersection Polygon::intersect(const Ray3<double> &ray) const
{
    Intersection out = Intersection();

    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);

    tools::intersection_res_t res = tools::intersect_plane(*this->center,
                                                           *this->normal,
                                                           tmp);

    if (!res.valid || FLT_EPSILON > res.t)
        return out;

    Point3<double> point = tmp(res.t);

    Vector3<double> dir = *this->center > point;
    bool valid = true;

    for (size_t i = 0; valid && 3 > i; i++)
        if (((*this->normals[i]) & dir) > this->lnormalssqr[i])
            valid = false;

    if (valid)
    {
        Vector3<double> a = *(this->points[0]) > *(this->points[1]);
        Vector3<double> n = a * Vector3<double>(*this->normal);

        Vector3<double> v = *(this->points[2]) > point;

        double t = - ((*(this->points[0]) > *(this->points[2])) & n) / (v & n);
        double k = distance(*(this->points[0]), (*(this->points[2]) + v * t)) \
                   / a.length();

        Point2<double> uv;

        if (FLT_EPSILON < fabs(t))
            uv = *this->pointsuv[0] \
                 + (*(this->pointsuv[0]) > *(this->pointsuv[1])) * k / t \
                 + (*(this->pointsuv[0]) > *(this->pointsuv[2])) * (t - 1) / t;

        out = Intersection(this, point, uv, *(this->normal_in),
                           res.t, *this->transform_global);
    }

    return out;
}

void Polygon::apply(const Transform<double, 3> &transform)
{
    this->center->apply(transform);

    for (size_t i = 0; 3 > i; i++)
    {
        this->normals[i]->apply(transform);
        this->lnormalssqr[i] = this->normals[i]->lengthSqr();
        this->points[i]->apply(transform);
    }

    this->normal_in->apply(transform);
    this->normal->apply(transform);

    this->bounding->apply(transform);
    this->sampler->apply(transform);
}

void Polygon::undo(const Transform<double, 3> &transform)
{
    for (size_t i = 0; 3 > i; i++)
    {
        this->normals[i]->undo(transform);
        this->lnormalssqr[i] = this->normals[i]->lengthSqr();
        this->points[i]->undo(transform);
    }

    this->normal_in->undo(transform);
    this->normal->undo(transform);

    this->bounding->undo(transform);
    this->sampler->undo(transform);
}

