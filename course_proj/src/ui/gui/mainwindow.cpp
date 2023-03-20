#include "mainwindow.h"
#include <cmath>

#include "tab_projector.h"
#include "tab_material.h"

#include <iostream>
#include <math.h>
#include <pthread.h>

#include "transform_strategies.h"
#include "simple_scene_tracer.h"
#include "direct_light_tracer.h"
#include "sampling_light_tracer.h"

#include "file_polygon_model_builder.h"

#include "solid_texture.h"
#include "array_texture.h"

#include "image_array_texture_builder.h"
#include "light_array_texture_builder.h"

#include "uv_texture_mapper.h"
#include "spherical_texture_mapper.h"
#include "grid_texture_mapper.h"

#include "lambert_difusion_builder.h"
#include "phong_specular_builder.h"
#include "specular_reflection_builder.h"
#include "specular_transmission_builder.h"
#include "dielectric_reflection_builder.h"
#include "conductor_reflection_builder.h"
#include "fresnel_transmission_builder.h"

#include "scattering_scale.h"
#include "scattering_refraction_index.h"
#include "scattering_phong_alpha.h"

#include "ambient_lighting.h"
#include "scene_active_projector.h"

#include "view_port_renderer.h"
#include "complete_renderer.h"
#include "parallel_render_decorator.h"

#include "shape_material_linker.h"
#include "material_scattering.h"
#include "material_texture.h"
#include "material_albedo.h"
#include "material_refraction_index.h"
#include "material_ambient_attraction.h"

#include "spherical_map.h"

#include "hdr_display_linker.h"
#include "linear_display_transform.h"
#include "gamma_display_transform.h"

#include "tracer_info.h"
#include "tracer_max_depth.h"
#include "tracer_light_samples.h"

#include "complete_tracer_builder.h"
#include "test_builder.h"

std::mutex mut;

std::shared_ptr<Texture<Intensity<>>> texture = nullptr;
std::shared_ptr<Texture<Intensity<>>> envmap = nullptr;
std::shared_ptr<Texture<Vector3<double>>> bmap = nullptr;

void MainWindow::setupScene(void)
{
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
    Transform<double, 3> trans4;
    // trans2.accept(RotateStrategyOX<double>(M_PI / 2));
    trans2.accept(MoveStrategy<double>({-1.5, 0, 2}));
    // trans.accept(RotateStrategyOX<double>(-M_PI / 2.3));

    // shape1.reset(new Disk(2.5));
    // shape1.reset(new Sphere(0.5));
    // shape1.reset(new Tube(4, 2));
    // shape1.reset(new Plane(5, 5));
    // shape1.reset(new Disk(center, Vector3<double>({0, 1, 0}), 5));
    // shape1.reset(new Cube(2, 1.5, 1));
    // shape1.reset(new Disk(center, Vector3<double>({0, 0.7, 0.7}), 5));
    shape1.reset(new Cilinder(1, 0.5));
    // shape1.reset(new Cilinder(5, 4));
    // shape1.reset(new Cone(5, 2));
    // shape1.reset(new Polygon());
    // shape1.reset(new Polygon(Point3<double>({4, 0, 0}), Point3<double>({0, 0, 0}),
    //                          Point3<double>({0, 0, 4}), Normal3<double>({0,1,0}),
    //                          Point2<double>({1, 0}), Point2<double>({0.5, 1}), Point2<double>({0, 0.5})));
    // shape2.reset(new Cilinder(Vector3<double>({0.7, 0.7, 0}), center, 5, 2));
    // shape1.reset(new Tube(Vector3<double>({0, 0.7, 0.7}), center, 5, 2));
    // shape2.reset(new Tube(Vector3<double>({0.7, 0.7, 0}), center, 5, 2));
    // shape1.reset(new Cilinder(Vector3<double>({0,0,1}), center, 5, 2));
    // shape1.reset(new Plane(center, Vector3<double>({1, 0, 0}), Vector3<double>({0, 0.7, -0.7}), 100, 100));
    // shape2.reset(new Cube(4, 3, 2));
    // shape2.reset(new Sphere(2));
    // shape1.reset(new Cube(4, 3, 2));
    // shape2.reset(new Polygon());
    // shape3.reset(new Sphere(center, 2.25));
    // shape3.reset(new Cube(4, 3, 2));
    // shape3.reset(new Plane(center, Vector3<double>({0, -1, 0}), Vector3<double>({0, 0, 1}), 100, 100));
    // FilePolygonModelBuilder builder ("/storage/Downloads/obj/Lowpoly_tree_sample.obj");;
    // FilePolygonModelBuilder builder ("/storage/Downloads/obj/Koltuk.obj");;
    // FilePolygonModelBuilder builder ("/storage/Downloads/obj/091_W_Aya_10K.obj");;
    // FilePolygonModelBuilder builder ("/storage/Downloads/obj/test_plane.obj");;
    // shape1 = builder.build();

    // double d = (double)1 / 5;
    // double d = (double)1 / 1317;
    // double d = 4;
    // double d = 0.002277904328018223;
    // trans4.accept(ScaleStrategy<double, 3>({d, d, d}));
    // trans4.accept(MoveStrategy<double, 3>({0, -2.5, 0}));
    // trans4.accept(MoveStrategy<double, 3>({0, -0.5, 0}));
    // trans4.accept(RotateStrategyOZ<double>(M_PI / 2));
    // trans4.accept(RotateStrategyOX<double>(M_PI / 2));
    // shape1->applyBasis(trans4);

    // shape1->add(shape2.get());
    // shape1->add(shape3.get());

    // this->shape1->applyBasis(trans2);
    // shape2->applyBasis(trans2);
    // trans2.accept(MoveStrategy<double>({0, 0, -4.5}));
    // this->shape1->applyBasis(trans2);
    // trans2.accept(MoveStrategy<double>({0, 0, 2.5}));
    // this->shape3->applyBasis(trans2);

    this->shapes.push_back(shape1);
    this->shapes.push_back(shape2);
    this->shapes.push_back(shape3);
    this->scene->add(shape1);
    // shape1->add(shape2.get());
    // this->scene->add(shape3);

    camera.reset(new NullObject());
    lighting.reset(new NullObject());
    lighting2.reset(new NullObject());
    lighting2.reset(new Sphere(0.25));
    // lighting2.reset(new NullObject());
    // lighting2.reset(new Plane(5, 5));
    // lighting2.reset(new Polygon());
    // lighting2.reset(new Cilinder(5, 0.25));
    // lighting2.reset(new Cone(3, 0.25));
    // lighting2.reset(new Cone(3, 0.25));
    // lighting2.reset(new Disk(center, Vector3<double>({-1, 0, 0}), 1));

    trans.accept(MoveStrategy<double>({-5, 5, 4}));
    // trans.accept(MoveStrategy<double>({-100, 0, 300}));
    lighting->applyBasis(trans);
    trans.accept(MoveStrategy<double>({5, -5, -4}));
    // trans.accept(MoveStrategy<double>({200, 1000, 0}));
    // trans.accept(RotateStrategyOY<double>(-M_PI / 2));
    // trans.accept(RotateStrategyOY<double>(-M_PI / 2));
    // trans.accept(RotateStrategyOZ<double>(M_PI / 2));
    // trans.accept(MoveStrategy<double>({2, 0, 0}));
    // trans.accept(MoveStrategy<double>({0, 2, 0}));
    trans.accept(MoveStrategy<double>({2, 1, 1.75}));
    // trans.accept(MoveStrategy<double>({4, 0, 0}));
    // trans.accept(MoveStrategy<double>({2, 1, 1}));
    // trans.accept(RotateStrategyOY<double>(-M_PI / 3));
    // trans.accept(MoveStrategy<double>({12, -5, -4}));
    // trans.accept(RotateStrategyOZ<double>(M_PI / 6));
    // trans.accept(MoveStrategy<double>({10, -5, -4}));
    // trans.accept(MoveStrategy<double>({3, 0, 0}));
    lighting2->applyBasis(trans);
    // shape3->applyBasis(trans);
    trans.accept(MoveStrategy<double>({-5, 5, 4}));
    trans3.accept(MoveStrategy<double>({0, 0, 3}));
    // trans3.accept(MoveStrategy<double>({0, 750, 700}));
    // trans3.accept(MoveStrategy<double>({0, 750, 700}));
    // trans3.accept(RotateStrategyOY<double>(-M_PI / 2));
    // trans3.accept(RotateStrategyOZ<double>(-M_PI / 6));
    // trans3.accept(RotateStrategyOX<double>(-M_PI / 6));
    // trans3.accept(RotateStrategyOX<double>(M_PI / 3));
    camera->applyBasis(trans3);

    this->shapes.push_back(lighting);
    this->shapes.push_back(lighting2);
    this->shapes.push_back(camera);
    this->scene->add(lighting);
    this->scene->add(lighting2);
    this->scene->add(camera);

    // std::shared_ptr<ShapeProperty> light_prop (new Lighting(lighting.get(), Intensity<>({5000, 5000, 5000})));
    std::shared_ptr<ShapeProperty> light_prop (new Lighting(lighting.get(), 40 * Intensity<>({1, 1, 1})));
    // std::shared_ptr<ShapeProperty> light_prop (new Lighting(lighting.get(), Intensity<>({5000, 0, 0})));
    std::shared_ptr<ShapeProperty> proj_prop (new PinholeProjector(camera.get(), 10));
    // std::shared_ptr<ShapeProperty> proj_prop (new PinholeProjector(camera.get(), 750));
    // std::shared_ptr<ShapeProperty> proj_prop (new ThinLensProjector(camera.get(), *this->scene, 4.5, 0.25, true));
    // std::shared_ptr<ShapeProperty> proj_prop (new OrthogonalProjector(camera.get()));
    // std::shared_ptr<ShapeProperty> light_prop2 (new Lighting(lighting2.get(), Intensity<>({800, 800, 1000})));
    // std::shared_ptr<ShapeProperty> light_prop2 (new Lighting(lighting2.get(), Intensity<>({400, 400, 500})));
    // std::shared_ptr<ShapeProperty> light_prop2 (new Lighting(lighting2.get(), Intensity<>({0.4, 0.4, 0.5})));
    std::shared_ptr<ShapeProperty> light_prop2 (new Lighting(lighting2.get(), 5 * Intensity<>({1, 0.7, 0.2})));
    // std::shared_ptr<ShapeProperty> light_prop2 (new Lighting(lighting2.get(), Intensity<>({8000, 8000, 10000})));
    // std::shared_ptr<ShapeProperty> light_prop2 (new Lighting(lighting2.get(), Intensity<>({2000, 2000, 2500})));
    // std::shared_ptr<ShapeProperty> light_prop2 (new Lighting(lighting2.get(), Intensity<>({0, 0, 5000})));

    std::shared_ptr<ShapeProperty> ambient (new AmbientLighting({0.2, 0.2, 0.2}));
    std::shared_ptr<ShapeProperty> active_proj (new SceneActiveProjector(std::static_pointer_cast<Projector>(proj_prop)));

    // envmap = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/HDR_111_Parking_Lot_2_Bg.jpg").build();
    envmap = LightArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/HDR_111_Parking_Lot_2/HDR_111_Parking_Lot_2/HDR_111_Parking_Lot_2_Ref.hdr").build();
    // envmap = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/HDR_111_Parking_Lot_2_Prev.jpg").build();
    std::shared_ptr<ShapeProperty> env (new SphericalMap(envmap, 4));

    texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/cross.jpg").build();
    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Downloads/obj/test/tex/091_W_Aya_2K_01.jpg").build();
    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/brick.jpeg").build();
    // texture = std::make_shared<SolidTexture<Intensity<>>>(Intensity<>({0.03, 0.38, 1}));
    // texture = std::make_shared<SolidTexture<Intensity<>>>(Intensity<>({1, 1, 1}));
    // texture = std::make_shared<SolidTexture<Intensity<>>>(Intensity<>({1, 0.8431372549019608, 0}));
    this->mat = std::make_shared<Material>();
    this->mat->add(std::make_shared<MaterialTexture>(texture, std::make_shared<UVTexturueMapper>()));
    this->mat->add(std::make_shared<MaterialAlbedo>(Intensity<>({1, 1, 1})));

    std::list<MaterialScattering::BuilderInfo> builders;

    std::shared_ptr<ScatteringInfo> info = std::make_shared<ScatteringInfo>();
    info->setProperty(std::make_shared<ScatteringScale>(0.3 * Intensity({1, 1, 1})));
    builders.push_back({std::make_shared<LambertDifusionBuilder>(), info});

    // info = std::make_shared<ScatteringInfo>();
    // info->setProperty(std::make_shared<ScatteringScale>(0.7 * Intensity({1, 1, 1})))
    //      .setProperty(std::make_shared<ScatteringPhongAlpha>(2));
    // builders.push_back({std::make_shared<PhongSpecularBuilder>(), info});

    // info = std::make_shared<ScatteringInfo>();
    // info->setProperty(std::make_shared<ScatteringScale>(Intensity({1, 1, 1})));
    // builders.push_back({std::make_shared<SpecularReflectionBuilder>(), info});
    //  
    // info = std::make_shared<ScatteringInfo>();
    // info->setProperty(std::make_shared<ScatteringScale>(Intensity({1, 1, 1})));
    // builders.push_back({std::make_shared<SpecularTransmissionBuilder>(), info});

    info = std::make_shared<ScatteringInfo>();
    info->setProperty(std::make_shared<ScatteringScale>(Intensity({1, 1, 1})));
    builders.push_back({std::make_shared<DielectricReflectionBuilder>(), info});
    // builders.push_back({std::make_shared<ConductorReflectionBuilder>(), info});

    // info = std::make_shared<ScatteringInfo>();
    // info->setProperty(std::make_shared<ScatteringScale>(Intensity({1, 1, 1})));
    // builders.push_back({std::make_shared<FresnelTransmissionBuilder>(), info});

    this->mat->add(std::make_shared<MaterialScattering>(builders));

    this->ralbedo = std::make_shared<MaterialRefractionIndex>(std::complex<double>(1.5, 0), Intensity<>({1, 1, 1}));
    this->mat->add(this->ralbedo);
    // this->mat->add(std::make_shared<MaterialAmbientAttraction>(Intensity<>({0, 0, 0})));

    std::shared_ptr<ShapeProperty> smlink (new ShapeMaterialLinker(shape1.get(), mat));

    this->scene->addProperty(light_prop);
    this->scene->addProperty(light_prop2);
    this->scene->addProperty(proj_prop);
    this->scene->addProperty(ambient);
    this->scene->addProperty(active_proj);
    this->scene->addProperty(env);
    this->scene->addProperty(smlink);

    // texture = std::make_unique<ArrayTexture<Intensity<>>>(mat);
    // texture = ImageArrayTextureBuilder<Intensity<>>("textures/01-3.jpg").build();
    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/01-3.jpg").build();
    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/cross.jpg").build();
    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/brick.jpeg").build();
    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/HDR_111_Parking_Lot_2_Bg.jpg").build();
    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/HDR_111_Parking_Lot_2_Prev.jpg").build();
    // envmap = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/HDR_111_Parking_Lot_2_Bg.jpg").build();
    // envmap = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/templates/latex/bmstu/Gerb_MGTU_imeni_Baumana-600x708.png").build();
    // envmap = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/HDR_111_Parking_Lot_2_Prev.jpg").build();
    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/brick2.jpg").build();
    // bmap = ImageArrayTextureBuilder<Vector3<double>>("/storage/Daniil/templates/latex/bmstu/Gerb_MGTU_imeni_Baumana-600x708.png").build();
    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/templates/latex/bmstu/Gerb_MGTU_imeni_Baumana-600x708.png").build();
    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/cross.jpg").build();

    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/wood/Substance_Graph_BaseColor.jpg").build();
    // bmap = ImageArrayTextureBuilder<Vector3<double>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/wood/Substance_Graph_Normal.jpg").build();
    // bmap = ImageArrayTextureBuilder<Vector3<double>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/normal_4.jpg").build();
    // bmap = ImageArrayTextureBuilder<Vector3<double>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/rock_normal.jpg").build();
    // bmap = ImageArrayTextureBuilder<Vector3<double>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/wood_normal.jpg").build();
    // texture = ImageArrayTextureBuilder<Intensity<>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/stone/bump.png").build();
    // texture = std::make_shared<SolidTexture<Intensity<>>>(Intensity<>({1, 0, 0}));
    // texture = std::make_shared<SolidTexture<Intensity<>>>(Intensity<>({0.7, 1, 0.7}));
    // bmap = ImageArrayTextureBuilder<Vector3<double>>("/storage/Daniil/work/lab/cgraphics/course_proj/textures/stone/bumpn.png").build();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_MainWindow()), canvas(new QCanvas(this)), 
      scene(new Scene())
{
    this->ui->setupUi(this);

    this->tab_projector = QSharedPointer<BaseTab>(new TabProjector(this->ui->tabWidget_props));
    this->tab_material = QSharedPointer<BaseTab>(new TabMaterial(this->ui->tabWidget_props));
    this->ui->tabWidget_props->addTab(this->tab_projector.get(), this->tab_projector->getName());
    this->ui->tabWidget_props->addTab(this->tab_material.get(), this->tab_material->getName());

    this->ui->mainLayout->addWidget(this->canvas.get(), 0, 0);

    // this->timer.setInterval(500);
    this->timer.start(100);

    QObject::connect(&this->timer, SIGNAL(timeout()), this, SLOT(timeout()));
    QObject::connect(this->ui->pushButton_transform_apply, SIGNAL(clicked()),
                     this, SLOT(canvas_clicked()));
    // QObject::connect(this->ui->pushButton_save, SIGNAL(clicked()),
    //                  this, SLOT(save()));

    this->setupScene();
}

void MainWindow::canvas_clicked()
{
    if (!this->needredraw)
    {
        Transform<double, 3> trans;
        // trans.accept(RotateStrategyOY<double>(4 * M_PI / 3));
        trans.accept(RotateStrategyOY<double>(M_PI / 12));
        // this->shapes.front()->applyBasis(trans);
        // trans.accept(RotateStrategyOY<double>(-M_PI / 12));
        // trans.accept(RotateStrategyOX<double>(M_PI / 12));
        this->shapes.back()->applyBasis(trans);
        this->needredraw = true;

        // this->mat->remove(this->ralbedo);
        // this->ralbedo = std::make_shared<MaterialRefractionIndex>(std::complex<double>(1.5, 0), Intensity<>({1, 1, 1}) * ((double)this->ui->horizontalSlider_ralbedo->value() / 100));
        // this->ralbedo = std::make_shared<MaterialRefractionIndex>(std::complex<double>(0.27732, 2.9278), Intensity<>({1, 1, 1}) * ((double)this->ui->horizontalSlider_ralbedo->value() / 100));
        // this->mat->add(this->ralbedo);

        this->paintEvent(nullptr);
    }
}

void *paint_master(void *_arg)
{
    MainWindow::ThreadArg *arg = (MainWindow::ThreadArg *)_arg;

    std::cout << "start" << std::endl;

    size_t cnt = arg->cnt - 1;

    size_t lx = arg->display->width(), ly = arg->display->height();
    QtDisplayAdapter display (*arg->display);

    double aspect = (double)ly / lx;

    // display.setOffset(-4, 8 * aspect / 2);
    // display.setRealWidth(8);

    display.setOffset(-1, 2 * aspect / 2);
    display.setRealWidth(2);

    arg->progress = std::make_shared<RenderProgress>(display);

    // display.setOffset(1500, 3000 * aspect / 2);
    // display.setOffset(-750 / aspect, 750);
    // display.setRealHeight(1500);

    // display.setOffset(-20, 40 * aspect / 2);
    // display.setRealWidth(40);

    ViewPortRenderer vrender;

    // TracerInfo info = TracerInfo().setProperty(std::make_shared<TracerMaxDepth>(10))
    //                               .setProperty(std::make_shared<TracerLightSamples>(10));

    // CompleteRenderer crender(CompleteTracerBuilder().build(info), 1);
    // CompleteRenderer crender(TestTracerBuilder().build(info), 1);

    // Renderer &base_render = crender;
    Renderer &base_render = vrender;

    ParallelRendererDecorator rdecor (base_render, cnt, cnt, cnt);

    HDRDisplayLinker linker (display);

    // Renderer &render = rdecor;
    Renderer &render = base_render;

    BaseDisplayAdapter &adapter = linker.getHDRAdapter();
    // BaseDisplayAdapter &adapter = display;

    render.render(*arg->scene, adapter, arg->progress.get());
    // render.render(*arg->scene, adapter);

    // linker.apply(LinearDisplayTransform());
    linker.apply(GammaDisplayTransform(2.2));

    *arg->fin = true;
    std::cout << "done" << std::endl;

    return NULL;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    if (this->needredraw && !this->start_draw)
    {
        // size_t cnt = this->ui->spinBox_threads->value(),
        //        scale = this->ui->spinBox_scale->value();
        size_t cnt = 10, scale = 5;


        size_t lx = this->canvas->width() / scale,
               ly = this->canvas->height() / scale;

        this->screen = QImage(lx, ly, QImage::Format_RGBA64);

        this->arg.display = &this->screen;
        this->arg.scene = this->scene.get();
        this->arg.fin = &this->stop_draw;
        this->arg.cnt = cnt;
        this->arg.progres = 0;

        pthread_create(&this->thread, NULL, paint_master, &this->arg);

        this->start_draw = true;
        this->stop_draw = false;
    }
}

void MainWindow::timeout(void)
{
    if (this->needredraw && this->stop_draw)
    {
        QPixmap *pixmap = *this->canvas;
        QPainter painter (pixmap);
        pixmap->fill(Qt::transparent);

        painter.drawImage(0, 0, this->screen.scaled(this->canvas->width(),
                                                    this->canvas->height()));
        this->canvas->update();

        this->needredraw = false;
        this->start_draw = false;
    }

    if (this->arg.progress)
        // this->ui->progressBar->setValue(this->arg.progress->progress() * 100);
        this->ui->label_status->setText(QString("Progress: %1%").arg(this->arg.progress->progress() * 100));

    // this->ui->progressBar->setValue((double)this->arg.progres / this->progres * 100);
}

void MainWindow::save(void)
{
    if (!this->needredraw && this->stop_draw)
    {
        QString filename = QFileDialog::getSaveFileName(this, "Save File",
                                                        "",
                                                        "Images (*.png *.xpm *.jpg)");

        if ("" != filename)
            this->screen.save(filename);
    }
}

#include "moc_mainwindow.cpp"

