#ifndef _QT_WRAP_LINE_ALGORITHMS_H_
#define _QT_WRAP_LINE_ALGORITHMS_H_

#include <QPoint>
#include <QPixmap>
#include <QColor>
#include "line_algorithms.h"

#define ERROR_NULL_POINTER_LINE_ALGS_WRAP 100

typedef int (*line_func_t)(QPixmap *const, const QColor, const QPoint, 
                           const QPoint);

int qt_draw_line_dda(QPixmap *const pixmap, const QColor color, 
                     const QPoint start, const QPoint end);

int qt_draw_line_BRHM(QPixmap *const pixmap, const QColor color, 
                      const QPoint start, const QPoint end);

int qt_draw_line_BRHMI(QPixmap *const pixmap, const QColor color, 
                       const QPoint start, const QPoint end);

int qt_draw_line_BRHMA(QPixmap *const pixmap, const QColor color, 
                       const QPoint start, const QPoint end);

int qt_draw_line_WU(QPixmap *const pixmap, const QColor color, 
                    const QPoint start, const QPoint end);

#endif

