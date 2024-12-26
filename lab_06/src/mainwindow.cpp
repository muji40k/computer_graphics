#include <iostream>
#include <cmath>
#include "mainwindow.h"

#include <QList>
#include <QPainter>
#include <QColorDialog>

#define EPS 1e-8
#define DEFAULT_WIDTH  1500
#define DEFAULT_HEIGHT 1000

ClickableLabel::ClickableLabel(QWidget* parent) : QLabel(parent)
{
    this->installEventFilter(this);
    QWidget::setMouseTracking(true);
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked(event);
}

bool ClickableLabel::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove)
        emit mouse_moved(static_cast<QMouseEvent *>(event));

    return QLabel::eventFilter(obj, event);
}

MainWindow::MainWindow(void)
{
    this->ui = new Ui_MainWindow();
    this->ui->setupUi(this);

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
    this->label_pixmap_holder = new ClickableLabel(this->ui->centralwidget);
    this->label_pixmap_holder->setAlignment(Qt::AlignCenter);
    QCursor cursor;
    cursor.setShape(Qt::CrossCursor);
    this->label_pixmap_holder->setCursor(cursor);
    this->ui->horizontalLayout->addWidget(this->label_pixmap_holder);
    this->ui->horizontalLayout->setStretch(1, 1);

    this->pixmap = new QPixmap(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    this->pixmap->fill(Qt::transparent);

    this->update_color_widget(this->ui->pushButton_color_background,
                              this->colors);
    this->update_color_widget(this->ui->pushButton_color_fill,
                              this->colors + 1);
    this->update_color_widget(this->ui->pushButton_color_border,
                              this->colors + 2);
    this->update_color_widget(this->label_pixmap_holder, this->colors);
}

void MainWindow::setup_binds(void)
{
    QObject::connect(this->ui->pushButton_color_background, SIGNAL(released()),
                     this, SLOT(on_click_color_background()));
    QObject::connect(this->ui->pushButton_color_fill, SIGNAL(released()),
                     this, SLOT(on_click_color_fill()));
    QObject::connect(this->ui->pushButton_color_border, SIGNAL(released()),
                     this, SLOT(on_click_color_edge()));
    QObject::connect(this->ui->pushButton_circuit, SIGNAL(released()),
                     this, SLOT(on_click_circuit()));
    QObject::connect(this->ui->pushButton_reset, SIGNAL(released()),
                     this, SLOT(on_click_reset()));
    QObject::connect(this->ui->pushButton_add, SIGNAL(released()),
                     this, SLOT(on_click_add()));
    QObject::connect(this->ui->pushButton_fill, SIGNAL(released()),
                     this, SLOT(on_click_fill()));
    QObject::connect(this->ui->pushButton_clear, SIGNAL(released()),
                     this, SLOT(on_click_clear()));

    QObject::connect(this->label_pixmap_holder, SIGNAL(mouse_moved(QMouseEvent *)),
                     this, SLOT(on_move_mouse(QMouseEvent *)));
    QObject::connect(this->label_pixmap_holder, SIGNAL(clicked(QMouseEvent *)),
                     this, SLOT(on_click_canvas(QMouseEvent *)));

    this->connect_spinboxes();
}

void MainWindow::connect_spinboxes(void)
{
    QObject::connect(this->ui->spinBox_choosen_x, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
    QObject::connect(this->ui->spinBox_choosen_y, SIGNAL(valueChanged(int)),
                     this, SLOT(on_spinbox_changed()));
}

void MainWindow::disconnect_spinboxes(void)
{
    this->ui->spinBox_choosen_x->disconnect();
    this->ui->spinBox_choosen_y->disconnect();
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

void MainWindow::draw_spaced_line(QPainter &painter, QPoint start, QPoint end)
{
    QImage img = static_cast<QPixmap *>(painter.device())->toImage();
    QColor color = this->colors[2];
    painter.setPen(color);

    int len = end.y() - start.y();
    double dx = (double)(end.x() - start.x()) / abs(len);
    int dy = 1;

    if (0 > len)
        dy = -1;

    len = abs(len);

    for (int i = 0, x, y; len >= i; i++)
    {
        x = round(dx * i + start.x());
        y = dy * i + start.y();

        if ((0 != i && len != i) && color == QColor(img.pixel(x, y)))
        {
            if (color == QColor(img.pixel(x + 1, y)))
            {
                painter.setPen(Qt::transparent);
                painter.drawPoint(x + 1, y);
                painter.setPen(color);
            }
            else
                painter.drawPoint(x + 1, y);
        }

        painter.drawPoint(x, y);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    this->need_redraw = true;
    this->repaint();
    // this->paintEvent(nullptr);
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

        painter.setPen(this->colors[2]);
        int i = 0;
        QPoint previous;
        int limit = this->figure.size();

        if (!this->is_drawing)
        {
            if (this->is_setting_point)
                limit--;

            for (; limit > i; i++)
            {
                previous = this->figure[i][0];

                for (int j = 1; this->figure[i].size() > j; j++)
                {
                    painter.drawLine(previous, this->figure[i][j]);
                    previous = this->figure[i][j];
                }

                painter.drawLine(previous, this->figure[i][0]);
            }

            if (this->is_setting_point)
            {
                previous = this->figure[i][0];

                for (int j = 1; this->figure[i].size() > j; j++)
                {
                    painter.drawLine(previous, this->figure[i][j]);
                    previous = this->figure[i][j];
                }

                painter.drawLine(this->last_point, this->current_point);
            }
        }

        painter.setBrush(this->colors[2]);
        painter.drawEllipse(this->chosen_pixel,
                            PIXER_TARGET_RADIUS, PIXER_TARGET_RADIUS);

        this->need_redraw = false;
    }

    this->label_pixmap_holder->setPixmap(*this->pixmap_current);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case (Qt::Key_Shift):
            this->is_shift_pressed = true;
            break;
        case (Qt::Key_Control):
            this->is_ctrl_pressed = true;
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case (Qt::Key_Shift):
            this->is_shift_pressed = false;
            break;
        case (Qt::Key_Control):
            this->is_ctrl_pressed = false;
            break;
        case (Qt::Key_C):
            this->on_click_circuit();
            break;
    }
}

QColor MainWindow::on_click_color(QPushButton *const button)
{
    QColor color = QColorDialog::getColor();
    this->update_color_widget(button, &color);

    return color;
}

void MainWindow::sync_pixel_by_spinbox(void)
{
    this->chosen_pixel.setX(this->ui->spinBox_choosen_x->value());
    this->chosen_pixel.setY(this->ui->spinBox_choosen_y->value());
    this->need_redraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::sync_spinbox_by_pixel(void)
{
    this->disconnect_spinboxes();
    this->ui->spinBox_choosen_x->setValue(this->chosen_pixel.x());
    this->ui->spinBox_choosen_y->setValue(this->chosen_pixel.y());
    this->connect_spinboxes();
}

void MainWindow::on_click_color_background(void)
{
    this->colors[0] = this->on_click_color(this->ui->pushButton_color_background);
    this->update_color_widget(this->label_pixmap_holder, this->colors);
}

void MainWindow::on_click_color_fill(void)
{
    this->colors[1] = this->on_click_color(this->ui->pushButton_color_fill);
}

void MainWindow::on_click_color_edge(void)
{
    this->colors[2] = this->on_click_color(this->ui->pushButton_color_border);
    this->need_redraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::on_click_clear(void)
{
    this->pixmap->fill(Qt::transparent);
    this->need_redraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::on_click_canvas(QMouseEvent *event)
{
    if (Qt::RightButton == event->button())
    {
        if (!this->is_ctrl_pressed)
            this->on_click_circuit();
        else
        {
            this->chosen_pixel.setX(event->x() - MARGIN_HALF);
            this->chosen_pixel.setY(event->y() - MARGIN_HALF);
            this->sync_spinbox_by_pixel();
            this->need_redraw = true;
        }
    }
    else if (Qt::LeftButton == event->button())
    {
        if (!this->is_setting_point)
        {
            this->is_setting_point = true;
            this->figure.append(QVector<QPoint> ());
            this->current_point.setX(event->x() - MARGIN_HALF);
            this->current_point.setY(event->y() - MARGIN_HALF);
            this->ui->listWidget_edges->addItem(QString("Фигура %0:")
                                                .arg(this->figure.size()));
        }

        if (this->last_point == this->current_point)
            return;

        this->last_point = this->current_point;
        this->figure[this->figure.size() - 1].append(this->last_point);
        this->need_redraw = true;

        int i = this->figure.size() - 1;
        int j = this->figure[i].size() - 1;
        this->ui->listWidget_edges->addItem(QString("- Точка %0: (%1, %2)")
                                            .arg(this->figure[i].size())
                                            .arg(this->figure[i][j].x())
                                            .arg(this->figure[i][j].y()));
    }
}

void MainWindow::on_click_circuit(void)
{
    this->is_setting_point = false;
    this->need_redraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::on_click_reset(void)
{
    this->is_setting_point = false;
    this->figure.clear();
    this->ui->listWidget_edges->clear();
    this->need_redraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::on_click_add(void)
{
    this->current_point.setX(this->ui->spinBox_add_x->value());
    this->current_point.setY(this->ui->spinBox_add_y->value());

    QPointF point (this->ui->spinBox_add_x->value() + MARGIN_HALF,
                   this->ui->spinBox_add_y->value() + MARGIN_HALF);
    QMouseEvent event(QEvent::MouseMove, point, Qt::LeftButton,
                      Qt::MouseButtons (),
                      Qt::KeyboardModifiers ());
    this->on_click_canvas(&event);
}

void MainWindow::on_spinbox_changed(void)
{
    this->sync_pixel_by_spinbox();
}

void MainWindow::on_click_fill(void)
{
    this->is_drawing = true;

    QPainter painter(this->pixmap);
    painter.setPen(this->colors[2]);

    for (int i = 0; this->figure.size() > i; i++)
    {
        QPoint previous = this->figure[i][0];

        for (int j = 1; this->figure[i].size() > j; j++)
        {
            painter.drawLine(previous, this->figure[i][j]);
            previous = this->figure[i][j];
        }

        painter.drawLine(previous, this->figure[i][0]);
    }

    QImage img = this->pixmap->toImage();
    QPainter painter_img(&img);
    painter_img.setPen(this->colors[1]);

    QList<QPoint> stack;
    stack.push_front(this->chosen_pixel);
    QRgb target_color = img.pixel(this->chosen_pixel);
    QPoint current, tmp;
    int left, right;
    int x_limit = img.width(),
        y_limit = img.height();
    bool is_upper, is_lower;

    while (!stack.empty())
    {
        current = stack.first();
        stack.pop_front();
        left = current.x();
        right = current.x() + 1;

        for (; left >= 0 && target_color == img.pixel(left, current.y());
             left--)
            painter_img.drawPoint(left, current.y());

        left++;

        for (; x_limit > right && target_color == img.pixel(right, current.y());
             right++)
            painter_img.drawPoint(right, current.y());

        is_upper = is_lower = false;

        for (int i = left; right > i; i++)
        {
            if (0 > current.y() - 1 || target_color != img.pixel(i, current.y() - 1))
                is_upper = false;
            else
            {
                if (!is_upper)
                {
                    tmp.setX(i);
                    tmp.setY(current.y() - 1);
                    stack.push_front(tmp);
                }

                is_upper = true;
            }

            if (y_limit <= current.y() + 1 || target_color != img.pixel(i, current.y() + 1))
                is_lower = false;
            else
            {
                if (!is_lower)
                {
                    tmp.setX(i);
                    tmp.setY(current.y() + 1);
                    stack.push_front(tmp);
                }

                is_lower = true;
            }
        }

        if (this->ui->checkBox_delay->isChecked())
        {
            painter.drawImage(0, 0, img);
            this->need_redraw = true;
            this->repaint();
        }
    }

    // painter_img.end();
    painter.drawImage(0, 0, img);

    this->is_drawing = false;
    this->need_redraw = true;
    this->paintEvent(nullptr);
}

void MainWindow::on_move_mouse(QMouseEvent *event)
{
    if (!this->is_setting_point)
        return;

    this->current_point.setX(event->x() - MARGIN_HALF);
    this->current_point.setY(event->y() - MARGIN_HALF);

    if (this->is_shift_pressed && 0 != this->figure.size()
        && 0 != this->figure[this->figure.size() - 1].size())
    {
        int dx = abs(event->x() - this->last_point.x()),
            dy = abs(event->y() - this->last_point.y());

        if (dx >= dy)
            this->current_point.setY(this->last_point.y());
        else
            this->current_point.setX(this->last_point.x());
    }

    this->need_redraw = true;
}

#include "moc_mainwindow.cpp"

