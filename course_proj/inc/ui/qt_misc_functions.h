#ifndef _QT_MISC_FUNCTIONS_H_
#define _QT_MISC_FUNCTIONS_H_

#include <QWidget>
#include <QColor>
#include "intensity.h"

void setBackgroundColor(QWidget *widget, const Intensity<> &intensity);

void setBackgroundColor(QWidget *widget, const QColor &color);

#endif

