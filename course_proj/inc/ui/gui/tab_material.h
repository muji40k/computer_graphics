#ifndef _TAB_MATERIAL_H_
#define _TAB_MATERIAL_H_

#include "base_tab.h"
#include <QSharedPointer>

#include "ui_tab_material.h"

class TabMaterial : public BaseTab
{
    public:
        TabMaterial(QWidget *parent = nullptr);
        virtual ~TabMaterial(void) = default;

    private:
        QSharedPointer<Ui_tab_material> ui = nullptr;
};

#endif

