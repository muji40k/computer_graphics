#include "pinhole_frame.h"

PinholeFrame::PinholeFrame(QWidget *parent)
    : ProjectorFrame(parent), ui(new Ui_frame_pinhole())
{
    this->ui->setupUi(this);
}

PinholeFrame::~PinholeFrame(void) {}

#include "moc_pinhole_frame.cpp"

