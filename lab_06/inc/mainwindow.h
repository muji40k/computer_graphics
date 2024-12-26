#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QPaintEvent>
#include <QResizeEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>

#include "ui_mainwindow.h"

#define MAX_COLOR 255
#define COLOR_AMOUNT 3

// For pixmap resize
#define MARGIN      10
#define MARGIN_HALF  5

#define PIXER_TARGET_RADIUS 2

class ClickableLabel: public QLabel
{
    Q_OBJECT

    public:
        ClickableLabel(QWidget* parent = Q_NULLPTR);
        ~ClickableLabel();

    signals:
        void clicked(QMouseEvent *event);
        void mouse_moved(QMouseEvent *event);

    private:
        void mousePressEvent(QMouseEvent *event);
        bool eventFilter(QObject *obj, QEvent *event);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui_MainWindow *ui = nullptr;
        ClickableLabel *label_pixmap_holder = nullptr;

        // Points
        size_t figure_amount = 0;
        QVector<QVector<QPoint>> figure;

        bool is_setting_point = false;
        bool is_drawing = false;
        QPoint last_point;
        QPoint current_point;
        QPoint chosen_pixel;

        // Misc
        bool is_shift_pressed = false;
        bool is_ctrl_pressed  = false;

        bool need_redraw = false;
        QPixmap *pixmap = nullptr;
        QPixmap *pixmap_current = nullptr;

        QColor colors[COLOR_AMOUNT] = { QColor(MAX_COLOR, MAX_COLOR, MAX_COLOR), 
                                        QColor(0, 0, 0),
                                        QColor(255, 0, 171)};

        // Functions
        void setup(void);
        void setup_binds(void);
        void connect_spinboxes(void);
        void disconnect_spinboxes(void);
        void update_color_widget(QWidget *const widget, 
                                 const QColor *const current);

        void draw_spaced_line(QPainter &painter, QPoint start, QPoint end);

        // Events
        void resizeEvent(QResizeEvent *event);
        void resize_pixmap(void);
        void paintEvent(QPaintEvent *event);

        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);

        QColor on_click_color(QPushButton *const button);

        void sync_pixel_by_spinbox(void);
        void sync_spinbox_by_pixel(void);

    public:
        MainWindow(void);
        ~MainWindow();

    private slots:
        void on_click_color_background(void);
        void on_click_color_fill(void);
        void on_click_color_edge(void);
        void on_click_clear(void);
        void on_click_canvas(QMouseEvent *event);
        void on_click_circuit(void);
        void on_click_reset(void);
        void on_click_add(void);

        void on_spinbox_changed(void);

        void on_click_fill(void);

        void on_move_mouse(QMouseEvent *event);
};

#endif

