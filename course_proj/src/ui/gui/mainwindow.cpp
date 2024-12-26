#include "mainwindow.h"
#include <cmath>

#include <QFileDialog>
#include <QColorDialog>

#include "qt_misc_functions.h"

#include "tab_projector.h"
#include "tab_material.h"

#include "form_material.h"
#include "form_preferences.h"

#include <iostream>
#include <math.h>
#include <pthread.h>

#include "qt_display_adapter.h"

#include "transform_strategies.h"

#include "file_polygon_model_builder.h"

#include "view_port_renderer.h"
#include "complete_renderer.h"
#include "parallel_render_decorator.h"

#include "hdr_display_linker.h"
#include "linear_display_transform.h"
#include "gamma_display_transform.h"

#include "tracer_info.h"
#include "tracer_max_depth.h"
#include "tracer_light_samples.h"

#include "complete_tracer_builder.h"

static void *paint_master(void *_arg);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_MainWindow()), canvas(new QCanvas(this))
{
    this->ui->setupUi(this);
    this->ui->mainLayout->addWidget(this->canvas.get(), 0, 0);

    this->vp_timer.start(100);
    this->complete_timer.start(100);

    QObject::connect(&this->vp_timer, SIGNAL(timeout()), this, SLOT(vp_timeout()));
    QObject::connect(&this->complete_timer, SIGNAL(timeout()), this, SLOT(complete_timeout()));

    QObject::connect(this->ui->pushButton_viewport, SIGNAL(clicked()),
                     this, SLOT(on_preview_clicked()));
    QObject::connect(this->ui->actionRun, SIGNAL(triggered()),
                     this, SLOT(complete_render_start()));

    QObject::connect(this->ui->listWidget_object, SIGNAL(itemClicked(QListWidgetItem *)),
                     this, SLOT(object_clicked(QListWidgetItem *)));
    QObject::connect(this->ui->listWidget_material, SIGNAL(itemClicked(QListWidgetItem *)),
                     this, SLOT(material_clicked(QListWidgetItem *)));
    QObject::connect(this->ui->listWidget_material, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
                     this, SLOT(material_double_clicked(QListWidgetItem *)));

    QObject::connect(this->ui->pushButton_material_add, SIGNAL(clicked()),
                     this, SLOT(material_add_clicked()));
    QObject::connect(this->ui->pushButton_material_delete, SIGNAL(clicked()),
                     this, SLOT(material_delete_clicked()));

    QObject::connect(this->ui->pushButton_object_delete, SIGNAL(clicked()),
                     this, SLOT(object_delete_clicked()));

    QObject::connect(this->ui->actionPreferences, SIGNAL(triggered()),
                     this, SLOT(action_preferences()));
    QObject::connect(this->ui->actionRun_in_viewport, SIGNAL(triggered()),
                     this, SLOT(action_run_in_viewport()));

    QObject::connect(this->ui->actionSphere, SIGNAL(triggered()),
                     this, SLOT(action_add_sphere_triggered()));
    QObject::connect(this->ui->actionCube, SIGNAL(triggered()),
                     this, SLOT(action_add_cube_triggered()));
    QObject::connect(this->ui->actionCilinder, SIGNAL(triggered()),
                     this, SLOT(action_add_cylinder_triggered()));
    QObject::connect(this->ui->actionCone, SIGNAL(triggered()),
                     this, SLOT(action_add_cone_triggered()));
    QObject::connect(this->ui->actionPlne, SIGNAL(triggered()),
                     this, SLOT(action_add_plane_triggered()));
    QObject::connect(this->ui->actionDisl, SIGNAL(triggered()),
                     this, SLOT(action_add_disk_triggered()));
    QObject::connect(this->ui->actionLoad_2, SIGNAL(triggered()),
                     this, SLOT(action_add_polygon_triggered()));
    QObject::connect(this->ui->actionCamera, SIGNAL(triggered()),
                     this, SLOT(action_add_camera_triggered()));
    QObject::connect(this->ui->actionNull_Object, SIGNAL(triggered()),
                     this, SLOT(action_add_null_object_triggered()));

    QObject::connect(this->ui->checkBox_ambient_lighting, SIGNAL(toggled(bool)),
                     this, SLOT(checkBox_ambient_lighting_clicked(bool)));
    QObject::connect(this->ui->checkBox_env_map, SIGNAL(toggled(bool)),
                     this, SLOT(checkBox_env_map_clicked(bool)));
    QObject::connect(this->ui->checkBox_emission, SIGNAL(toggled(bool)),
                     this, SLOT(checkBox_emission_clicked(bool)));

    QObject::connect(this->ui->pushButton_ambient_lighting_color, SIGNAL(clicked()),
                     this, SLOT(pushButton_ambient_lighting_color_clicked()));
    QObject::connect(this->ui->toolButton_env_map, SIGNAL(clicked()),
                     this, SLOT(toolButton_env_map_clicked()));
    QObject::connect(this->ui->pushButton_transform_apply, SIGNAL(clicked()),
                     this, SLOT(pushButton_transform_apply_clicked()));
    QObject::connect(this->ui->pushButton_emission_color, SIGNAL(clicked()),
                     this, SLOT(pushButton_emission_color_clicked()));

    this->initScene();
    this->refreshTabs();
}

MainWindow::~MainWindow(void)
{
    while (!this->tabs.empty())
    {
        delete this->tabs.front();
        this->tabs.pop_front();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    if (!this->complete_needredraw && this->vp_needredraw && !this->vp_start_draw)
    {
        size_t cnt = this->render_pref.viewport.threads;
        double scale = (double)this->render_pref.viewport.resolution / 100;

        size_t lx = this->canvas->width() * scale,
               ly = this->canvas->height() * scale;

        this->screen = QSharedPointer<QImage>::create(lx, ly, QImage::Format_RGBA64);
        // this->last_scene = this->buildScene();
        this->last_scene = build_scene(this->scene_handle);

        this->arg.render_pref = &this->render_pref;
        this->arg.projector = this->scene_handle.meta.projector;
        this->arg.display = this->screen.get();
        this->arg.scene = this->last_scene.get();
        this->arg.fin = &this->vp_stop_draw;
        this->arg.cnt = cnt;

        pthread_create(&this->thread, NULL, paint_master, &this->arg);

        this->vp_start_draw = true;
        this->vp_stop_draw = false;
    }
}

void MainWindow::showMaterialPref(material_t *material)
{
    this->form_material = QSharedPointer<FormMaterial>::create(material);
    this->form_material->show();
}

object_t MainWindow::getDefaultObj(std::string name)
{
    object_t out;

    out.name = name;
    out.shape = nullptr;
    out.material = nullptr;

    out.lighting.set = false;
    out.lighting.color = Intensity<>({1, 1, 1});
    out.lighting.power = 0;

    out.projector.set = false;
    out.projector.type = PINHOLE_PROJECTOR;
    out.projector.width = 1;

    out.projector.offset = 1;

    out.projector.aperture = 1;
    out.projector.autofocus = false;
    out.projector.focus = 1;

    return out;
}

void MainWindow::initScene(void)
{
    this->render_pref.viewport.resolution = 5;
    this->render_pref.viewport.threads = 2;

    this->render_pref.complete.filename = "unknown.png";
    this->render_pref.complete.width = 1280;
    this->render_pref.complete.height = 720;
    this->render_pref.complete.camera_samples = 1;
    this->render_pref.complete.light_samples = 100;
    this->render_pref.complete.max_depth = 5;
    this->render_pref.complete.threads = 2;

    this->action_add_camera_triggered();
    this->scene_handle.meta.projector = &this->scene_handle.objects.back();
    this->active_object = &this->scene_handle.objects.back();
    this->scene_handle.meta.projector->lighting.set = true;
    this->scene_handle.meta.projector->lighting.color = Intensity<>({1, 1, 1});
    this->scene_handle.meta.projector->lighting.power = 0.5;

    this->scene_handle.meta.ambient.set = false;
    this->scene_handle.meta.ambient.power = 0.3;
    this->scene_handle.meta.ambient.color = Intensity<>({1, 1, 1});

    this->scene_handle.meta.env_map_size = 10;
    this->scene_handle.meta.env_map.set = false;

    Transform<double, 3> trans;
    trans.accept(MoveStrategy<double, 3>({0, 0, 2}));

    this->scene_handle.objects.front().shape->applyBasis(trans);
}

void MainWindow::refreshTabs(void)
{
    if (!this->active_object)
        return;

    while (!this->tabs.empty())
    {
        delete this->tabs.front();
        this->tabs.pop_front();
    }

    if (this->active_object->projector.set)
        this->tabs.push_back(new TabProjector());
    else
        this->tabs.push_back(new TabMaterial());

    this->ui->tabWidget_props->addTab(this->tabs.back(), this->tabs.back()->getName());
    this->setFields();
}

void MainWindow::setFields(void)
{
    meta_t &meta = this->scene_handle.meta;

    this->ui->comboBox_active_projector->clear();

    size_t i = 0;
    size_t k = 0;

    for (object_t &object : this->scene_handle.objects)
        if (object.projector.set)
        {
            this->ui->comboBox_active_projector->addItem(object.name.c_str());

            if (&object == meta.projector)
                k = i;

            i++;
        }

    this->ui->comboBox_active_projector->setCurrentIndex(k);

    this->ui->checkBox_ambient_lighting->setChecked(meta.ambient.set);
    this->ui->doubleSpinBox_ambient_lighting->setValue(meta.ambient.power);
    setBackgroundColor(this->ui->label_ambient_lighting_color, meta.ambient.color);
    this->ambient_color.setRed(255 * meta.ambient.color[0]);
    this->ambient_color.setGreen(255 * meta.ambient.color[1]);
    this->ambient_color.setBlue(255 * meta.ambient.color[2]);

    this->ui->checkBox_env_map->setChecked(meta.env_map.set);
    this->ui->doubleSpinBox_env_map_size->setValue(meta.env_map_size);
    this->ui->lineEdit_env_map->setText(meta.env_map.texture_name.c_str());

    if (!this->active_object)
        return;

    this->ui->checkBox_emission->setChecked(this->active_object->lighting.set);
    this->ui->doubleSpinBox_emission->setValue(this->active_object->lighting.power);
    setBackgroundColor(this->ui->label_emission_color, this->active_object->lighting.color);
    this->emission_color.setRed(255 * this->active_object->lighting.color[0]);
    this->emission_color.setGreen(255 * this->active_object->lighting.color[1]);
    this->emission_color.setBlue(255 * this->active_object->lighting.color[2]);

    for (BaseTab *tab : this->tabs)
        tab->set(*this->active_object, this->scene_handle);
}

void MainWindow::getFields(void)
{
    meta_t &meta = this->scene_handle.meta;
    std::string projector = this->ui->comboBox_active_projector->currentText().toStdString();

    for (object_t &object : this->scene_handle.objects)
        if (object.name == projector)
            meta.projector = &object;

    meta.ambient.set = this->ui->checkBox_ambient_lighting->isChecked();
    meta.ambient.power = this->ui->doubleSpinBox_ambient_lighting->value();
    meta.ambient.color[0] = (double)this->ambient_color.red() / 255;
    meta.ambient.color[1] = (double)this->ambient_color.green() / 255;
    meta.ambient.color[2] = (double)this->ambient_color.blue() / 255;

    meta.env_map.set = this->ui->checkBox_env_map->isChecked();
    meta.env_map_size = this->ui->doubleSpinBox_env_map_size->value();
    meta.env_map.texture_name = this->ui->lineEdit_env_map->text().toStdString();

    if (!this->active_object)
        return;

    this->active_object->lighting.set = this->ui->checkBox_emission->isChecked();
    this->active_object->lighting.power = this->ui->doubleSpinBox_emission->value();
    this->active_object->lighting.color[0] = (double)this->emission_color.red() / 255;
    this->active_object->lighting.color[1] = (double)this->emission_color.green() / 255;
    this->active_object->lighting.color[2] = (double)this->emission_color.blue() / 255;

    for (BaseTab *tab : this->tabs)
        tab->save(*this->active_object, this->scene_handle);
}

void MainWindow::on_preview_clicked(void)
{
    if (this->complete_needredraw)
        return;

    if (this->vp_needredraw && this->vp_start_draw && !this->vp_stop_draw)
        pthread_cancel(this->thread);

    if (!this->vp_needredraw)
    {
        this->getFields();
        // this->cache();
        refresh_cache(this->scene_handle);
        this->render_pref.type = VIEWPORT;
        this->vp_needredraw = true;
        this->paintEvent(nullptr);
    }
}

void MainWindow::vp_timeout(void)
{
    if (this->vp_needredraw && this->vp_stop_draw)
    {
        QPixmap *pixmap = *this->canvas;
        QPainter painter (pixmap);
        pixmap->fill(Qt::transparent);

        painter.drawImage(0, 0, this->screen->scaled(this->canvas->width(),
                                                     this->canvas->height()));
        this->canvas->update();
        this->ui->label_status->setText(QString("Status: viewport progress - %1%").arg(this->arg.progress->progress() * 100));

        this->vp_needredraw = false;
        this->vp_start_draw = false;
    }
    else if (this->vp_needredraw && this->vp_start_draw && this->arg.progress)
        this->ui->label_status->setText(QString("Status: viewport progress - %1%").arg(this->arg.progress->progress() * 100));
}

void MainWindow::complete_timeout(void)
{
    if (this->complete_needredraw && this->complete_stop_draw)
    {
        if (DEST_SCREEN == this->render_pref.complete.destination)
        {
            QPixmap *pixmap = *this->canvas;
            QPainter painter (pixmap);
            pixmap->fill(Qt::transparent);

            painter.drawImage(0, 0, this->screen->scaled(this->canvas->width(),
                                                         this->canvas->height()));
            this->canvas->update();
            this->ui->label_status->setText(QString("Status: complete progress - %1%").arg(this->arg.progress->progress() * 100));
        }
        else if (DEST_FILE == this->render_pref.complete.destination)
        {
            this->screen->save(this->render_pref.complete.filename.c_str());
            this->ui->label_status->setText(QString("Status: render saved - %1").arg(this->render_pref.complete.filename.c_str()));
        }


        this->complete_needredraw = false;
        this->complete_start_draw = false;
    }
    else if (this->complete_needredraw && this->complete_start_draw && this->arg.progress)
        this->ui->label_status->setText(QString("Status: complete progress - %1%").arg(this->arg.progress->progress() * 100));
}

void MainWindow::complete_render_start(void)
{
    if (this->vp_needredraw && this->vp_start_draw && !this->vp_stop_draw)
        pthread_cancel(this->thread);

    if (!this->complete_needredraw)
    {
        this->render_pref.type = COMPLETE;
        this->render_pref.complete.destination = DEST_FILE;
        this->complete_needredraw = true;
        this->getFields();
        // this->cache();
        refresh_cache(this->scene_handle);

        size_t cnt = this->render_pref.complete.threads;
        size_t lx = this->render_pref.complete.width,
               ly = this->render_pref.complete.height;

        this->screen = QSharedPointer<QImage>::create(lx, ly, QImage::Format_RGBA64);
        // this->last_scene = this->buildScene();
        this->last_scene = build_scene(this->scene_handle);

        this->arg.render_pref = &this->render_pref;
        this->arg.projector = this->scene_handle.meta.projector;
        this->arg.display = this->screen.get();
        this->arg.scene = this->last_scene.get();
        this->arg.fin = &this->complete_stop_draw;
        this->arg.cnt = cnt;

        pthread_create(&this->thread, NULL, paint_master, &this->arg);

        this->complete_start_draw = true;
        this->complete_stop_draw = false;
    }
}

void MainWindow::object_clicked(QListWidgetItem *item)
{
    this->getFields();

    for (object_t &obj : this->scene_handle.objects)
        if (item->text() == QString(obj.name.c_str()))
        {
            this->active_object = &obj;
            this->refreshTabs();
            // this->setFields();
            return;
        }
}

void MainWindow::material_clicked(QListWidgetItem *item)
{
    for (material_t &mat : this->scene_handle.materials)
        if (item->text() == QString(mat.name.c_str()))
        {
            this->active_material = &mat;
            return;
        }
}

void MainWindow::material_double_clicked(QListWidgetItem *item)
{
    this->material_clicked(item);
    this->showMaterialPref(this->active_material);
}

void MainWindow::material_add_clicked(void)
{
    material_t mat;

    mat.name = std::string("Material ") + std::to_string(this->material_counter++);
    mat.albedo = 0.7;
    mat.ambient_attraction = 1.0;
    mat.ri = {1, 0};
    mat.texture.set = false;
    mat.texture.color = Intensity<>({1, 1, 1});

    mat.scattering.push_back({"Lambert", LAMBERT_DIFUSION, 0.7, 0});
    mat.scattering.push_back({"Phong", PHONG_SPECULAR, 0.3, 3});

    this->scene_handle.materials.push_back(mat);

    this->ui->listWidget_material->addItem(QString(mat.name.c_str()));
}

void MainWindow::material_delete_clicked(void)
{
    if (!this->active_material)
        return;

    QListWidgetItem *item = this->ui->listWidget_material->takeItem(this->ui->listWidget_material->currentRow());

    if (!item)
        return;

    for (auto iter = this->scene_handle.materials.begin();
         this->scene_handle.materials.end() != iter; iter++)
        if (item->text() == QString((*iter).name.c_str()))
        {
            this->scene_handle.materials.erase(iter);
            this->material_clicked(this->ui->listWidget_material->currentItem());
            return;
        }
}

void MainWindow::object_delete_clicked(void)
{
    if (!this->active_object)
        return;

    QListWidgetItem *item = this->ui->listWidget_object->takeItem(this->ui->listWidget_object->currentRow());

    if (!item)
        return;

    for (auto iter = this->scene_handle.objects.begin();
         this->scene_handle.objects.end() != iter; iter++)
        if (item->text() == QString((*iter).name.c_str()))
        {
            this->scene_handle.objects.erase(iter);
            this->object_clicked(this->ui->listWidget_object->currentItem());
            return;
        }
}

void MainWindow::action_preferences(void)
{
    this->form_preferences = QSharedPointer<FormPreferences>::create(&this->render_pref);
    this->form_preferences->show();
}

void MainWindow::action_run_in_viewport(void)
{
    if (this->vp_needredraw && this->vp_start_draw && !this->vp_stop_draw)
        pthread_cancel(this->thread);

    if (!this->complete_needredraw)
    {
        this->render_pref.type = COMPLETE;
        this->render_pref.complete.destination = DEST_SCREEN;
        this->complete_needredraw = true;
        this->getFields();
        // this->cache();
        refresh_cache(this->scene_handle);

        size_t cnt = this->render_pref.complete.threads;
        size_t lx = this->canvas->width(), ly = this->canvas->height();

        this->screen = QSharedPointer<QImage>::create(lx, ly, QImage::Format_RGBA64);
        // this->last_scene = this->buildScene();
        this->last_scene = build_scene(this->scene_handle);

        this->arg.render_pref = &this->render_pref;
        this->arg.projector = this->scene_handle.meta.projector;
        this->arg.display = this->screen.get();
        this->arg.scene = this->last_scene.get();
        this->arg.fin = &this->complete_stop_draw;
        this->arg.cnt = cnt;

        pthread_create(&this->thread, NULL, paint_master, &this->arg);

        this->complete_start_draw = true;
        this->complete_stop_draw = false;
    }
}

#include "sphere.h"
void MainWindow::action_add_sphere_triggered(void)
{
    object_t obj = getDefaultObj(std::string("Sphere ")
                                 + std::to_string(this->sphere_counter++));
    obj.shape = std::make_shared<Sphere>(0.5);
    this->scene_handle.objects.push_back(obj);
    this->ui->listWidget_object->addItem(QString(obj.name.c_str()));
}

#include "cube.h"
void MainWindow::action_add_cube_triggered(void)
{
    object_t obj = getDefaultObj(std::string("Cube ")
                                 + std::to_string(this->cube_counter++));
    obj.shape = std::make_shared<Cube>(1, 1, 1);
    this->scene_handle.objects.push_back(obj);
    this->ui->listWidget_object->addItem(QString(obj.name.c_str()));
}

#include "cilinder.h"
void MainWindow::action_add_cylinder_triggered(void)
{
    object_t obj = getDefaultObj(std::string("Cylinder ")
                                 + std::to_string(this->cylinder_counter++));
    obj.shape = std::make_shared<Cilinder>(1, 0.5);
    this->scene_handle.objects.push_back(obj);
    this->ui->listWidget_object->addItem(QString(obj.name.c_str()));
}

#include "cone.h"
void MainWindow::action_add_cone_triggered(void)
{
    object_t obj = getDefaultObj(std::string("Cone ")
                                 + std::to_string(this->cone_counter++));
    obj.shape = std::make_shared<Cone>(1, 0.5);
    this->scene_handle.objects.push_back(obj);
    this->ui->listWidget_object->addItem(QString(obj.name.c_str()));
}

#include "plane.h"
void MainWindow::action_add_plane_triggered(void)
{
    object_t obj = getDefaultObj(std::string("Plane ")
                                 + std::to_string(this->plane_counter++));
    obj.shape = std::make_shared<Plane>(1, 1);
    this->scene_handle.objects.push_back(obj);
    this->ui->listWidget_object->addItem(QString(obj.name.c_str()));
}

#include "disk.h"
void MainWindow::action_add_disk_triggered(void)
{
    object_t obj = getDefaultObj(std::string("Disk ")
                                 + std::to_string(this->disk_counter++));
    obj.shape = std::make_shared<Disk>(0.5);
    this->scene_handle.objects.push_back(obj);
    this->ui->listWidget_object->addItem(QString(obj.name.c_str()));
}


#include "file_polygon_model_builder.h"
void MainWindow::action_add_polygon_triggered(void)
{
    object_t obj = getDefaultObj(std::string("Polygon Model ")
                                 + std::to_string(this->polygon_model_counter++));

    QString filename = QFileDialog::getOpenFileName(this, "Open polygon model",
                                                    "", "Object (*.obj)");

    if ("" != filename)
    {
        try
        {
            obj.shape = FilePolygonModelBuilder(filename.toStdString().c_str()).build();
            this->scene_handle.objects.push_back(obj);
            this->ui->listWidget_object->addItem(QString(obj.name.c_str()));
        }
        catch (CommonFilePolygonModelBuilderException &e)
        {
            this->ui->label_status->setText((std::string("Status: wrong object file ") + filename.toStdString()).c_str());
        }
    }
}

#include "camera.h"
void MainWindow::action_add_camera_triggered(void)
{
    object_t obj = getDefaultObj(std::string("Camera ")
                                 + std::to_string(this->camera_counter++));
    obj.shape = std::make_shared<Camera>();
    obj.projector.set = true;
    this->scene_handle.objects.push_back(obj);
    this->ui->listWidget_object->addItem(QString(obj.name.c_str()));
}

#include "null_object.h"
void MainWindow::action_add_null_object_triggered(void)
{
    object_t obj = getDefaultObj(std::string("Null Object ")
                                 + std::to_string(this->null_object_counter++));
    obj.shape = std::make_shared<NullObject>();
    this->scene_handle.objects.push_back(obj);
    this->ui->listWidget_object->addItem(QString(obj.name.c_str()));
}

void MainWindow::checkBox_ambient_lighting_clicked(bool state)
{
    meta_t &meta = this->scene_handle.meta;

    meta.ambient.set = state;
    this->ui->frame_lighting->setVisible(state);
}

void MainWindow::checkBox_env_map_clicked(bool state)
{
    meta_t &meta = this->scene_handle.meta;

    meta.env_map.set = state;
    this->ui->frame_env_map->setVisible(state);
}

void MainWindow::checkBox_emission_clicked(bool state)
{
    lighting_t &light = this->active_object->lighting;

    light.set = state;
    this->ui->frame_emission->setVisible(state);
}

void MainWindow::pushButton_ambient_lighting_color_clicked(void)
{
    QColor tmp = QColorDialog::getColor();

    if (tmp.isValid())
    {
        this->ambient_color = tmp;
        setBackgroundColor(this->ui->label_ambient_lighting_color, this->ambient_color);
    }
}

void MainWindow::toolButton_env_map_clicked(void)
{
    QString filename = QFileDialog::getOpenFileName(this, "Open environmental map",
                                                    "",
                                                    "Images (*.png *.xpm *.jpg *.hdr)");

    if ("" != filename)
        this->ui->lineEdit_env_map->setText(filename);
}

void MainWindow::pushButton_transform_apply_clicked(void)
{
    if (!this->active_object)
        return;

    const Transform<double, 3> &toGlobal = this->active_object->shape->getBasisTransform();
    Point3<double> center;
    center.apply(toGlobal);

    Transform<double, 3> current;

    current.accept(MoveStrategy<double, 3>({-center.x, -center.y, -center.z}));
    current.accept(RotateStrategyOX<double>(this->ui->doubleSpinBox_rotate_x->value() / 180 * M_PI));
    current.accept(RotateStrategyOY<double>(this->ui->doubleSpinBox_rotate_y->value() / 180 * M_PI));
    current.accept(RotateStrategyOZ<double>(this->ui->doubleSpinBox_rotate_z->value() / 180 * M_PI));
    current.accept(MoveStrategy<double, 3>({center.x + this->ui->doubleSpinBox_move_x->value(),
                                            center.y + this->ui->doubleSpinBox_move_y->value(),
                                            center.z + this->ui->doubleSpinBox_move_z->value()}));
    current.accept(ScaleStrategy<double, 3>({this->ui->doubleSpinBox_scale_x->value(),
                                             this->ui->doubleSpinBox_scale_y->value(),
                                             this->ui->doubleSpinBox_scale_z->value()}));

    this->active_object->shape->applyBasis(current);
}

void MainWindow::pushButton_emission_color_clicked(void)
{
    QColor tmp = QColorDialog::getColor();

    if (tmp.isValid())
    {
        this->emission_color = tmp;
        setBackgroundColor(this->ui->label_emission_color, this->emission_color);
    }
}

static void *paint_master(void *_arg)
{
    MainWindow::ThreadArg *arg = (MainWindow::ThreadArg *)_arg;
    size_t cnt = arg->cnt;

    size_t lx = arg->display->width(), ly = arg->display->height();
    QtDisplayAdapter display (*arg->display);

    double aspect = (double)ly / lx;

    double width = arg->projector->projector.width;
    display.setOffset(-width / 2, width * aspect / 2);
    display.setRealWidth(width);

    arg->progress = std::make_shared<RenderProgress>(display);

    std::shared_ptr<Renderer> renderer = nullptr;

    if (VIEWPORT == arg->render_pref->type)
        renderer = std::make_shared<ViewPortRenderer>();
    else
    {
        TracerInfo info = TracerInfo().setProperty(std::make_shared<TracerMaxDepth>(arg->render_pref->complete.max_depth))
                                      .setProperty(std::make_shared<TracerLightSamples>(arg->render_pref->complete.light_samples));
        renderer = std::make_shared<CompleteRenderer>(CompleteTracerBuilder().build(info),
                                                      arg->render_pref->complete.camera_samples);
    }

    ParallelRendererDecorator rdecor (*renderer, cnt, cnt, cnt);
    HDRDisplayLinker linker (display);
    BaseDisplayAdapter &adapter = linker.getHDRAdapter();

    rdecor.render(*arg->scene, adapter, arg->progress.get());

    linker.apply(GammaDisplayTransform(2.2));
    *arg->fin = true;

    return NULL;
}

#include "moc_mainwindow.cpp"

