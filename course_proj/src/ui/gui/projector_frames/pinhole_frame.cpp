#include "pinhole_frame.h"

PinholeFrame::PinholeFrame(QWidget *parent)
    : ProjectorFrame(parent), ui(new Ui_frame_pinhole())
{
    this->ui->setupUi(this);
}

PinholeFrame::~PinholeFrame(void) {}

void PinholeFrame::set(object_t &object)
{
    this->ui->doubleSpinBox_offset->setValue(object.projector.offset);
}

void PinholeFrame::save(object_t &object)
{
    object.projector.offset = this->ui->doubleSpinBox_offset->value();
}

#include "moc_pinhole_frame.cpp"

