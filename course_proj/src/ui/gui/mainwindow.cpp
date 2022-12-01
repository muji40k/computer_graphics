#include "mainwindow.h"
#include <cmath>

#include <iostream>
#include <math.h>
#include <pthread.h>

#include "transform_strategies.h"

typedef struct
{
    QImage *image;
    Shape  *shape;
    double offset;
    double startx;
    double starty;
    double step;
    size_t sx;
    size_t sy;
    size_t lx;
    size_t ly;
} parg_t;

void *pdrawfunc(void *param)
{
    if (!param)
        pthread_exit(NULL);

    parg_t *arg = (parg_t *)param;

    QColor color;
    Point3<double> start ({arg->startx, 0, arg->offset});
    Point3<double> base ({0, 0, 8 * arg->offset});
    Point3<double> res;
    Point3<double> ls ({-1.75, 1.75, 5.75});
    Vector3<double> dir ({0, 0, -1});
    Vector3<double> ref;
    Ray3<double> ray;
    Ray3<double> ray2;
    Intersection inter;
    double valr, valg, valb;
    Vector3<double> cur, norm;

    for (size_t i = 0; arg->lx > i; i++)
    {
        start.x = start.x + arg->step;
        start.y = arg->starty;;

        for (size_t j = 0; arg->ly > j; j++)
        {
            start.y = start.y + arg->step;
            ray.setOrigin(start);
            dir = base > start;
            ray.setDirection(dir);
            inter = arg->shape->intersect(ray);

            if (inter)
            {
                res = inter.getPoint();
                res.apply(inter.toGlobal());
                norm = inter.getNormal();
                norm.apply(inter.toGlobal());

                cur = ls < res;
                ray2.setOrigin(res);
                ray2.setDirection(cur);

                ref = 2 * (cur & norm) / norm.lengthSqr() * norm - cur;

                inter = arg->shape->intersect(ray2);

                if (inter && 1 - FLT_EPSILON > inter.getT() && FLT_EPSILON < inter.getT())
                    valr = valg = valb = 55;
                else
                {
                    if (0 > (cur & norm))
                        norm *= -1;

                    double d = distance(ls, res);
                    valg = (cur.normalised() & norm.normalised()) * double(400) / (d * d) + pow(((-dir.normalise()) & ref.normalised()), 3) * double(400) / (d * d) + 55;
                    valr = valb = 55;
                }

                // if (!inter || (inter && (FLT_EPSILON > fabs(inter.getT()) || inter.getT() > 1)))
                // {
                //     if (0 > (cur & norm))
                //         norm *= -1;
                //  
                //     double d = distance(ls, res);
                //     valg = (cur.normalised() & norm.normalised()) * double(200) / (d * d) + 55;
                //     valr = valb = 55;
                // }
                // else
                //     valr = valg = valb = 25;
            }
            else
                valr = valg = valb = 0;

            if (valg > 255 || 0 > valg)
                valg = 255;

            color.setRgb(valr, valg, valb);
            arg->image->setPixelColor(arg->sx + i, arg->sy + arg->ly - j - 1, color);
        }
    }

    pthread_exit(NULL);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_MainWindow()), canvas(new QCanvas(this))
{
    this->ui->setupUi(this);

    this->ui->verticalLayout_2->insertWidget(0, this->canvas.get());
    Point3<double> center;
    Normal3<double> norm ({0, 0, 1});
    Transform<double, 3> trans;
    Transform<double, 3> trans2;
    trans2.accept(MoveStrategy<double>({0, 0, 3.25}));
    trans.accept(RotateStrategyOX<double>(-M_PI / 2.3));

    // this->shape1.reset(new Disk(center, norm, 3));
    this->shape1.reset(new Plane(center, Vector3<double>({1, 0, 0}), Vector3<double>({0, 1, 0}), 100, 100));
    this->shape2.reset(new Polygon());
    // this->shape3.reset(new Sphere(center, 1.5));
    this->shape3.reset(new Cube(2, 2, 1.25));

    this->shape1->add(this->shape2.get());
    this->shape1->add(this->shape3.get());

    this->shape1->applyBasis(trans);
    this->shape2->applyBasis(trans2);
    trans2.accept(MoveStrategy<double>({0, 0, -4.5}));
    this->shape1->applyBasis(trans2);
    trans2.accept(MoveStrategy<double>({0, 0, 2.5}));
    this->shape3->applyBasis(trans2);

    // QObject::connect(this->canvas.get(), SIGNAL(clicked(QMouseEvent)),
    //                  this, SLOT(canvas_clicked(QMouseEvent)));
    QObject::connect(this->ui->pushButton, SIGNAL(clicked()),
                     this, SLOT(canvas_clicked()));
}

void MainWindow::canvas_clicked()
{
    Transform<double, 3> trans;
    trans.accept(RotateStrategyOY<double>(M_PI / 12));
    this->shape1->applyBasis(trans);
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

        double offset = 3.5;
        size_t _lx = this->canvas->width(), _ly = this->canvas->height();
        size_t scale = this->ui->spinBox_scale->value();
        size_t lx = _lx / scale, ly = _ly / scale;
        double aspect = double(lx) / ly;
        QImage image = QImage(lx, ly, QImage::Format_RGBA64);
        double dy = 5;
        double dx = dy * aspect;
        double step =  2 * dy / ly;

        int istepx = lx / cnt;
        double sstepx = step * istepx;

        size_t ci = 0;
        double cs = -dx;

        for (size_t i = 0; cnt > i; i++)
        {
            args[i].image = &image;
            args[i].shape = this->shape1.get();
            args[i].offset = offset;
            args[i].startx = cs;
            args[i].starty = -dy;
            args[i].step = step;
            args[i].sx = ci;
            args[i].sy = 0;
            args[i].lx = istepx;
            args[i].ly = ly;

            pthread_attr_init(tattrs + i);
            pthread_create(tids + i, tattrs + i, pdrawfunc, args + i);

            cs += sstepx;
            ci += istepx;
        }

        for (size_t i = 0; cnt > i; i++)
            pthread_join(tids[i], NULL);

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

