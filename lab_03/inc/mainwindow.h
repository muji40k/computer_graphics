#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QPaintEvent>
#include <QResizeEvent>
#include <QLabel>
#include <QMouseEvent>
#include "ui_mainwindow.h"
#include "qt_wrap_line_algorithms.h"
#define MAX_COLOR 255
#define RADIO_AMOUNT 2
#define COLOR_AMOUNT 2
#define COLOR_SLIDER_AMOUNT 3
#define MARGIN      10
#define MARGIN_HALF  5

class ClickableLabel: public QLabel
{
    Q_OBJECT

    public:
        ClickableLabel(QWidget* parent = Q_NULLPTR);
        ~ClickableLabel();

    signals:
        void clicked(QMouseEvent *event);

    private:
        void mousePressEvent(QMouseEvent *event);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui_MainWindow *ui = nullptr;
        ClickableLabel *label_pixmap_holder = nullptr;

        // Holders
        QRadioButton *radio_array[RADIO_AMOUNT] = { nullptr };
        QSlider *slider_array[COLOR_SLIDER_AMOUNT] = { nullptr };

        // Misc
        bool need_redraw = false;
        QPixmap *pixmap = nullptr;
        QPixmap *pixmap_current = nullptr;

        size_t choosen_color = -1;
        QColor colors[COLOR_AMOUNT] = { QColor(MAX_COLOR, MAX_COLOR, 
                                                    MAX_COLOR), 
                                        QColor(0, 0, 0) };
        QString strings_color_display[COLOR_AMOUNT] = { QString("Фон"),
                                                        QString("Линия") };

        line_func_t func_array[5] = {qt_draw_line_dda, 
                                     qt_draw_line_BRHM,
                                     qt_draw_line_BRHMI,
                                     qt_draw_line_BRHMA,
                                     qt_draw_line_WU};

        QPoint point_start, point_end;

        // Functions
        void setup(void);
        void setup_containters(void);
        void setup_binds(void);
        void connect_spinboxes(void);
        void disconnect_spinboxes(void);
        void update_color_widget(QWidget *const widget, 
                                 const QColor *const current);
        void sync_dots_by_spinbox(void);
        void sync_spinbox_by_dots(void);

        // Events
        void resizeEvent(QResizeEvent *event);
        void resize_pixmap(void);
        void paintEvent(QPaintEvent *event);

    public:
        MainWindow(void);
        ~MainWindow();

    private slots:
        void change_slider_color(void);
        void color_slider_moved(void);

        void on_spinbox_changed(void);

        void on_click_clear(void);
        void on_click_proceed(void);
        void on_click_canvas(QMouseEvent *event);
        void on_click_radiobutton(void);
        void on_click_compare(void);
};

#endif

