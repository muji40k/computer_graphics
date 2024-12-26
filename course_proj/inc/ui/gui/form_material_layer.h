#ifndef _FORM_MATERIAL_LAYER_H_
#define _FORM_MATERIAL_LAYER_H_

#include <QWidget>
#include <QSharedPointer>
#include <QFrame>
#include <QCloseEvent>

#include "interface_handle.h"
#include "scattering_frame.h"

#include "ui_form_material_layer.h"

class FormMaterialLayer : public QWidget
{
    Q_OBJECT

    public:
        FormMaterialLayer(scattering_t *scattering, QWidget *parent = nullptr);
        ~FormMaterialLayer(void);

    private:
        void initFields(void);
        void closeEvent(QCloseEvent* event);
        void saveFields(void);

    signals:
        void closed(void);

    private slots:
        void on_combobox_changed(int item);

    private:
        scattering_t *scattering = nullptr;
        QSharedPointer<Ui_form_material_layer> ui = nullptr;
        ScatteringFrame *frame = nullptr;
};

#endif

