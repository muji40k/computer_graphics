#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "mainwindow.h"
#include "measure.h"

#include <memory>

#include "interface_handle.h"
#include "view_port_renderer.h"

#include "cube.h"
#include "sphere.h"
#include "cilinder.h"
#include "camera.h"
#include "null_object.h"
#include "pinhole_projector.h"

#include "transform_strategies.h"

int measure(void)
{
    handle_t preset;

    material_t mat = {"material", {{"phong", PHONG_SPECULAR, 0.4, 3},
                                   {"lambert", LAMBERT_DIFUSION, 0.6, 0}},
                      0.7, {1, 0}, 1,
                      // {true, FILE_TEXTURE, "textures/cross.jpg", {}}};
                      {true, FILE_TEXTURE, "/storage/Daniil/work/lab/cgraphics/course_proj/textures/cross.jpg", {}}};

    preset.materials.push_back(mat);

    preset.objects.push_back({"cube", std::make_shared<Cube>(2, 2, 2), nullptr,
                              {false, ORTHOGONAL_PROJECTOR, 0, 0, 0, false, 0},
                              {false, 0, {}}});
    Transform<double, 3> trans_cube;
    trans_cube.accept(MoveStrategy<double, 3>({0.5, 0, 0}));
    preset.objects.back().shape->applyBasis(trans_cube);

    preset.objects.push_back({"sphere", std::make_shared<Sphere>(0.5), &preset.materials.back(),
                              {false, ORTHOGONAL_PROJECTOR, 0, 0, 0, false, 0},
                              {false, 0, {}}});
    Transform<double, 3> trans_sphere;
    trans_sphere.accept(MoveStrategy<double, 3>({-0.25, 0, 0.5}));
    preset.objects.back().shape->applyBasis(trans_sphere);

    preset.objects.push_back({"cylinder", std::make_shared<Cilinder>(5, 0.5), nullptr,
                              {false, ORTHOGONAL_PROJECTOR, 0, 0, 0, false, 0},
                              {false, 0, {}}});
    Transform<double, 3> trans_cylinder;
    trans_cylinder.accept(RotateStrategyOZ<double>(M_PI / 2));
    trans_cylinder.accept(MoveStrategy<double, 3>({0, 0, -0.5}));
    preset.objects.back().shape->applyBasis(trans_cylinder);

    preset.objects.push_back({"camera", std::make_shared<Camera>(), nullptr,
                              {true, PINHOLE_PROJECTOR, 1, 0.5, 0, false, 0},
                              {false, 0, {}}});
    Transform<double, 3> trans_camera;
    trans_camera.accept(MoveStrategy<double, 3>({0, 0, 2}));
    trans_camera.accept(RotateStrategyOY<double>(-M_PI / 6));
    preset.objects.back().shape->applyBasis(trans_camera);
    preset.meta.projector = &preset.objects.back();

    preset.objects.push_back({"light1", std::make_shared<NullObject>(), nullptr,
                              {false, PINHOLE_PROJECTOR, 0, 0, 0, false, 0},
                              {true, 0.5, {1, 1, 1}}});
    Transform<double, 3> trans_light1;
    trans_light1.accept(MoveStrategy<double, 3>({-2.5, 2, 0.5}));
    preset.objects.back().shape->applyBasis(trans_light1);

    preset.objects.push_back({"light2", std::make_shared<NullObject>(), nullptr,
                              {false, PINHOLE_PROJECTOR, 0, 0, 0, false, 0},
                              {true, 0.7, {0.5, 0.5, 1}}});
    Transform<double, 3> trans_light2;
    trans_light2.accept(MoveStrategy<double, 3>({3, 1.5, 0.5}));
    preset.objects.back().shape->applyBasis(trans_light2);

    preset.meta.ambient.set = true;
    preset.meta.ambient.power = 0.02;
    preset.meta.ambient.color = Intensity<>({1, 1, 1});

    preset.meta.env_map_size = 10;
    preset.meta.env_map.set = true;
    // preset.meta.env_map.texture_name = "textures/HDR_111_Parking_Lot_2_Prev.jpg";
    preset.meta.env_map.texture_name = "/storage/Daniil/work/lab/cgraphics/course_proj/textures/HDR_111_Parking_Lot_2_Prev.jpg";

    refresh_cache(preset);

    preset_t mpreset;
    mpreset.scene = build_scene(preset);
    mpreset.renderer = std::make_shared<ViewPortRenderer>();

    static const std::list<size_t> sizes = {57, 105, 153, 200};
    static const size_t rep = 1;

    // std::list<Measurement::Stat> size_measure;
    // PlainMeasurement pmeasure (rep);
    //  
    // for (size_t size : sizes)
    // {
    //     mpreset.height = mpreset.width = size;
    //     mpreset.name = to_string(size) + "x" + to_string(size);
    //     size_measure.splice(size_measure.end(), pmeasure.measure(mpreset));
    // }
    //  
    // std::cout << "plain:" << std::endl;
    //  
    // for (Measurement::Stat &stat : size_measure)
    //     std::cout << stat.name << "," << stat.time << std::endl;

    std::list<Measurement::Stat> parallel_measure;

    for (size_t split : {6, 8, 10})
    {
        ParallelMeasurements parmeas (rep, split, split, {2, 4, 6, 8, 10});

        for (size_t size : sizes)
        {
            parallel_measure.clear();
            mpreset.height = mpreset.width = size;
            mpreset.name = to_string(size) + "x" + to_string(size);
            parallel_measure.splice(parallel_measure.end(), parmeas.measure(mpreset));

            std::cout << "parallel grid: split - " << split << " size - " << size <<  std::endl;

            for (Measurement::Stat &stat : parallel_measure)
                std::cout << stat.description << "," << stat.time << std::endl;
        }
    }


    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    if (2 == argc && !strcmp(argv[1], "measure"))
        return measure();

    QApplication app (argc, argv);
    MainWindow window;

    window.show();

    return app.exec();
}
