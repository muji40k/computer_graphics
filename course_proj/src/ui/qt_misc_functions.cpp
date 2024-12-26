#include "qt_misc_functions.h"

static void setBackgroundColor(QWidget *widget, int r, int g, int b)
{
    widget->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                          .arg(r).arg(g).arg(b));
}

void setBackgroundColor(QWidget *widget, const Intensity<> &intensity)
{
    setBackgroundColor(widget, int(intensity[0] * 255), int(intensity[1] * 255),
                       int(intensity[2] * 255));
}

void setBackgroundColor(QWidget *widget, const QColor &color)
{
    setBackgroundColor(widget, color.red(), color.green(), color.blue());
}

