#include <iostream>
#include <QPalette>
#include <cmath>
#include "qcustomplot.h"
#include "mainwindow.h"
#include "moc_mainwindow.cpp"
#include "ellipse_test.h"

#include <QGridLayout>
#include <QPainter>
#include <QFontMetrics>
#include <QVector>

#define EPS 1e-8
#define AMOUNT_LINES 5
#define DEFAULT_WIDTH  1500
#define DEFAULT_HEIGHT 1000

typedef enum
{
    SINGLE,
    SPECTRUM,
    UNKNOWN
} draw_mode_t;

typedef enum
{
    CIRCLE,
    ELLIPSE
} draw_type_t;

static size_t get_active_radio(QRadioButton **const buttons,
                               const size_t amount);

static int get_distance(QPoint &point1, QPoint &point2);

ClickableLabel::ClickableLabel(QWidget* parent) : QLabel(parent) {}
ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked(event);
}

MainWindow::MainWindow(void)
{
    this->ui = new Ui_MainWindow();
    this->ui->setupUi(this);

    this->setup_containters();
    this->setup();
    this->setup_binds();

    this->need_redraw = true;
    this->paintEvent(nullptr);
}

MainWindow::~MainWindow(void)
{
    delete this->ui;
    delete this->pixmap;
    delete this->pixmap_current;
    delete this->label_pixmap_holder;
}

void MainWindow::setup(void)
{
    this->label_pixmap_holder = new ClickableLabel(this->ui->frame_result);
    this->label_pixmap_holder->setAlignment(Qt::AlignCenter);
    QCursor cursor;
    cursor.setShape(Qt::CrossCursor);
    this->label_pixmap_holder->setCursor(cursor);
    this->ui->gridLayout->addWidget(this->label_pixmap_holder, 0, 0, 1, 1);

    this->change_slider_color();
    this->choosen_type = CIRCLE;
    this->sync_coefficient_spinbox();

    this->pixmap = new QPixmap(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    this->pixmap->fill(Qt::transparent);

    this->point_center.setX(0);
    this->point_center.setY(0);
}

void MainWindow::setup_containters(void)
{
    this->radio_array_type[0] = this->ui->radioButton_circle;
    this->radio_array_type[1] = this->ui->radioButton_ellipse;

    this->radio_array_mode[0] = this->ui->radioButton_single;
    this->radio_array_mode[1] = this->ui->radioButton_spectrum;

    this->slider_array[0] = this->ui->hslider_red;
    this->slider_array[1] = this->ui->hslider_green;
    this->slider_array[2] = this->ui->hslider_blue;
}

void MainWindow::setup_binds(void)
{
    QObject::connect(this->ui->button_color_display, SIGNAL(released()),
                     this, SLOT(change_slider_color()));
    QObject::connect(this->ui->pushButton_clear, SIGNAL(released()),
                     this, SLOT(on_click_clear()));
    QObject::connect(this->ui->pushButton_build, SIGNAL(released()),
                     this, SLOT(on_click_proceed()));
    QObject::connect(this->ui->pushButton_compare, SIGNAL(released()),
                     this, SLOT(on_click_compare()));
    QObject::connect(this->ui->pushButton_switch_color, SIGNAL(released()),
                     this, SLOT(on_click_color_swap()));

    QObject::connect(this->label_pixmap_holder, SIGNAL(clicked(QMouseEvent *)),
                     this, SLOT(on_click_canvas(QMouseEvent *)));

    for (size_t i = 0; COLOR_SLIDER_AMOUNT > i; i++)
        QObject::connect(this->slider_array[i], SIGNAL(sliderMoved(int)),
                         this, SLOT(color_slider_moved()));

    for (size_t i = 0; RADIO_AMOUNT_TYPE > i; i++)
        QObject::connect(this->radio_array_type[i], SIGNAL(released()),
                         this, SLOT(on_click_radiobutton_type()));

    this->connect_spinboxes();
}

void MainWindow::connect_spinboxes(void)
{
    QObject::connect(this->ui->spinBox_line_center_x, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
    QObject::connect(this->ui->spinBox_line_center_y, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
    QObject::connect(this->ui->spinBox_line_coefficient_x, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
    QObject::connect(this->ui->spinBox_line_coefficient_y, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
}

void MainWindow::disconnect_spinboxes(void)
{
    this->ui->spinBox_line_center_x->disconnect();
    this->ui->spinBox_line_center_y->disconnect();
    this->ui->spinBox_line_coefficient_x->disconnect();
    this->ui->spinBox_line_coefficient_y->disconnect();
}

void MainWindow::update_color_widget(QWidget *const widget,
                                     const QColor *const current)
{
    QString style = QString("background-color: rgb(%1, %2, %3);"
                            "color: rgb(%4, %5, %6)")            \
                    .arg(current->red())                         \
                    .arg(current->green())                       \
                    .arg(current->blue())                        \
                    .arg(MAX_COLOR - current->red())             \
                    .arg(MAX_COLOR - current->green())           \
                    .arg(MAX_COLOR - current->blue());
    widget->setStyleSheet(style);
}

void MainWindow::sync_dots_by_spinbox(void)
{
    this->point_center.setX(this->ui->spinBox_line_center_x->value());
    this->point_center.setY(this->ui->spinBox_line_center_y->value());
}

void MainWindow::sync_spinbox_by_dots(void)
{
    this->ui->spinBox_line_center_x->setValue(this->point_center.x());
    this->ui->spinBox_line_center_y->setValue(this->point_center.y());
}

void MainWindow::sync_coefficient_spinbox(void)
{
    bool enabled = true;

    if (CIRCLE == this->choosen_type)
        enabled = false;

    this->ui->spinBox_line_coefficient_y->setEnabled(enabled);
}

void MainWindow::change_slider_color(void)
{
    this->choosen_color = (this->choosen_color + 1) % COLOR_AMOUNT;

    this->ui->button_color_display \
    ->setText(this->strings_color_display[this->choosen_color]);

    QColor *current = this->colors + this->choosen_color;
    this->ui->hslider_red->setValue(current->red());
    this->ui->hslider_green->setValue(current->green());
    this->ui->hslider_blue->setValue(current->blue());

    this->update_color_widget(this->ui->button_color_display, current);

    if (0 == this->choosen_color)
        this->update_color_widget(this->label_pixmap_holder, current);
}

void MainWindow::color_slider_moved(void)
{
    QColor *current = this->colors + this->choosen_color;

    current->setRed(this->ui->hslider_red->value());
    current->setGreen(this->ui->hslider_green->value());
    current->setBlue(this->ui->hslider_blue->value());

    this->update_color_widget(this->ui->button_color_display, current);

    if (0 == this->choosen_color)
        this->update_color_widget(this->label_pixmap_holder, current);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    this->need_redraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::resize_pixmap(void)
{
    QPixmap *tmp = nullptr;
    int width = this->label_pixmap_holder->width() - MARGIN,
        height = this->label_pixmap_holder->height() - MARGIN;

    if (this->pixmap->width() < width || this->pixmap->height() < height)
    {
        width = width < this->pixmap->width() ? this->pixmap->width() : width;
        height = height < this->pixmap->height() ? this->pixmap->height() : height;
        tmp = new QPixmap(width, height);
    }

    if (tmp)
    {
        tmp->fill(Qt::transparent);
        QPainter painter(tmp);
        painter.drawPixmap(0, 0, *this->pixmap);
        delete this->pixmap;
        this->pixmap = tmp;
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    this->resize_pixmap();

    if (this->need_redraw)
    {
        int width = this->label_pixmap_holder->width() - MARGIN,
            height = this->label_pixmap_holder->height() - MARGIN;

        delete this->pixmap_current;
        this->pixmap_current = new QPixmap(width, height);
        this->pixmap_current->fill(Qt::transparent);

        QPainter painter(this->pixmap_current);
        painter.drawPixmap(0, 0, width, height, *this->pixmap,
                           0, 0, width, height);

        this->need_redraw = false;
    }

    this->label_pixmap_holder->setPixmap(*this->pixmap_current);
}

void MainWindow::on_spinbox_changed(void)
{
    this->sync_dots_by_spinbox();
}

void MainWindow::on_click_clear(void)
{
    this->pixmap->fill(Qt::transparent);
    this->need_redraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::on_click_proceed(void)
{
    size_t choosen_func = this->ui->list_widget_algorithm->currentRow();
    size_t mode = get_active_radio(this->radio_array_mode, RADIO_AMOUNT_MODE);
    size_t radius_a = this->ui->spinBox_line_coefficient_x->value();
    size_t radius_b = radius_a;

    if (ELLIPSE == this->choosen_type)
        radius_b = this->ui->spinBox_line_coefficient_y->value();

    if (SINGLE == mode)
        this->func_array[choosen_func](this->pixmap, this->colors[1], 
                                       this->point_center,
                                       radius_a, radius_b);
    else if (SPECTRUM == mode)
    {
        double start = this->ui->doubleSpinBox_input_spectrum_radius_start->value();
        double end = this->ui->doubleSpinBox_input_spectrum_radius_end->value();

        if (end < start)
        {
            double tmp = start;
            start = end;
            end = tmp;
        }

        double current = start;
        double step = (end - start) / this->ui->spinBox_input_spectrum_amount->value();

        for (; end + EPS > current; current += step)
            this->func_array[choosen_func](this->pixmap, this->colors[1], 
                                           this->point_center,
                                           current * radius_a,
                                           current * radius_b);
    }

    this->need_redraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::on_click_canvas(QMouseEvent *event)
{
    this->disconnect_spinboxes();

    int distance;
    QPoint tmp;

    switch(event->button())
    {
        case (Qt::LeftButton):
            this->point_center.setX(event->x() - MARGIN_HALF);
            this->point_center.setY(event->y() - MARGIN_HALF);
            break;
        case (Qt::RightButton):
            tmp.setX(event->x());
            tmp.setY(event->y());
            distance = get_distance(tmp, this->point_center);
            this->ui->spinBox_line_coefficient_x->setValue(distance);

            if (ELLIPSE == get_active_radio(this->radio_array_type,
                                            RADIO_AMOUNT_TYPE))
                this->ui->spinBox_line_coefficient_y->setValue(distance);

            break;
        default:
            break;
    }

    this->sync_spinbox_by_dots();
    this->connect_spinboxes();
}

void MainWindow::on_click_radiobutton_type(void)
{
    this->choosen_type = get_active_radio(this->radio_array_type,
                                          RADIO_AMOUNT_TYPE);

    this->sync_coefficient_spinbox();
}

void MainWindow::on_click_compare(void)
{
// window
    QWidget *widget_plot = new QWidget;
    QGridLayout *layout = new QGridLayout(widget_plot);
    widget_plot->resize(850, 480);
    widget_plot->setWindowTitle("Сравнение");

// General Ticks
    static QVector<double> x_ticks = {0, 1, 2, 3};
    static QVector<QString> x_ticks_str = {"Каноническое уравнение",
                                           "Параметрическое уравнение",
                                           "Алгоритм Брезенхема",
                                           "Алгоритм Среденей Точки"};

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(x_ticks, x_ticks_str);

// Dot generate
    point_t<int> center = {rand() % MAX_TEST_CORD, rand() % MAX_TEST_CORD};
    int a = rand() % MAX_TEST_CORD,
        b = rand() % MAX_TEST_CORD;

// Time diagram
    QCustomPlot *plt_time = new QCustomPlot(widget_plot);

    QCPTextElement *title_time = new QCPTextElement(plt_time,
            QString("Эллипс с центром в точке (%0, %1) c размерами (%2, %3)")
            .arg(center[0]).arg(center[1]).arg(a).arg(b));
    plt_time->plotLayout()->insertRow(0);
    plt_time->plotLayout()->addElement(0, 0, title_time);

    QVector<double> y;

    for (size_t i = 0; TEST_AMOUNT > i; i++)
        y.append(test_time_func_array[i](center, a, b));

    plt_time->xAxis->setTicker(textTicker);
    plt_time->xAxis->setSubTicks(false);
    plt_time->xAxis->setTickLength(0, 4);
    plt_time->xAxis->setRange(-1, 4);
    plt_time->xAxis->setTickLabelRotation(10);

    plt_time->yAxis->setRange(*(std::min_element(y.constBegin(), y.constEnd()))
                              * 0.9,
                              *(std::max_element(y.constBegin(), y.constEnd()))
                              * 1.1);
    plt_time->yAxis->setLabel("Время (мс)");

    QCPBars *bars = new QCPBars (plt_time->xAxis, plt_time->yAxis);
    bars->addData(x_ticks, y);

    layout->addWidget(plt_time, 0, 0);

    widget_plot->show();
}

void MainWindow::on_click_color_swap(void)
{
    this->colors[this->choosen_color] = this->colors[(this->choosen_color + 1) % 2];
    this->choosen_color++;

    this->change_slider_color();
}

static size_t get_active_radio(QRadioButton **const buttons,
                               const size_t amount)
{
    for (size_t i = 0; amount > i; i++)
        if (buttons[i]->isChecked())
            return i;

    return amount;
}

static int get_distance(QPoint &point1, QPoint &point2)
{
    return sqrt(pow(point1.x() - point2.x(), 2) 
                + pow(point1.y() - point2.y(), 2));
}

