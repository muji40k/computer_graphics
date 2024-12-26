#include "form_material.h"

#include <QColorDialog>
#include <QFileDialog>

#include "form_material_layer.h"

#include "qt_misc_functions.h"

FormMaterial::FormMaterial(material_t *material, QWidget *parent)
    : QWidget(parent), material(material), ui(QSharedPointer<Ui_Form>::create())
{
    this->ui->setupUi(this);
    this->initFields();

    QObject::connect(this->ui->listWidget_layers, SIGNAL(itemClicked(QListWidgetItem *)),
                     this, SLOT(on_listwidget_clicked(QListWidgetItem *)));
    QObject::connect(this->ui->listWidget_layers, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
                     this, SLOT(on_listwidget_double_clicked(QListWidgetItem *)));
    QObject::connect(this->ui->pushButton_add, SIGNAL(clicked()),
                     this, SLOT(on_listwidget_add_clicked()));
    QObject::connect(this->ui->pushButton_delete, SIGNAL(clicked()),
                     this, SLOT(on_listwidget_delete_clicked()));
    QObject::connect(this->ui->pushButton_color_choose, SIGNAL(clicked()),
                     this, SLOT(on_push_button_color_choose_clicked()));
    QObject::connect(this->ui->toolButton_texture_path, SIGNAL(clicked()),
                     this, SLOT(on_tool_button_texture_path()));
}

void FormMaterial::initFields(void)
{
    if (this->material->texture.set)
    {
        setBackgroundColor(this->ui->label_color, this->material->texture.color);
        this->ui->lineEdit_texture_path->setText(this->material->texture.texture_name.c_str());

        if (FILE_TEXTURE == this->material->texture.type)
            this->ui->radioButton_texture->setChecked(true);
        else if (COLOR_TEXTURE == this->material->texture.type)
            this->ui->radioButton_color->setChecked(true);
    }

    this->ui->doubleSpinBox_ri_real->setValue(this->material->ri.real());
    this->ui->doubleSpinBox_ri_imag->setValue(this->material->ri.imag());
    this->ui->doubleSpinBox_albedo->setValue(this->material->albedo);
    this->ui->doubleSpinBox_ambient->setValue(this->material->ambient_attraction);

    this->scattering = this->material->scattering;

    for (scattering_t &scattering : this->scattering)
        this->ui->listWidget_layers->addItem(scattering.name.c_str());

    this->color = QColor(int(this->material->texture.color[0]),
                         int(this->material->texture.color[1]),
                         int(this->material->texture.color[2]));
}

void FormMaterial::closeEvent(QCloseEvent* event)
{
    this->saveFields();
    QWidget::closeEvent(event);
}

void FormMaterial::saveFields(void)
{
    this->material->texture.set = true;

    if (this->ui->radioButton_color->isChecked())
    {
        this->material->texture.type = COLOR_TEXTURE;
        this->material->texture.color[0] = (double)this->color.red() / 255;
        this->material->texture.color[1] = (double)this->color.green() / 255;
        this->material->texture.color[2] = (double)this->color.blue() / 255;
    }
    else if (this->ui->radioButton_texture->isChecked())
    {
        this->material->texture.type = FILE_TEXTURE;
        this->material->texture.texture_name = this->ui->lineEdit_texture_path->text().toStdString();
    }

    this->material->ri.real(this->ui->doubleSpinBox_ri_real->value());
    this->material->ri.imag(this->ui->doubleSpinBox_ri_imag->value());
    this->material->albedo = this->ui->doubleSpinBox_albedo->value();
    this->material->ambient_attraction = this->ui->doubleSpinBox_ambient->value();

    this->material->scattering = this->scattering;
}

void FormMaterial::showScatteringPref(scattering_t *scattering)
{
    this->form_material_layer = QSharedPointer<FormMaterialLayer>::create(scattering);
    this->form_material_layer->show();

    QObject::connect(this->form_material_layer.get(), SIGNAL(closed()),
                     this, SLOT(on_pref_close()));
}

void FormMaterial::on_pref_close(void)
{
    QObject::disconnect(this->form_material_layer.get(), nullptr,
                        this, nullptr);

    this->ui->listWidget_layers->clear();

    for (scattering_t &scattering : this->scattering)
        this->ui->listWidget_layers->addItem(scattering.name.c_str());
}

void FormMaterial::on_listwidget_clicked(QListWidgetItem *item)
{
    for (scattering_t &scattering : this->scattering)
        if (item->text() == QString(scattering.name.c_str()))
        {
            this->active_scattering = &scattering;
            return;
        }
}

void FormMaterial::on_listwidget_double_clicked(QListWidgetItem *item)
{
    this->on_listwidget_clicked(item);
    this->showScatteringPref(this->active_scattering);
}

void FormMaterial::on_listwidget_add_clicked(void)
{
    scattering_t out;

    out.name = std::string("Layer ") + std::to_string(this->layer_counter++);
    out.type = LAMBERT_DIFUSION;
    out.scale = 1;
    out.phong_alpgha = 3;

    this->scattering.push_back(out);
    this->ui->listWidget_layers->addItem(QString(out.name.c_str()));
}

void FormMaterial::on_listwidget_delete_clicked(void)
{
    if (!this->active_scattering)
        return;

    QListWidgetItem *item = this->ui->listWidget_layers->takeItem(this->ui->listWidget_layers->currentRow());

    if (!item)
        return;

    for (auto iter = this->scattering.begin();
         this->scattering.end() != iter; iter++)
        if (item->text() == QString((*iter).name.c_str()))
        {
            this->scattering.erase(iter);
            this->on_listwidget_clicked(this->ui->listWidget_layers->currentItem());
            return;
        }
}

void FormMaterial::on_push_button_color_choose_clicked(void)
{
    QColor tmp = QColorDialog::getColor();

    if (tmp.isValid())
    {
        this->color = tmp;
        setBackgroundColor(this->ui->label_color, this->color);
    }
}

void FormMaterial::on_tool_button_texture_path(void)
{
    QString filename = QFileDialog::getOpenFileName(this, "Open texture",
                                                    "",
                                                    "Images (*.png *.xpm *.jpg)");

    if ("" != filename)
        this->ui->lineEdit_texture_path->setText(filename);
}

#include "moc_form_material.cpp"

