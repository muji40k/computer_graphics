#include "phong_specular_frame.h"

PhongSpecularFrame::PhongSpecularFrame(QWidget *parent)
    : ScatteringFrame(parent), ui(QSharedPointer<Ui_phong_specular_frame>::create())
{
    this->ui->setupUi(this);
}

PhongSpecularFrame::~PhongSpecularFrame(void) {}

void PhongSpecularFrame::save(scattering_t &scattering)
{
    scattering.phong_alpgha = this->ui->spinBox_alpha->value();
}

void PhongSpecularFrame::set(scattering_t &scattering)
{
    this->ui->spinBox_alpha->setValue(scattering.phong_alpgha);
}

#include "moc_phong_specular_frame.cpp"

