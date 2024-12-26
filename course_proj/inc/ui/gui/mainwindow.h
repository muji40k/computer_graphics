#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <list>
#include <memory>

#include <QSharedPointer>
#include <QPaintEvent>
#include <QTimer>
#include <QFileDialog>
#include <QListWidget>
#include <QColor>

#include "interface_handle.h"

#include "ui_mainwindow.h"
#include "qcanvas.h"

#include "base_tab.h"

#include "renderer.h"

#include "scene.h"
#include "shape.h"
#include "material.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        using ThreadArg = struct
        {
            const render_pref_t *render_pref;
            const object_t      *projector;
            QImage              *display;
            Scene               *scene;
            bool                *fin;
            size_t               cnt;
            std::shared_ptr<RenderProgress> progress;
        };

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow(void);

    private:
        void paintEvent(QPaintEvent *event);
        // std::shared_ptr<Scene> buildScene(void);
        void showMaterialPref(material_t *material);
        object_t getDefaultObj(std::string name);
        // void cache(void);
        void initScene(void);
        void refreshTabs(void);
        void setFields(void);
        void getFields(void);

    private:
        QSharedPointer<Ui_MainWindow> ui = nullptr;
        QSharedPointer<QCanvas> canvas = nullptr;
        QSharedPointer<QImage> screen = nullptr;
        QColor ambient_color;
        QColor emission_color;

        std::list<BaseTab *> tabs;
        QSharedPointer<QWidget> form_material = nullptr;
        QSharedPointer<QWidget> form_preferences = nullptr;

        handle_t scene_handle;
        object_t *active_object;
        material_t *active_material;
        render_pref_t render_pref;
        std::shared_ptr<Scene> last_scene;

        bool vp_needredraw = false;
        QTimer vp_timer;
        bool vp_start_draw = false;
        bool vp_stop_draw = false;

        bool complete_needredraw = false;
        QTimer complete_timer;
        bool complete_start_draw = false;
        bool complete_stop_draw = false;

        ThreadArg arg;
        pthread_t thread;

        size_t sphere_counter = 0;
        size_t cube_counter = 0;
        size_t cylinder_counter = 0;
        size_t cone_counter = 0;
        size_t plane_counter = 0;
        size_t disk_counter = 0;
        size_t polygon_model_counter = 0;
        size_t camera_counter = 0;
        size_t material_counter = 0;
        size_t null_object_counter = 0;

    private slots:
        void on_preview_clicked(void);
        void vp_timeout(void);
        void complete_timeout(void);
        void complete_render_start(void);

        void object_clicked(QListWidgetItem *item);
        void material_clicked(QListWidgetItem *item);
        void material_double_clicked(QListWidgetItem *item);

        void material_add_clicked(void);
        void material_delete_clicked(void);

        void object_delete_clicked(void);

        void action_preferences(void);
        void action_run_in_viewport(void);

        void action_add_sphere_triggered(void);
        void action_add_cube_triggered(void);
        void action_add_cylinder_triggered(void);
        void action_add_cone_triggered(void);
        void action_add_plane_triggered(void);
        void action_add_disk_triggered(void);
        void action_add_polygon_triggered(void);
        void action_add_camera_triggered(void);
        void action_add_null_object_triggered(void);

        void checkBox_ambient_lighting_clicked(bool state);
        void checkBox_env_map_clicked(bool state);
        void checkBox_emission_clicked(bool state);

        void pushButton_ambient_lighting_color_clicked(void);
        void toolButton_env_map_clicked(void);
        void pushButton_transform_apply_clicked(void);
        void pushButton_emission_color_clicked(void);
};

#endif

