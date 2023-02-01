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

class NoneAdapter : public BaseDisplayAdapter
{
    public:
        virtual ~NoneAdapter(void) override {};
        virtual size_t width(void) const override { return 1920; };
        virtual size_t height(void) const override { return 1080; };
        virtual void setAt(size_t, size_t, const Intensity<> &) override {};
};

#include <exception>

class MyApplication : public QApplication
{
    public:
        MyApplication(int& argc, char** argv) :QApplication(argc, argv) {}

        bool notify(QObject *receiver, QEvent *event)
        {
            bool done = true;

            try
            {
                done = QApplication::notify(receiver, event);
            }
            catch (const std::exception &ex)
            {
                std::cout << ex.what() << std::endl;
            }

            return done;
        }
};

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

    MyApplication app (argc, argv);
    MainWindow window;

    window.show();

    return app.exec();

    // NullObject obj;
    // NoneAdapter adapter;
    // Transform<double, 3> trans;
    //  
    // adapter.setRealWidth(16);
    // adapter.setOffset(-8, 4.5);
    //  
    // trans.accept(MoveStrategy<double>({-1.5, 0, 2}));
    // trans.accept(RotateStrategyOX<double>(-M_PI / 2));
    // obj.applyBasis(trans);
    //  
    // std::shared_ptr<Projector> projector = std::make_shared<PinholeProjector>(&obj, 5);
    // std::shared_ptr<Projection> projection = projector->project(adapter);
    //  
    // Ray3<double> res;
    //  
    // for (size_t i = 0, j = 1, row, col; j; i++)
    // {
    //     std::cout << "[" << i << "] Enter i j: ";
    //  
    //     if (!(std::cin >> row >> col))
    //         j = 0;
    //     else
    //     {
    //         res = projection->spawnRay(row, col);
    //  
    //         std::cout << res.getOrigin() << std::endl;
    //         std::cout << res.getDirection() << std::endl;
    //  
    //         for (size_t k = 0; 10 > k; k++)
    //         {
    //             res = projection->sampleRay(row, col);
    //  
    //             std::cout << "\t{" << k << "}"<< std::endl << res.getOrigin() << std::endl << res.getDirection() << std::endl;
    //         }
    //     }
    //  
    //     std::cout << std::endl;
    // }
    //  
    // return 0;
}

