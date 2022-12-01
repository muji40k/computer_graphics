#ifndef _QCANVAS_H_
#define _QCANVAS_H_

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>

class QCanvas : public QLabel
{
    Q_OBJECT

    signals:
        void clicked(QMouseEvent event);
        void released(QMouseEvent event);
        void mouseMoved(QMouseEvent event);

    public:
        QCanvas(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
        QCanvas(const QCanvas &canvas);
        QCanvas(QCanvas &&canvas);
        ~QCanvas(void);

        operator QPixmap *(void);
        operator QPixmap &(void);

        void update(void);

    public:
        static const int margin = 5;

    private:
        bool eventFilter(QObject *object, QEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

        void resizeEvent(QResizeEvent *event);

        void setupConnections(void);

        QMouseEvent adjustMousePosition(QMouseEvent &event);

        bool enlargeBuffer(const int width, const int height);
        bool resizeScreen(const int width, const int height);

        static bool enlargePixmap(QPixmap *(&pixmap),
                                  const int width, const int height);
        static void resizePixmap(QPixmap *(&pixmap),
                                 const int width, const int height,
                                 bool save = false);

    private:
        QPixmap *pixmap_buffer = nullptr;
        QPixmap *pixmap_screen = nullptr;
};

#endif

