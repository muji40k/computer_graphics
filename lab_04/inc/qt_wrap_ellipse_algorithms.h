#ifndef _QT_WRAP_LINE_ALGORITHMS_H_
#define _QT_WRAP_LINE_ALGORITHMS_H_

#include <QPoint>
#include <QPixmap>
#include <QColor>

#define ERROR_NULL_POINTER_LINE_ALGS_WRAP 100

typedef int (*ellipse_func_t)(QPixmap *const, const QColor, const QPoint, 
                           const int, const int);

int qt_draw_ellipse_canon(QPixmap *const pixmap, const QColor color, 
                          const QPoint center, const int a, const int b);

int qt_draw_ellipse_parametric(QPixmap *const pixmap, const QColor color, 
                               const QPoint center, const int a, const int b);

int qt_draw_ellipse_library(QPixmap *const pixmap, const QColor color, 
                            const QPoint center, const int a, const int b);

int qt_draw_ellipse_Bresenham(QPixmap *const pixmap, const QColor color, 
                              const QPoint center, const int a, const int b);

int qt_draw_ellipse_middle_point(QPixmap *const pixmap, const QColor color, 
                                 const QPoint center, const int a, const int b);

#endif

