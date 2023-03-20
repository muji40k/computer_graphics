#include "tab_projector.h"

#include "pinhole_frame.h"
#include "thinlens_frame.h"

TabProjector::TabProjector(QWidget *parent)
    : BaseTab("Projector", parent), ui(new Ui_tab_projector())
{
    this->ui->setupUi(this);

    this->typeChanged(this->ui->comboBox_projector_type->currentIndex());

    QObject::connect(this->ui->comboBox_projector_type,
                     SIGNAL(activated(int)),
                     this, SLOT(typeChanged(int)));
}

void TabProjector::typeChanged(int index)
{
    if (3 == this->ui->formLayout->rowCount())
        this->ui->formLayout->removeRow(2);

    if (1 == index)
        this->active_frame = new PinholeFrame(this);
    else if (2 == index)
        this->active_frame = new ThinLensFrame(this);
    else
        this->active_frame = nullptr;

    if (nullptr != this->active_frame)
        this->ui->formLayout->addRow(this->active_frame);
}

#include "moc_tab_projector.cpp"

