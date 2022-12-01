#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QSharedPointer>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QShowEvent>
#include <QVector>
#include <QList>
#include <QPair>

#include "ui_mainwindow.h"
#include "qcanvas.h"

#include "shape.h"
#include "disk.h"
#include "polygon.h"
#include "sphere.h"
#include "cube.h"
#include "plane.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow(void) = default;

    public slots:
        // void canvas_clicked(QMouseEvent event);
        void canvas_clicked();

    private:
        QSharedPointer<Ui_MainWindow> ui = nullptr;
        QSharedPointer<QCanvas> canvas = nullptr;
        QSharedPointer<Shape> shape1 = nullptr;
        QSharedPointer<Shape> shape2 = nullptr;
        QSharedPointer<Shape> shape3 = nullptr;
        bool needredraw = false;
        QList<QPair<QPoint, int>> list;

        void paintEvent(QPaintEvent *event);
};

#endif

