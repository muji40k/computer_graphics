#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <list>
#include <memory>

#include <QSharedPointer>
#include <QPaintEvent>
#include <QTimer>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "qcanvas.h"

#include "base_tab.h"

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

#include "material.h"
#include "material_property.h"

#include "renderer.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        using ThreadArg = struct
        {
            QImage *display;
            Scene  *scene;
            bool   *fin;
            size_t  cnt;
            size_t  progres;
            std::shared_ptr<RenderProgress> progress;
        };

        using Handle = struct
        {
            std::shared_ptr<Scene> scene;
            std::list<std::shared_ptr<Shape>> shapes;
            std::list<std::shared_ptr<ShapeProperty>> properties;
            std::list<std::shared_ptr<Material>> materials;
        };

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow(void) = default;

    public slots:
        void canvas_clicked();

    private:
        QSharedPointer<Ui_MainWindow> ui = nullptr;
        QSharedPointer<QCanvas> canvas = nullptr;
        QSharedPointer<Scene> scene = nullptr;
        QSharedPointer<BaseTab> tab_projector = nullptr;
        QSharedPointer<BaseTab> tab_material = nullptr;
        bool needredraw = false;
        std::list<std::shared_ptr<Shape>> shapes;
        std::list<std::shared_ptr<ShapeProperty>> properties;
        std::shared_ptr<Material> mat;
        std::shared_ptr<MaterialProperty> ralbedo;
        QTimer timer;

        bool start_draw = false;
        bool stop_draw = false;
        QImage screen;
        ThreadArg arg;
        pthread_t thread;

        void paintEvent(QPaintEvent *event);
        void setupScene(void);

    private slots:
        void timeout(void);
        void save(void);
};

#endif

