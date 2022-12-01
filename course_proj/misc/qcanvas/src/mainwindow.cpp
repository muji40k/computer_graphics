#include "mainwindow.h"
#include <cmath>

#include <iostream>

void fill_polygon(QPixmap &pixmap, QColor color, QList<QPair<QPoint, int>> list);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_MainWindow()), canvas(new QCanvas(this))
{
    this->ui->setupUi(this);

    this->ui->verticalLayout_2->addWidget(this->canvas.get());

    QObject::connect(this->canvas.get(), SIGNAL(clicked(QMouseEvent)),
                     this, SLOT(canvas_clicked(QMouseEvent)));
}

void MainWindow::canvas_clicked(QMouseEvent event)
{
    this->list.push_back({event.pos(), int(((double)event.y() / this->canvas->height()) * 255)});
    this->needredraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    if (this->needredraw)
    {
        // QPainter painter (*this->canvas);
        //  
        // painter.setPen(Qt::black);
        // painter.setBrush(Qt::black);
        // painter.drawRect(0, 0, 400, 400);
        // painter.setPen(Qt::red);
        // painter.drawLine(100, 100, 300, 300);

        QPixmap *pixmap = *this->canvas;
        pixmap->fill(Qt::transparent);

        // fill_polygon(*pixmap, QColor(0, 0, 0),
        //              QList<QPair<QPoint, int>> ({
        //                                          {{100, 100}, 0},
        //                                          {{200, 250}, 255},
        //                                          {{390, 340}, 100},
        //                                          {{400, 350}, 0},
        //                                          {{390, 360}, 100},
        //                                          {{169, 450}, 255},
        //                                          {{109, 360}, 0},
        //                                          {{56, 304}, 100}
        //                                         }));

        if (2 < this->list.size())
            fill_polygon(*pixmap, QColor(255, 100, 100), this->list);

        this->needredraw = false;
    }

    this->canvas->update();

    // char c;
    // std::cin >> c;
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    std::cout << "show" << std::endl;

    this->needredraw = true;
    this->canvas->update();
}


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

