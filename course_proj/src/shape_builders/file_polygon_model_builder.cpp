#include "file_polygon_model_builder.h"
#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include "point.h"
#include "normal.h"
#include "polygon.h"
#include "polygon_model.h"
#include "tools.h"

static Point3<double> parse_point(const std::vector<std::string> string);
static Normal3<double> parse_normal(const std::vector<std::string> string);

typedef struct
{
    size_t point;
    size_t normal;
} point_spec_t;

static std::vector<point_spec_t> parse_face(const std::vector<std::string> string);

FilePolygonModelBuilder::FilePolygonModelBuilder(const char *filename)
    : FileShapeBuilder(filename) {}

FilePolygonModelBuilder::~FilePolygonModelBuilder(void) {}

std::shared_ptr<Shape> FilePolygonModelBuilder::build(void)
{
    std::vector<Point3<double>> points;
    std::vector<Normal3<double>> normals;
    std::shared_ptr<PolygonModel> out = make_shared<PolygonModel>();

    bool read = true;
    std::string str;
    std::vector<std::string> line;

    while (read)
    {
        std::getline(this->file, str);

        if (this->file.eof())
            read = false;

        if (read)
        {
            line = tools::split(str, ' ');

            if (0 == line.size())
                continue;

            if ("v" == line[0])
                points.push_back(parse_point(line));
            else if ("vn" == line[0])
                normals.push_back(parse_normal(line));
            else if ("f" == line[0])
            {
                std::vector<point_spec_t> pts = parse_face(line);
                Normal3<double> avg;

                if (points.size() < pts[0].point)
                    throw CALL_EX(WrongFilePolygonModelBuilderException);

                for (size_t i = 0; pts.size() > i; i++)
                {
                    if (normals.size() < pts[i].normal)
                        throw CALL_EX(WrongFilePolygonModelBuilderException);

                    avg += normals[pts[i].normal - 1];
                }

                avg /= pts.size();

                for (size_t i = 1; pts.size() - 1 > i; i++)
                {
                    if (points.size() < pts[i + 1].point)
                        throw CALL_EX(WrongFilePolygonModelBuilderException);

                    out->add(points[pts[0].point - 1], points[pts[i].point - 1],
                             points[pts[i + 1].point - 1], avg);
                }
            }
            // else if ("vt" != line[0] && "vp" != line[0] && "l" == line[0]
            //          && "#" != line[0])
            //     throw CALL_EX(WrongFilePolygonModelBuilderException);
        }
    }

    return out;
}

static Point3<double> parse_point(const std::vector<std::string> string)
{
    Point3<double> out;

    if (string.size() < 4 || string.size() > 5)
        throw CALL_EX(WrongFilePolygonModelBuilderException);

    for (size_t i = 0; 3 > i; i++)
        out[i] = std::stod(string[i + 1]);

    if (5 == string.size())
        out /= std::stod(string[4]);

    return out;
}

static Normal3<double> parse_normal(const std::vector<std::string> string)
{
    Normal3<double> out;

    if (4 != string.size())
        throw CALL_EX(WrongFilePolygonModelBuilderException);

    for (size_t i = 0; 3 > i; i++)
        out[i] = std::stod(string[i + 1]);

    return out;
}

static std::vector<point_spec_t> parse_face(const std::vector<std::string> string)
{
    std::vector<point_spec_t> out;

    if (string.size() < 4)
    {
        for (size_t i = 0; string.size() > i; i++)
            std::cout << string[i] << " | ";

        std::cout << std::endl;
        throw CALL_EX(WrongFilePolygonModelBuilderException);
    }

    for (size_t i = 1; string.size() > i; i++)
    {
        out.push_back({});
        point_spec_t &spec = out.back();

        std::vector<std::string> items = tools::split(string[i], '/', false);

        if (3 != items.size())
            throw CALL_EX(WrongFilePolygonModelBuilderException);

        spec.point = std::stoll(items[0]);
        spec.normal = std::stoll(items[2]);
    }

    return out;
}

