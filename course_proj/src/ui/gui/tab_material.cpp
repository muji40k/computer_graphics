#include "tab_material.h"

TabMaterial::TabMaterial(QWidget *parent)
    : BaseTab("Material", parent), ui(new Ui_tab_material())
{
    this->ui->setupUi(this);
}

void TabMaterial::set(object_t &object, handle_t &handle)
{
    this->ui->comboBox_material->clear();
    this->ui->comboBox_material->addItem("None");

    this->ui->comboBox_material->setCurrentIndex(0);

    for (material_t &mat : handle.materials)
        this->ui->comboBox_material->addItem(mat.name.c_str());

    if (!object.material)
        return;

    size_t i = 1;

    for (material_t &mat : handle.materials)
    {
        if (&mat == object.material)
        {
            this->ui->comboBox_material->setCurrentIndex(i);
            return;
        }
        i++;
    }
}

void TabMaterial::save(object_t &object, handle_t &handle)
{
    size_t index = this->ui->comboBox_material->currentIndex();
    object.material = nullptr;

    if (0 == index--)
        return;

    for (material_t &mat : handle.materials)
        if (0 == index--)
        {
            object.material = &mat;
            return;
        }
}

#include "moc_tab_material.cpp"

