#include "thinlens_frame.h"

ThinLensFrame::ThinLensFrame(QWidget *parent)
    : ProjectorFrame(parent), ui(new Ui_frame_thinlens())
{
    this->ui->setupUi(this);

    QObject::connect(this->ui->checkBox_autofocus, SIGNAL(stateChanged(int)),
                     this, SLOT(autofocus()));
}

ThinLensFrame::~ThinLensFrame(void) {}

void ThinLensFrame::autofocus(void)
{
    this->ui->frame_focus->setVisible(!this->ui->checkBox_autofocus->isChecked());
}

#include "moc_thinlens_frame.cpp"

