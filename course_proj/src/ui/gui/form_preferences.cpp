#include "form_preferences.h"

#include <QFileDialog>

FormPreferences::FormPreferences(render_pref_t *preferences, QWidget *parent)
    : QWidget(parent), preferences(preferences),
      ui(QSharedPointer<Ui_form_render_preferences>::create())
{
    this->ui->setupUi(this);
    this->initFields();
    
    QObject::connect(this->ui->toolButton_filename, SIGNAL(clicked()),
                     this, SLOT(tool_button_clicked()));
}

void FormPreferences::initFields(void)
{
    this->ui->spinBox_max_resolution->setValue(this->preferences->viewport.resolution);
    this->ui->spinBox_threads_vp->setValue(this->preferences->viewport.threads);

    this->ui->lineEdit_filename->setText(this->preferences->complete.filename.c_str());
    this->ui->spinBox_width->setValue(this->preferences->complete.width);
    this->ui->spinBox_height->setValue(this->preferences->complete.height);
    this->ui->spinBox_camear_samples->setValue(this->preferences->complete.camera_samples);
    this->ui->spinBox_light_samples->setValue(this->preferences->complete.light_samples);
    this->ui->spinBox_light_max_depth->setValue(this->preferences->complete.max_depth);
    this->ui->spinBox_threads_2->setValue(this->preferences->complete.threads);
}

void FormPreferences::closeEvent(QCloseEvent* event)
{
    this->saveFields();
    QWidget::closeEvent(event);
}

void FormPreferences::saveFields(void)
{
    this->preferences->viewport.resolution = this->ui->spinBox_max_resolution->value();
    this->preferences->viewport.threads = this->ui->spinBox_threads_vp->value();

    this->preferences->complete.filename = this->ui->lineEdit_filename->text().toStdString();
    this->preferences->complete.width = this->ui->spinBox_width->value();
    this->preferences->complete.height = this->ui->spinBox_height->value();
    this->preferences->complete.camera_samples = this->ui->spinBox_camear_samples->value();
    this->preferences->complete.light_samples = this->ui->spinBox_light_samples->value();
    this->preferences->complete.max_depth = this->ui->spinBox_light_max_depth->value();
    this->preferences->complete.threads = this->ui->spinBox_threads_2->value();
}

void FormPreferences::tool_button_clicked(void)
{
    QString filename = QFileDialog::getSaveFileName(this, "Choose render name",
                                                    "",
                                                    "Images (*.png *.xpm *.jpg)");

    if ("" != filename)
        this->ui->lineEdit_filename->setText(filename);
}

#include "moc_form_preferences.cpp"

