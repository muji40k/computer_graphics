#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QSharedPointer>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QShowEvent>
#include <QVector>
#include <QList>
#include <QPair>
#include <QTimer>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "qcanvas.h"

#include "qt_display_adapter.h"
#include "split_display_decorator.h"
#include "scene.h"

#include "lighting.h"
#include "orthogonal_projector.h"
#include "pinhole_projector.h"
#include "thin_lens_projector.h"
#include "projection.h"

#include "shape.h"
#include "disk.h"
#include "polygon.h"
#include "sphere.h"
#include "cube.h"
#include "plane.h"
#include "cilinder.h"
#include "cone.h"
#include "tube.h"
#include "null_object.h"

typedef struct
{
    QImage *display;
    Scene  *scene;
    bool   *fin;
    size_t  cnt;
    size_t  progres;
} pdarg_t;

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
        QSharedPointer<Scene> scene = nullptr;
        bool needredraw = false;
        QList<QPair<QPoint, int>> list;
        std::list<std::shared_ptr<Shape>> shapes;
        std::list<std::shared_ptr<ShapeProperty>> properties;
        QTimer timer;

        bool start_draw = false;
        bool stop_draw = false;
        size_t progres;
        QImage screen;
        pdarg_t arg;
        pthread_t thread;

        void paintEvent(QPaintEvent *event);

    private slots:
        void timeout(void);
        void save(void);
};

#endif

