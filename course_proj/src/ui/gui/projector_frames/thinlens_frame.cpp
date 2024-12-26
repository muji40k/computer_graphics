#include "thinlens_frame.h"

ThinLensFrame::ThinLensFrame(QWidget *parent)
    : ProjectorFrame(parent), ui(new Ui_frame_thinlens())
{
    this->ui->setupUi(this);

    QObject::connect(this->ui->checkBox_autofocus, SIGNAL(toggled(bool)),
                     this, SLOT(autofocus()));
}

ThinLensFrame::~ThinLensFrame(void) {}

void ThinLensFrame::set(object_t &object)
{
    this->ui->doubleSpinBox_aperture->setValue(object.projector.aperture);
    this->ui->doubleSpinBox_focus_distance->setValue(object.projector.focus);
    this->ui->checkBox_autofocus->setChecked(object.projector.autofocus);
}

void ThinLensFrame::save(object_t &object)
{
    object.projector.aperture = this->ui->doubleSpinBox_aperture->value();
    object.projector.focus = this->ui->doubleSpinBox_focus_distance->value();
    object.projector.autofocus = this->ui->checkBox_autofocus->isChecked();
}

void ThinLensFrame::autofocus(void)
{
    this->ui->frame_focus->setVisible(!this->ui->checkBox_autofocus->isChecked());
}

#include "moc_thinlens_frame.cpp"

