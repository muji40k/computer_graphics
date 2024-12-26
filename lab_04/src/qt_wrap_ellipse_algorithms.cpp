#include <QPainter>

#include "qt_wrap_ellipse_algorithms.h"
#include "ellipse_algorithms.h"

template <typename T>
static void point_init(point_t<T> point, const QPoint qpoint)
{
    point[0] = qpoint.x();
    point[1] = qpoint.y();
}

int qt_draw_ellipse_canon(QPixmap *const pixmap, const QColor color, 
                          const QPoint center, const int a, const int b)
{
    if (nullptr == pixmap)
        return ERROR_NULL_POINTER_LINE_ALGS_WRAP;

    point_t<int> p_center;
    point_init(p_center, center);

    canon_ellipse_handle_t handle;
    int rc = canon_ellipse_handle_init(handle, p_center, a, b);

    if (EXIT_SUCCESS == rc)
    {
        QPainter painter(pixmap);
        painter.setPen(color);
        unpacked_dot_t points;

        do
        {
            canon_ellipse_handle_get(handle, points);

            for (size_t i = 0; DIMENSIONS > i; i++)
                painter.drawPoint(points.points[i][0], points.points[i][1]);
        }
        while (CONTINUE_DRAW == canon_ellipse_handle_step(handle));
    }

    return rc;
}

int qt_draw_ellipse_parametric(QPixmap *const pixmap, const QColor color, 
                               const QPoint center, const int a, const int b)
{
    if (nullptr == pixmap)
        return ERROR_NULL_POINTER_LINE_ALGS_WRAP;

    point_t<int> p_center;
    point_init(p_center, center);

    parametric_ellipse_handle_t handle;
    int rc = parametric_ellipse_handle_init(handle, p_center, a, b);

    if (EXIT_SUCCESS == rc)
    {
        QPainter painter(pixmap);
        painter.setPen(color);
        unpacked_dot_t points;

        do
        {
            parametric_ellipse_handle_get(handle, points);

            for (size_t i = 0; DIMENSIONS > i; i++)
                painter.drawPoint(points.points[i][0], points.points[i][1]);
        }
        while (CONTINUE_DRAW == parametric_ellipse_handle_step(handle));
    }

    return rc;
}

int qt_draw_ellipse_library(QPixmap *const pixmap, const QColor color, 
                            const QPoint center, const int a, const int b)
{
    QPainter painter(pixmap);

    painter.setPen(color);
    painter.drawEllipse(center, a, b);

    return EXIT_SUCCESS;
}

int qt_draw_ellipse_Bresenham(QPixmap *const pixmap, const QColor color, 
                              const QPoint center, const int a, const int b)
{
    if (nullptr == pixmap)
        return ERROR_NULL_POINTER_LINE_ALGS_WRAP;

    point_t<int> p_center;
    point_init(p_center, center);

    Bresenham_ellipse_handle_t handle;
    int rc = Bresenham_ellipse_handle_init(handle, p_center, a, b);

    if (EXIT_SUCCESS == rc)
    {
        QPainter painter(pixmap);
        painter.setPen(color);
        unpacked_dot_t points;

        do
        {
            Bresenham_ellipse_handle_get(handle, points);

            for (size_t i = 0; DIMENSIONS > i; i++)
                painter.drawPoint(points.points[i][0], points.points[i][1]);
        }
        while (CONTINUE_DRAW == Bresenham_ellipse_handle_step(handle));
    }

    return rc;
}

int qt_draw_ellipse_middle_point(QPixmap *const pixmap, const QColor color, 
                                 const QPoint center, const int a, const int b)
{
    if (nullptr == pixmap)
        return ERROR_NULL_POINTER_LINE_ALGS_WRAP;

    point_t<int> p_center;
    point_init(p_center, center);

    middle_point_ellipse_handle_t handle;
    int rc = middle_point_ellipse_handle_init(handle, p_center, a, b);

    if (EXIT_SUCCESS == rc)
    {
        QPainter painter(pixmap);
        painter.setPen(color);
        unpacked_dot_t points;

        do
        {
            middle_point_ellipse_handle_get(handle, points);

            for (size_t i = 0; DIMENSIONS > i; i++)
                painter.drawPoint(points.points[i][0], points.points[i][1]);
        }
        while (CONTINUE_DRAW == middle_point_ellipse_handle_step(handle));
    }

    return rc;
}

