#include <QApplication>

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

int main(int argc, char **argv)
// int main(void)
{
    QApplication app (argc, argv);
    MainWindow window;

    window.show();

    return app.exec();

    // FilePolygonModelBuilder builder ("/storage/Downloads/obj/FinalBaseMesh.obj");;
    // std::shared_ptr<Shape> obj = builder.build();
    //  
    // return 0;
}

