#include "tab_projector.h"

#include "pinhole_frame.h"
#include "thinlens_frame.h"

TabProjector::TabProjector(QWidget *parent)
    : BaseTab("Projector", parent), ui(new Ui_tab_projector())
{
    this->ui->setupUi(this);

    QObject::connect(this->ui->comboBox_projector_type,
                     SIGNAL(currentIndexChanged(int)),
                     this, SLOT(typeChanged(int)));
}

void TabProjector::set(object_t &object, handle_t &)
{
    this->last = &object;
    this->ui->doubleSpinBox_width->setValue(object.projector.width);
    this->ui->comboBox_projector_type->setCurrentIndex(object.projector.type);
}

void TabProjector::save(object_t &object, handle_t &)
{
    object.projector.width = this->ui->doubleSpinBox_width->value();
    object.projector.type = (projector_type_t)this->ui->comboBox_projector_type->currentIndex();

    if (this->active_frame)
        this->active_frame->save(object);
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
    {
        if (this->last)
            this->active_frame->set(*this->last);

        this->ui->formLayout->addRow(this->active_frame);
    }
}

#include "moc_tab_projector.cpp"

