#ifndef _FORM_MATERIAL_H_
#define _FORM_MATERIAL_H_

#include <QWidget>
#include <QSharedPointer>
#include <QColor>
#include <QCloseEvent>

#include "interface_handle.h"

#include "ui_form_material.h"

class FormMaterial : public QWidget
{
    Q_OBJECT

    public:
        FormMaterial(material_t *material, QWidget *parent = nullptr);

    private:
        void initFields(void);
        void closeEvent(QCloseEvent* event);
        void saveFields(void);
        void showScatteringPref(scattering_t *scattering);

    private slots:
        void on_pref_close(void);
        void on_listwidget_clicked(QListWidgetItem *item);
        void on_listwidget_double_clicked(QListWidgetItem *item);
        void on_listwidget_add_clicked(void);
        void on_listwidget_delete_clicked(void);
        void on_push_button_color_choose_clicked(void);
        void on_tool_button_texture_path(void);

    private:
        material_t *material = nullptr;
        std::list<scattering_t> scattering;
        scattering_t *active_scattering;
        QSharedPointer<Ui_Form> ui = nullptr;
        QColor color;
        QSharedPointer<QWidget> form_material_layer = nullptr;
        size_t layer_counter = 0;
};

#endif

