#include "qt_wrap_line_algorithms.h"
#include <QPainter>

#define MAX_ALPHA 255

template <typename T>
static void point_init(point_t<T> point, const QPoint qpoint)
{
    point[0] = qpoint.x();
    point[1] = qpoint.y();
}

int qt_draw_line_dda(QPixmap *const pixmap, const QColor color, 
                      const QPoint start, const QPoint end)
{
    if (nullptr == pixmap)
        return ERROR_NULL_POINTER_LINE_ALGS_WRAP;

    point_t<int> p_start, p_end;
    point_init(p_start, start);
    point_init(p_end, end);

    dda_line_handle_t handle;
    int rc = dda_line_handle_init(handle, p_start, p_end);

    if (EXIT_SUCCESS == rc)
    {
        QPainter painter(pixmap);
        painter.setPen(color);
        point_t<int> point;

        do
        {
            dda_line_handle_get(handle, point);
            painter.drawPoint(point[0], point[1]);
        }
        while (CONTINUE_DRAW == dda_line_handle_step(handle));
    }

    return rc;
}

int qt_draw_line_BRHM(QPixmap *const pixmap, const QColor color, 
                      const QPoint start, const QPoint end)
{
    if (nullptr == pixmap)
        return ERROR_NULL_POINTER_LINE_ALGS_WRAP;

    point_t<int> p_start, p_end;
    point_init(p_start, start);
    point_init(p_end, end);

    BRHM_line_handle_t handle;
    int rc = BRHM_line_handle_init(handle, p_start, p_end);

    if (EXIT_SUCCESS == rc)
    {
        QPainter painter(pixmap);
        painter.setPen(color);
        point_t<int> point;

        do
        {
            BRHM_line_handle_get(handle, point);
            painter.drawPoint(point[0], point[1]);
        }
        while (CONTINUE_DRAW == BRHM_line_handle_step(handle));
    }

    return rc;
}

int qt_draw_line_BRHMI(QPixmap *const pixmap, const QColor color, 
                       const QPoint start, const QPoint end)
{
    if (nullptr == pixmap)
        return ERROR_NULL_POINTER_LINE_ALGS_WRAP;

    point_t<int> p_start, p_end;
    point_init(p_start, start);
    point_init(p_end, end);

    BRHMI_line_handle_t handle;
    int rc = BRHMI_line_handle_init(handle, p_start, p_end);

    if (EXIT_SUCCESS == rc)
    {
        QPainter painter(pixmap);
        painter.setPen(color);
        point_t<int> point;

        do
        {
            BRHMI_line_handle_get(handle, point);
            painter.drawPoint(point[0], point[1]);
        }
        while (CONTINUE_DRAW == BRHMI_line_handle_step(handle));
    }

    return rc;
}

int qt_draw_line_BRHMA(QPixmap *const pixmap, const QColor color, 
                       const QPoint start, const QPoint end)
{
    if (nullptr == pixmap)
        return ERROR_NULL_POINTER_LINE_ALGS_WRAP;

    point_t<int> p_start, p_end; point_init(p_start, start);
    point_init(p_end, end);

    BRHMA_line_handle_t handle;
    int rc = BRHMA_line_handle_init(handle, p_start, p_end);

    if (EXIT_SUCCESS == rc)
    {
        QPainter painter(pixmap);
        BRHMA_result_t point;
        QColor tmp_color;

        do
        {
            BRHMA_line_handle_get(handle, point);

            tmp_color = color;
            tmp_color.setAlpha(MAX_ALPHA * point.alpha);
            painter.setPen(tmp_color);
            painter.drawPoint(point.dot[0], point.dot[1]);
        }
        while (CONTINUE_DRAW == BRHMA_line_handle_step(handle));
    }

    return rc;
}

int qt_draw_line_WU(QPixmap *const pixmap, const QColor color, 
                    const QPoint start, const QPoint end)
{
    if (nullptr == pixmap)
        return ERROR_NULL_POINTER_LINE_ALGS_WRAP;

    point_t<int> p_start, p_end; point_init(p_start, start);
    point_init(p_end, end);

    WU_line_handle_t handle;
    int rc = WU_line_handle_init(handle, p_start, p_end);

    if (EXIT_SUCCESS == rc)
    {
        QPainter painter(pixmap);
        WU_result_t point;
        QColor tmp_color;

        do
        {
            WU_line_handle_get(handle, point);

            tmp_color = color;
            tmp_color.setAlpha(MAX_ALPHA * point.alpha_start);
            painter.setPen(tmp_color);
            painter.drawPoint(point.start[0], point.start[1]);

            if (2 == point.amount)
            {
                tmp_color = color;
                tmp_color.setAlpha(MAX_ALPHA * point.alpha_end);
                painter.setPen(tmp_color);
                painter.drawPoint(point.end[0], point.end[1]);
            }
        }
        while (CONTINUE_DRAW == WU_line_handle_step(handle));
    }

    return rc;
}

