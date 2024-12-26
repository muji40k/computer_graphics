#include "form_material_layer.h"

#include "phong_specular_frame.h"

FormMaterialLayer::FormMaterialLayer(scattering_t *scattering, QWidget *parent)
    : QWidget(parent), scattering(scattering), ui(QSharedPointer<Ui_form_material_layer>::create())
{
    this->ui->setupUi(this);
    QObject::connect(this->ui->comboBox_type, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(on_combobox_changed(int)));

    this->initFields();
}

FormMaterialLayer::~FormMaterialLayer(void)
{
    if (this->frame)
        delete this->frame;
}

void FormMaterialLayer::initFields(void)
{
    this->ui->lineEdit_name->setText(this->scattering->name.c_str());
    this->ui->doubleSpinBox_scale->setValue(this->scattering->scale);
    this->ui->comboBox_type->setCurrentIndex(this->scattering->type);
}

void FormMaterialLayer::closeEvent(QCloseEvent* event)
{
    this->saveFields();
    emit this->closed();
    QWidget::closeEvent(event);
}

void FormMaterialLayer::saveFields(void)
{
    this->scattering->name = this->ui->lineEdit_name->text().toStdString();
    this->scattering->scale = this->ui->doubleSpinBox_scale->value();
    this->scattering->type = (scattering_type_t)this->ui->comboBox_type->currentIndex();

    if (this->frame)
        this->frame->save(*this->scattering);
}

void FormMaterialLayer::on_combobox_changed(int item)
{
    if (4 == this->ui->formLayout->rowCount())
        this->ui->formLayout->removeRow(3);

    if (PHONG_SPECULAR == item)
        this->frame = new PhongSpecularFrame(this);
    else
        this->frame = nullptr;

    if (nullptr != this->frame)
    {
        this->frame->set(*this->scattering);
        this->ui->formLayout->addRow(this->frame);
    }
}

#include "moc_form_material_layer.cpp"

