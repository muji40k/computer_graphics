#ifndef _TAB_MATERIAL_H_
#define _TAB_MATERIAL_H_

#include "base_tab.h"
#include <QSharedPointer>

#include "ui_tab_material.h"

class TabMaterial : public BaseTab
{
    Q_OBJECT

    public:
        TabMaterial(QWidget *parent = nullptr);
        virtual ~TabMaterial(void) override = default;

        virtual void set(object_t &object, handle_t &handle) override;
        virtual void save(object_t &object, handle_t &handle) override;

    private:
        QSharedPointer<Ui_tab_material> ui = nullptr;
};

#endif

