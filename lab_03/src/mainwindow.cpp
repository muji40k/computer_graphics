#include <iostream>
#include <QPalette>
#include <cmath>
#include "qcustomplot.h"
#include "mainwindow.h"
#include "moc_mainwindow.cpp"
#include "line_test.h"

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
    LINE,
    SPECTRUM,
    UNKNOWN
} line_mode_t;

static size_t get_active_radio(QRadioButton **const buttons,
                               const size_t amount);

static int get_distance(QPoint &point1, QPoint &point2);
// static void point_rotate(QPoint &point, QPoint center, double angle);

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
    this->ui->gridLayout->addWidget(this->label_pixmap_holder, 0, 0, 1, 1);

    this->change_slider_color();

    this->pixmap = new QPixmap(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    this->pixmap->fill(Qt::transparent);

    this->point_start.setX(0);
    this->point_start.setY(0);
    this->point_end.setX(0);
    this->point_end.setY(0);
}

void MainWindow::setup_containters(void)
{
    this->radio_array[0] = this->ui->radioButton_line;
    this->radio_array[1] = this->ui->radioButton_spectrum;

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

    QObject::connect(this->label_pixmap_holder, SIGNAL(clicked(QMouseEvent *)),
                     this, SLOT(on_click_canvas(QMouseEvent *)));

    for (size_t i = 0; COLOR_SLIDER_AMOUNT > i; i++)
        QObject::connect(this->slider_array[i], SIGNAL(sliderMoved(int)),
                         this, SLOT(color_slider_moved()));

    for (size_t i = 0; RADIO_AMOUNT > i; i++)
        QObject::connect(this->radio_array[i], SIGNAL(released()),
                         this, SLOT(on_click_radiobutton()));

    this->connect_spinboxes();
}

void MainWindow::connect_spinboxes(void)
{
    QObject::connect(this->ui->spinBox_line_start_x, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
    QObject::connect(this->ui->spinBox_line_start_y, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
    QObject::connect(this->ui->spinBox_line_end_x, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
    QObject::connect(this->ui->spinBox_line_end_y, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
    QObject::connect(this->ui->spinBox_input_center_x, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
    QObject::connect(this->ui->spinBox_input_center_y, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
}

void MainWindow::disconnect_spinboxes(void)
{
    this->ui->spinBox_line_start_x->disconnect();
    this->ui->spinBox_line_start_y->disconnect();
    this->ui->spinBox_line_end_x->disconnect();
    this->ui->spinBox_line_end_y->disconnect();
    this->ui->spinBox_input_center_x->disconnect();
    this->ui->spinBox_input_center_y->disconnect();
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
    size_t mode = get_active_radio(this->radio_array, RADIO_AMOUNT);

    if (LINE == mode)
    {
        this->point_start.setX(this->ui->spinBox_line_start_x->value());
        this->point_start.setY(this->ui->spinBox_line_start_y->value());
        this->point_end.setX(this->ui->spinBox_line_end_x->value());
        this->point_end.setY(this->ui->spinBox_line_end_y->value());
    }
    else if (SPECTRUM == mode)
    {
        this->point_start.setX(this->ui->spinBox_input_center_x->value());
        this->point_start.setY(this->ui->spinBox_input_center_y->value());
    }
}

void MainWindow::sync_spinbox_by_dots(void)
{
    size_t mode = get_active_radio(this->radio_array, RADIO_AMOUNT);

    if (LINE == mode)
    {
        this->ui->spinBox_line_start_x->setValue(this->point_start.x());
        this->ui->spinBox_line_start_y->setValue(this->point_start.y());
        this->ui->spinBox_line_end_x->setValue(this->point_end.x());
        this->ui->spinBox_line_end_y->setValue(this->point_end.y());
    }
    else if (SPECTRUM == mode)
    {
        this->ui->spinBox_input_center_x->setValue(this->point_start.x());
        this->ui->spinBox_input_center_y->setValue(this->point_start.y());
    }
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
    size_t mode = get_active_radio(this->radio_array, RADIO_AMOUNT);

    if (LINE == mode)
        this->func_array[choosen_func](this->pixmap, this->colors[1], 
                                       this->point_start, this->point_end);
    else if (SPECTRUM == mode)
    {
        double step = 2 * M_PI \
                      / this->ui->spinBox_input_spectrum_amount->value(),
               angle = 0;
        QPoint tmp;
        int radius = this->ui->spinBox_input_spectrum_radius->value();

        for (; 2 * M_PI > angle; angle += step)
        {
            tmp.setX(round(this->point_start.x() + radius * cos(angle)));
            tmp.setY(round(this->point_start.y() + radius * sin(angle)));

            this->func_array[choosen_func](this->pixmap, this->colors[1], 
                                           this->point_start, tmp);
        }
    }

    this->need_redraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::on_click_canvas(QMouseEvent *event)
{
    this->disconnect_spinboxes();
    size_t mode = get_active_radio(this->radio_array, RADIO_AMOUNT);
    QPoint *target = nullptr;

    if (LINE == mode)
    {
        switch(event->button())
        {
            case (Qt::LeftButton):
                target = &this->point_start;
                break;
            case (Qt::RightButton):
                target = &this->point_end;
                break;
            default:
                break;
        }
    }
    else if (SPECTRUM == mode)
    {
        QPoint tmp(event->x(), event->y());

        switch(event->button())
        {
            case (Qt::LeftButton):
                target = &this->point_start;
                break;
            case (Qt::RightButton):
                this->ui->spinBox_input_spectrum_radius->setValue(
                        get_distance(tmp, this->point_start));
                break;
            default:
                break;
        }
    }

    if (target)
    {
        target->setX(event->x() - MARGIN_HALF);
        target->setY(event->y() - MARGIN_HALF);
    }

    this->sync_spinbox_by_dots();
    this->connect_spinboxes();
}

void MainWindow::on_click_radiobutton(void)
{
    this->sync_dots_by_spinbox();
}

void MainWindow::on_click_compare(void)
{
// window
    QWidget *widget_plot = new QWidget;
    QGridLayout *layout = new QGridLayout(widget_plot);
    widget_plot->resize(1280, 480);
    widget_plot->setWindowTitle("Сравнение");

// General Ticks
    static QVector<double> x_ticks = {0, 1, 2, 3, 4};
    static QVector<QString> x_ticks_str = {"ЦДА", "Вещественный Брезензем",
                                           "Целочисленный Брезенхем",
                                           "Брезенхем со сглаживанием", "Ву"};

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(x_ticks, x_ticks_str);

// Dot generate
    point_t<int> start = {rand() % MAX_TEST_CORD, rand() % MAX_TEST_CORD},
                 end = {rand() % MAX_TEST_CORD, rand() % MAX_TEST_CORD};

// Time diagram
    QCustomPlot *plt_time = new QCustomPlot(widget_plot);

    QCPTextElement *title_time = new QCPTextElement(plt_time,
            QString("Линия из точки (%0, %1) в точку (%2, %3)")
            .arg(start[0]).arg(start[1]).arg(end[0]).arg(end[1]));
    plt_time->plotLayout()->insertRow(0);
    plt_time->plotLayout()->addElement(0, 0, title_time);

    QVector<double> y;

    for (size_t i = 0; TEST_AMOUNT > i; i++)
        y.append(test_time_func_array[i](start, end));

    plt_time->xAxis->setTicker(textTicker);
    plt_time->xAxis->setSubTicks(false);
    plt_time->xAxis->setTickLength(0, 4);
    plt_time->xAxis->setRange(-1, 5);
    plt_time->xAxis->setTickLabelRotation(10);

    plt_time->yAxis->setRange(*(std::min_element(y.constBegin(), y.constEnd()))
                              * 0.9,
                              *(std::max_element(y.constBegin(), y.constEnd()))
                              * 1.1);
    plt_time->yAxis->setLabel("Время (мс)");

    QCPBars *bars = new QCPBars (plt_time->xAxis, plt_time->yAxis);
    bars->addData(x_ticks, y);

    layout->addWidget(plt_time, 0, 0);

// Stairs graph
    QCustomPlot *plt_stairs = new QCustomPlot(widget_plot);

    double radius = int(sqrt(pow(start[0] - end[0], 2)
                               + pow(start[1] - end[1], 2)));
    QCPTextElement *title_stairs = new QCPTextElement(plt_stairs,
            QString("Зависимость числа ступеней от угла наклона (радиус: %0)")
            .arg(radius));
    plt_stairs->plotLayout()->insertRow(0);
    plt_stairs->plotLayout()->addElement(0, 0, title_stairs);

    QVector<QVector<double>> x_stairs;
    QVector<QVector<double>> y_stairs;
    point_t<int> center = {0, 0}, edge;
    static QVector<QColor> pens = {Qt::blue, Qt::red, Qt::black,
                                   Qt::magenta, Qt::green};

    for (size_t j = 0; TEST_AMOUNT > j; j++)
    {
        x_stairs.append(QVector<double> ());
        y_stairs.append(QVector<double> ());

        for (double i = 0; 360 >= i; i++)
        {
            x_stairs[j].append(i);

            edge[0] = radius * cos(i / 180 * M_PI);
            edge[1] = radius * sin(i / 180 * M_PI);

            y_stairs[j].append(test_stairs_func_array[j](center, edge));
        }

        plt_stairs->addGraph();
        plt_stairs->graph(j)->setPen(pens[j]);
        plt_stairs->graph(j)->setData(x_stairs[j], y_stairs[j]);
        plt_stairs->graph(j)->setName(x_ticks_str[j]);
        plt_stairs->graph(j)->rescaleAxes();
    }

    plt_stairs->legend->setVisible(true);
    plt_stairs->yAxis->setLabel("Число ступенек");
    plt_stairs->xAxis->setLabel("Угол (градусы)");

    layout->addWidget(plt_stairs, 0, 1);

    widget_plot->show();
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

// static void point_rotate(QPoint &point, QPoint center, double angle)
// {
//     point.setX(point.x() - center.x());
//     point.setY(point.y() - center.y());
//  
//     int x = point.x(),
//         y = point.y();
//     double c_cos = cos(angle),
//            c_sin = sin(angle);
//  
//     point.setX(x * c_cos - y * c_sin + center.x());
//     point.setY(x * c_sin + y * c_cos + center.y());
// }

