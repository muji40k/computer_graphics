#include "mainwindow.h"
#include <cmath>

#include <iostream>
#include <math.h>
#include <pthread.h>

#include "transform_strategies.h"
#include "simple_shape_tracer.h"
#include "direct_light_tracer.h"

typedef struct
{
    BaseDisplayAdapter *display;
    Scene              *scene;
    bool               *fin;
} parg_t;

void *pdrawfunc(void *param)
{
    if (!param)
        pthread_exit(NULL);

    parg_t *arg = (parg_t *)param;

    DirectLightTracer ltracer (*arg->scene);
    SimpleShapeTracer stracer;
    Ray3<double> ray;
    Point3<double> tmp;
    Intersection inter;
    Intersection close;
    Intensity<> intensity;
    std::list<light_trace_t> trace;

    auto projectors = arg->scene->getProperties(Projector::ATTRIBUTE());
    std::shared_ptr<Projection> projection = std::static_pointer_cast<Projector>(projectors.front())->project(*arg->display);

    // std::cout << "w: " << arg->display->width() << ", h: " << arg->display->height() << std::endl;

    for (size_t i = 0; arg->display->width() > i; i++)
        for (size_t j = 0; arg->display->height() > j; j++)
        {
            // std::cout << "i: " << i << ", j: " << j << std::endl;
            ray = projection->spawnRay(i, j);
            close = Intersection();
            intensity = Intensity<>();

            // std::cout << "Attempt to find intersection" << std::endl;
            for (auto shape : *arg->scene)
            {
                inter = stracer.trace(*shape, ray);

                if (inter && (!close || (close && close.getT() < inter.getT())))
                    close = inter;
            }

            if (close)
            {
                // std::cout << "Intersection found" << std::endl;
                intensity = Intensity<>({55, 55, 55});
                // intensity = Intensity<>({0, 55, 0});
                tmp = close.getPoint();
                tmp.apply(close.toGlobal());
                trace = ltracer.trace(tmp);

                for (light_trace_t &t : trace)
                {
                    Vector3<double> &cur = t.direction, norm (close.getNormal());
                    norm.apply(close.toGlobal());
                    Vector3<double> ref = 2 * (cur & norm) / norm.lengthSqr() * norm - cur;

                    double fraca = (cur & norm) / norm.length();
                    double fracs = pow(((-ray.getDirection().normalised()) & ref.normalised()), 3);
                    intensity += t.intensity * (0.2 * fraca + 0.8 * fracs);
                }

                intensity[0] *= 0.8;
                intensity[1] *= 1;
                intensity[2] *= 0.8;
            }

            arg->display->setAt(i, j, intensity);
        }

    // QColor color;
    // Point3<double> start ({arg->startx, 0, arg->offset});
    // Point3<double> base ({0, 0, 5 * arg->offset});
    // Point3<double> res;
    // Point3<double> ls ({-1.75, 1.75, 5.75});
    // Vector3<double> dir ({0, 0, -1});
    // Vector3<double> ref;
    // Ray3<double> ray;
    // Ray3<double> ray2;
    // Intersection inter;
    // double valr, valg, valb;
    // Vector3<double> cur, norm;
    // SimpleShapeTracer tracer;
    //  
    // for (size_t i = 0; arg->lx > i; i++)
    // {
    //     start.x = start.x + arg->step;
    //     start.y = arg->starty;;
    //  
    //     for (size_t j = 0; arg->ly > j; j++)
    //     {
    //         start.y = start.y + arg->step;
    //         ray.setOrigin(start);
    //         dir = base > start;
    //         ray.setDirection(dir);
    //         inter = tracer.trace(*arg->shape, ray);
    //         // inter = arg->shape->intersect(ray);
    //  
    //         if (inter)
    //         {
    //             res = inter.getPoint();
    //             res.apply(inter.toGlobal());
    //             norm = inter.getNormal();
    //             norm.apply(inter.toGlobal());
    //  
    //             cur = ls < res;
    //             ray2.setOrigin(res);
    //             ray2.setDirection(cur);
    //  
    //             ref = 2 * (cur & norm) / norm.lengthSqr() * norm - cur;
    //  
    //             // inter = arg->shape->intersect(ray2);
    //             inter = tracer.trace(*arg->shape, ray2);
    //  
    //             if (inter && 1 - FLT_EPSILON > inter.getT() && FLT_EPSILON < inter.getT())
    //             {
    //                 valg = 1 * (55);
    //                 valr = 0.6 * (55);
    //                 valb = 0.6 * (55);
    //             }
    //             else
    //             {
    //                 if (0 > (cur & norm))
    //                     norm *= -1;
    //  
    //                 double suma = 5000;
    //                 double sums = 1000;
    //  
    //                 double d = distance(ls, res);
    //                 d = 1 / (d * d);
    //                 double fraca = (cur.normalised() & norm.normalised()) * d;
    //                 double fracs = pow(((-dir.normalise()) & ref.normalised()), 3) * d;
    //                 int frac = 0.3 * suma * fraca + 0.8 * sums * fracs;
    //                 if (frac > 205)
    //                     frac = 205;
    //                 // valg = (cur.normalised() & norm.normalised()) * double(400) / (d * d) + pow(((-dir.normalise()) & ref.normalised()), 3) * double(400) / (d * d) + 55;
    //                 // valg = (cur.normalised() & norm.normalised()) * double(200) / (d * d) + 55;
    //                 valg = 1 * (1 * frac + 55);
    //                 valr = 0.6 * (1 * frac + 55);
    //                 valb = 0.6 * (1 * frac + 55);
    //             }
    //  
    //             // if (!inter || (inter && (FLT_EPSILON > fabs(inter.getT()) || inter.getT() > 1)))
    //             // {
    //             //     if (0 > (cur & norm))
    //             //         norm *= -1;
    //             //  
    //             //     double d = distance(ls, res);
    //             //     valg = (cur.normalised() & norm.normalised()) * double(200) / (d * d) + 55;
    //             //     valr = valb = 55;
    //             // }
    //             // else
    //             //     valr = valg = valb = 25;
    //         }
    //         else
    //             valr = valg = valb = 0;
    //  
    //         if (valg > 255 || 0 > valg)
    //             valg = 255;
    //  
    //         color.setRgb(valr, valg, valb);
    //         arg->image->setPixelColor(arg->sx + i, arg->sy + arg->ly - j - 1, color);
    //     }
    // }

    // pthread_exit(NULL);
    // std::cout << "End: " << arg->i << " " << arg->j << std::endl;
    *arg->fin = false;
    return NULL;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_MainWindow()), canvas(new QCanvas(this)), 
      scene(new Scene())
{
    this->ui->setupUi(this);

    this->ui->verticalLayout_2->insertWidget(0, this->canvas.get());

    Point3<double> center;

    std::shared_ptr<Shape> shape1;
    std::shared_ptr<Shape> shape2;
    std::shared_ptr<Shape> shape3;
    std::shared_ptr<Shape> camera;
    std::shared_ptr<Shape> lighting;
    std::shared_ptr<Shape> lighting2;

    Transform<double, 3> trans;
    Transform<double, 3> trans2;
    Transform<double, 3> trans3;
    // trans2.accept(RotateStrategyOX<double>(M_PI / 2));
    trans2.accept(MoveStrategy<double>({-1.5, 0, 2}));
    // trans.accept(RotateStrategyOX<double>(-M_PI / 2.3));

    // shape1.reset(new Disk(center, Normal3<double>({0, 0.7, 0.7}), 5));
    // shape1.reset(new Disk(center, Vector3<double>({0, 0.7, 0.7}), 5));
    // shape1.reset(new Cilinder(Vector3<double>({0, 0.7, 0.7}), center, 5, 2));
    shape1.reset(new Cone(Vector3<double>({0, 0.7, 0.7}), center, 5, 2));
    // shape2.reset(new Cilinder(Vector3<double>({0.7, 0.7, 0}), center, 5, 2));
    // shape1.reset(new Tube(Vector3<double>({0, 0.7, 0.7}), center, 5, 2));
    // shape2.reset(new Tube(Vector3<double>({0.7, 0.7, 0}), center, 5, 2));
    // shape1.reset(new Cilinder(Vector3<double>({0,0,1}), center, 5, 2));
    // shape1.reset(new Plane(center, Vector3<double>({1, 0, 0}), Vector3<double>({0, 0.7, -0.7}), 100, 100));
    shape2.reset(new Cube(4, 3, 2));
    // shape2.reset(new Sphere(center, 2));
    // shape1.reset(new Cube(4, 3, 2));
    // shape2.reset(new Polygon());
    // shape3.reset(new Sphere(center, 2.25));
    // shape3.reset(new Cube(4, 3, 2));

    shape1->add(shape2.get());
    // shape1->add(shape3.get());

    // this->shape1->applyBasis(trans2);
    // shape2->applyBasis(trans2);
    // trans2.accept(MoveStrategy<double>({0, 0, -4.5}));
    // this->shape1->applyBasis(trans2);
    // trans2.accept(MoveStrategy<double>({0, 0, 2.5}));
    // this->shape3->applyBasis(trans2);

    // QObject::connect(this->canvas.get(), SIGNAL(clicked(QMouseEvent)),
    //                  this, SLOT(canvas_clicked(QMouseEvent)));

    this->shapes.push_back(shape1);
    this->shapes.push_back(shape2);
    // this->shapes.push_back(shape3);
    this->scene->add(shape1);

    camera.reset(new NullObject());
    lighting.reset(new NullObject());
    lighting2.reset(new NullObject());

    trans.accept(MoveStrategy<double>({-5, 5, 4}));
    lighting->applyBasis(trans);
    trans.accept(MoveStrategy<double>({10, -10, 0}));
    lighting2->applyBasis(trans);
    trans.accept(MoveStrategy<double>({-5, 5, 4}));
    trans3.accept(MoveStrategy<double>({0, 0, 5}));
    camera->applyBasis(trans3);

    this->shapes.push_back(lighting);
    this->shapes.push_back(lighting2);
    this->shapes.push_back(camera);
    this->scene->add(lighting);
    this->scene->add(lighting2);
    this->scene->add(camera);

    std::shared_ptr<ShapeProperty> light_prop (new Lighting(lighting.get(), Intensity<>({5000, 5000, 5000})));
    // std::shared_ptr<ShapeProperty> light_prop (new Lighting(lighting.get(), Intensity<>({5000, 0, 0})));
    std::shared_ptr<ShapeProperty> proj_prop (new PinholeProjector(camera.get(), 10));
    std::shared_ptr<ShapeProperty> light_prop2 (new Lighting(lighting2.get(), Intensity<>({5000, 5000, 0})));
    // std::shared_ptr<ShapeProperty> light_prop2 (new Lighting(lighting2.get(), Intensity<>({0, 0, 5000})));

    this->scene->addProperty(light_prop);
    this->scene->addProperty(light_prop2);
    this->scene->addProperty(proj_prop);

    QObject::connect(this->ui->pushButton, SIGNAL(clicked()),
                     this, SLOT(canvas_clicked()));
}

void MainWindow::canvas_clicked()
{
    Transform<double, 3> trans;
    trans.accept(RotateStrategyOY<double>(M_PI / 12));
    this->shapes.front()->applyBasis(trans);
    this->needredraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    if (this->needredraw)
    {
        QPixmap *pixmap = *this->canvas;
        QPainter painter (pixmap);
        pixmap->fill(Qt::transparent);

        std::cout << "start" << std::endl;

        const size_t cnt = this->ui->spinBox_threads->value();

        pthread_t tids[12];
        pthread_attr_t tattrs[12];
        parg_t args[12];
        bool active[12] = {false};
        std::list<SplitDisplayDecorator> displays;

        size_t _lx = this->canvas->width(), _ly = this->canvas->height();
        size_t scale = this->ui->spinBox_scale->value();
        size_t lx = _lx / scale, ly = _ly / scale;
        QImage image = QImage(lx, ly, QImage::Format_RGBA64);
        QtDisplayAdapter display (image);

        double aspect = (double)ly / lx;

        display.setOffset(-4, 8 * aspect / 2);
        display.setRealWidth(8);

        size_t stepx = lx / cnt;
        size_t stepy = ly / cnt;
        size_t act = 0;

        // std::cout << "w: " << display.width() << " h: " << display.height() << std::endl;

        for (size_t i = 0; cnt > i; i++)
            for (size_t j = 0; cnt > j; j++)
            {
                for (; active[act]; act = (act + 1) % cnt);

                displays.push_back(SplitDisplayDecorator(display, i * stepx, j * stepy, stepx, stepy));
                args[act].display = &displays.back();
                args[act].scene = this->scene.get();
                args[act].fin = active + act;
                *args[act].fin = true;

                pthread_attr_init(tattrs + act);
                pthread_create(tids + act, tattrs + act, pdrawfunc, args + act);
            }

        for (size_t i = 0; cnt > i; i++)
            pthread_join(tids[i], NULL);

        // for (size_t i = 0; cnt > i; i++)
        // {
        //     // displays.push_back(SplitDisplayDecorator(display, i * stepx, 0, stepx, ly));
        //     displays.push_back(SplitDisplayDecorator(display, 0, i * stepy, lx, stepy));
        //     args[i].display = &displays.back();
        //     args[i].scene = this->scene.get();
        //  
        //     pthread_attr_init(tattrs + i);
        //     pthread_create(tids + i, tattrs + i, pdrawfunc, args + i);
        //     // pdrawfunc(args + i);
        // }
        //  
        // for (size_t i = 0; cnt > i; i++)
        //     pthread_join(tids[i], NULL);

        std::cout << "done" << std::endl;

        painter.drawImage(0, 0, image.scaled(_lx, _ly));
        this->needredraw = false;
    }

    this->canvas->update();
}

// void MainWindow::paintEvent(QPaintEvent *event)
// {
//     QMainWindow::paintEvent(event);
//  
//     if (this->needredraw)
//     {
//         QPixmap *pixmap = *this->canvas;
//         QPainter painter (pixmap);
//         QColor color;
//         pixmap->fill(Qt::transparent);
//  
//         double offset = 4;
//         // size_t lx = this->canvas->width(), ly = this->canvas->height();
//         size_t lx = 640, ly = 360;
//         double aspect = double(lx) / ly;
//         double dy = 5;
//         double dx = dy * aspect;
//         double step =  2 * dy / ly;
//         Point3<double> start ({-dx, 0, offset});
//         Point3<double> res;
//         Vector3<double> dir ({0, 0, -1});
//         Ray3<double> ray;
//         Intersection inter;
//         double val, valr;
//         ray.setDirection(dir);
//  
//         for (size_t i = 0; lx > i; i++)
//         {
//             start.x = start.x + step;
//             start.y = -dy;
//  
//             for (size_t j = 0; ly > j; j++)
//             {
//                 start.y = start.y + step;
//                 ray.setOrigin(start);
//                 inter = this->shape1->intersect(ray);
//  
//                 if (inter)
//                 {
//                     res = inter.getPoint();
//                     res.apply(inter.toGlobal());
//                     double d = distance(start, res);
//                     valr = double(200) / (d * d) + 55;
//  
//                     if (this->shape2.get() == inter.getShape())
//                         val = 0;
//                     else
//                         val = valr;
//                 }
//                 else
//                     val = (valr = 0);
//  
//                 color.setRgb(valr, val, val);
//                 painter.setPen(color);
//                 painter.drawPoint(i, lx - j);
//                 // std::cout << i << " " << j << std::endl;
//             }
//         }
//  
//         this->needredraw = false;
//     }
//  
//     this->canvas->update();
// }

void draw_line(QPixmap &pixmap, QColor color,
               QPair<QPointF, int> start, QPair<QPointF, int> end)
{
    int len = (int)end.first.x() - (int)start.first.x();

    int dx = 1;

    if (0 > len)
    {
        len *= -1;
        dx = -1;
    }

    double dint = (double)(end.second - start.second) / len;

    QPoint current (start.first.x(), end.first.y());
    QColor col (color);
    double intensity = start.second;
    QPainter painter (&pixmap);

    for (; 0 <= len; len--)
    {
        col.setAlpha(255 - int(intensity));
        painter.setPen(col);
        painter.drawPoint(current);

        intensity += dint;
        current.setX(current.x() + dx);
    }
}

typedef struct
{
    QPointF current;
    double intensity;
    double dx;
    double dint;
    int len;
} edge_t;

void fill_polygon(QPixmap &pixmap, QColor color, QList<QPair<QPoint, int>> list)
{
    QList<edge_t> edges;
    QPair<int, int> bounds (pixmap.height(), 0);
    edge_t tmp;

    for (int i = 0, j = 0, k = 0; list.size() > i; i++)
    {
        if (list[i].first.y() < bounds.first)
            bounds.first = list[i].first.y();

        if (list[i].first.y() > bounds.second)
            bounds.second = list[i].first.y();

        j = (i + 1) % list.size();

        if (0 == list[j].first.y() - list[i].first.y())
            continue;

        if (list[j].first.y() > list[i].first.y())
            k = j;
        else
            k = i;

        tmp.current.setX(list[k].first.x());
        tmp.current.setY(list[k].first.y());
        tmp.intensity = list[k].second;
        tmp.len = list[k].first.y() - list[i + j - k].first.y();
        tmp.dx = (double)(list[i + j - k].first.x() - list[k].first.x()) / tmp.len;
        tmp.dint = (double)(list[i + j - k].second - list[k].second) / tmp.len;

        edges.push_back(tmp);
    }

    QList<edge_t> active;

    for (int y = bounds.second; bounds.first < y; y--)
    {
        for (int i = 0; edges.size() > i; i++)
            if (edges[i].current.y() >= y)
            {
                active.push_back(edges[i]);
                edges.removeAt(i--);
            }

        if (2 < active.size())
            return;

        if (2 == active.size())
            draw_line(pixmap, color,
                      QPair<QPointF, int>(active[0].current, active[0].intensity),
                      QPair<QPointF, int>(active[1].current, active[1].intensity));

        for (int i = 0; active.size() > i; i++)
        {
            active[i].current.setX(active[i].current.x() + active[i].dx);
            active[i].current.setY(active[i].current.y() - 1);
            active[i].intensity += active[i].dint;
            active[i].len--;

            if (0 == active[i].len)
                active.removeAt(i--);
        }
    }
}

// void draw_grid(QPixmap &pixmap, QVector<QVector<int>> grid)
// {
//     QList edges
// }



#include "moc_mainwindow.cpp"

