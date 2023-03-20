#include "tab_material.h"

TabMaterial::TabMaterial(QWidget *parent)
    : BaseTab("Material", parent), ui(new Ui_tab_material())
{
    this->ui->setupUi(this);
}

