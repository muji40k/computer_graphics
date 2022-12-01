#include "bounding_rectangle.h"

#define EPS 1e-8

BoundingRectangle::BoundingRectangle(const Point3<double> &start)
{
    this->low = start;
    this->high = start;
}

BoundingRectangle::BoundingRectangle(const BoundingRectangle &bounding)
    : low(bounding.low), high(bounding.high) {}

BoundingRectangle::BoundingRectangle(BoundingRectangle &&bounding)
    : low(bounding.low), high(bounding.high) {}

BoundingRectangle::~BoundingRectangle(void) {}

void BoundingRectangle::expand(const Point3<double> &point)
{
    for (size_t i = 0; 3 > i; i++)
    {
        this->high[i] = std::max(this->high[i], point[i]);
        this->low[i] = std::min(this->low[i], point[i]);
    }
}

void BoundingRectangle::expand(const std::list<Point3<double>> &points)
{
    for (const Point3<double> &point : points)
        for (size_t i = 0; 3 > i; i++)
        {
            this->high[i] = std::max(this->high[i], point[i]);
            this->low[i] = std::min(this->low[i], point[i]);
        }
}

std::list<Point3<double>> BoundingRectangle::farest(const Point3<double> &point) const
{
    std::list<Point3<double>> lst;

    Point3<double> current;
    double dist, current_dist = distance(this->low, point);

    for (size_t i = 0; 2 > i; i++)
        for (size_t j = 0; 2 > j; j++)
            for (size_t k = 0; 2 > k; k++)
            {
                current = this->combine(i, j, k);
                dist = distance(point, current);

                if (EPS > fabs(dist - current_dist))
                    lst.push_back(current);
                else if (dist > current_dist)
                {
                    lst.clear();
                    lst.push_back(current);
                    current_dist = dist;
                }
            }

    return lst;
}

std::list<Point3<double>> BoundingRectangle::nearest(const Point3<double> &point) const
{
    std::list<Point3<double>> lst;

    Point3<double> current;
    double dist, current_dist = distance(this->low, point);

    for (size_t i = 0; 2 > i; i++)
        for (size_t j = 0; 2 > j; j++)
            for (size_t k = 0; 2 > k; k++)
            {
                current = this->combine(i, j, k);
                dist = distance(point, current);

                if (EPS > fabs(dist - current_dist))
                    lst.push_back(current);
                else if (dist < current_dist)
                {
                    lst.clear();
                    lst.push_back(current);
                    current_dist = dist;
                }
            }

    return lst;
}

bool BoundingRectangle::isInside(const Point3<double> &point) const
{
    bool mark = true;

    for (size_t i = 0; mark && 3 > i; i++)
        mark = this->low[i] < point[i] && point[i] < this->high[i];

    return mark;
}

bool BoundingRectangle::intersect(const Ray3<double> &ray) const
{
    static const size_t map[6][4][3] = {
                                        {{0, 0, 0}, {0, 1, 0}, {0, 1, 1}, {0, 0, 1}},
                                        {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}},
                                        {{0, 0, 0}, {0, 0, 1}, {1, 0, 1}, {1, 0, 0}},
                                        {{1, 1, 1}, {0, 1, 1}, {0, 1, 0}, {1, 1, 0}},
                                        {{1, 1, 1}, {1, 0, 1}, {0, 0, 1}, {0, 1, 1}},
                                        {{1, 1, 1}, {1, 1, 0}, {1, 0, 0}, {1, 0, 1}}
                                       };

#define APPLY_MAP(i, j) map[i][j][0], map[i][j][1], map[i][j][2]

    bool mark = true;
    Point3<double> points[3], found;
    Vector3<double> va, vb, normal;
    double tmp, t;

    for (size_t i = 0; mark && 6 > i; i++)
    {
        for (size_t j = 0; 3 > j; j++)
            points[j] = this->combine(APPLY_MAP(i, j));

        va = points[1] > points[0];
        vb = points[1] > points[2];
        normal = va * vb;

        tmp = ray.getDirection() & normal;

        if (EPS > fabs(tmp))
            continue;

        t = ((points[0] < ray.getOrigin()) & normal) / tmp;

        if (0 > t)
            continue;

        found = ray(t);

        for (size_t j = 0, k; mark && 4 > j; j++)
        {
             k = (j + 1) % 4;
             va = points[j] > points[k];
             vb = points[j] > found;

             if (0 > (va & vb))
                 mark = false;
        }
    }

    return mark;

#undef APPLY_MAP
}

Point3<double> BoundingRectangle::combine(const size_t i, const size_t j,
                                          const size_t k) const
{
    return Point3<double>((*this)[i].x, (*this)[j].y, (*this)[k].z);
}

Point3<double> &BoundingRectangle::operator [] (const size_t i)
{
    size_t _i = i % 2;

    if (_i)
        return this->high;

    return this->low;
}

const Point3<double> &BoundingRectangle::operator [] (const size_t i) const
{
    size_t _i = i % 2;

    if (_i)
        return this->high;

    return this->low;
}

