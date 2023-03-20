#include <QApplication>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "mainwindow.h"
#include <iostream>
#include <math.h>
#include "point.h"
#include "vector.h"
#include "normal.h"
#include "ray.h"
#include "basis.h"
#include "transform.h"
#include "transform_strategies.h"
#include "matrix.h"
#include "attribute.h"
#include "polygon.h"
#include "intersection.h"

#include "null_object.h"
#include "projector.h"
#include "projection.h"

#include "orthogonal_projector.h"
#include "orthogonal_projection.h"

#include "pinhole_projector.h"
#include "pinhole_projection.h"

#include "base_display_adapter.h"

#include <memory>
#include "file_polygon_model_builder.h"

// #include "solid_texture.h"
#include "array_texture.h"

#include <unordered_map>
#include <map>

#include "tools.h"

std::ostream &operator << (std::ostream &stream, const Attribute &attr)
{
    for (size_t i = 0; 10 > i; i++)
        stream << attr(i);

    return stream;
}

#include "vector.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    MainWindow window;

    window.show();

    return app.exec();
}
