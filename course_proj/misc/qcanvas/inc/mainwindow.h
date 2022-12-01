#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QSharedPointer>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QShowEvent>
#include <QVector>
#include <QList>
#include <QPair>

#include "untitled.h"
#include "qcanvas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow(void) = default;

    public slots:
        void canvas_clicked(QMouseEvent event);

    private:
        QSharedPointer<Ui_MainWindow> ui = nullptr;
        QSharedPointer<QCanvas> canvas = nullptr;
        bool needredraw = false;
        QList<QPair<QPoint, int>> list;

        void paintEvent(QPaintEvent *event);
        void showEvent(QShowEvent *event);

};

#endif

