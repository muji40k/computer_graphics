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

#define SIZE 33

int main(int argc, char **argv)
// int main(void)
{
    // Transform<double, 3> t;
    // t.accept(RotateStrategyOX<double>(M_PI / 4));
    // // t.accept(RotateStrategyOY<double>(M_PI / 4));
    // Shape *p = new Polygon();
    // p->applyBasis(t);
    // Point3<double> origin ({0.5, 0.25, 0.5});
    // Vector3<double> direction ({0, 0, -1});
    //  
    // Ray3<double> r (origin, direction);
    // Intersection i = p->intersect(r);
    // Point3<double> n = i.getPoint();
    // n.apply(i.toGlobal());
    //  
    // std::cout << i << " " << n << std::endl;
    //  
    // delete p;
    //  
    // return 0;

    QApplication app (argc, argv);
    MainWindow window;

    window.show();

    return app.exec();
}

