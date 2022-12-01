#include "qcanvas.h"

QCanvas::QCanvas(QWidget *parent, Qt::WindowFlags f) : QLabel(parent, f)
{
    this->setStyleSheet(QString("background-color: rgb(255, 255, 255);"));
    this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    this->setupConnections();
    this->update();
}

QCanvas::QCanvas(const QCanvas &canvas)
    : QCanvas(static_cast<QWidget *>(canvas.parent()))
{
    if (this->pixmap_buffer)
        delete this->pixmap_buffer;

    if (this->pixmap_screen)
        delete this->pixmap_screen;

    this->pixmap_buffer = new QPixmap(*canvas.pixmap_buffer);
    this->pixmap_screen = new QPixmap(*canvas.pixmap_screen);
    this->update();
}

QCanvas::QCanvas(QCanvas &&canvas)
    : QCanvas(static_cast<QWidget *>(canvas.parent()))
{
    if (this->pixmap_buffer)
        delete this->pixmap_buffer;

    if (this->pixmap_screen)
        delete this->pixmap_screen;

    this->pixmap_buffer = canvas.pixmap_buffer;
    canvas.pixmap_buffer = nullptr;

    this->pixmap_screen = canvas.pixmap_screen;
    canvas.pixmap_screen = nullptr;

    this->update();
}

QCanvas::~QCanvas(void)
{
    if (this->pixmap_buffer)
        delete this->pixmap_buffer;

    if (this->pixmap_screen)
        delete this->pixmap_screen;
}

QCanvas::operator QPixmap *(void)
{
    return this->pixmap_buffer;
}

QCanvas::operator QPixmap &(void)
{
    return *this->pixmap_buffer;
}

void QCanvas::update(void)
{
    int width = this->width() - 2 * this->margin,
        height = this->height() - 2 * this->margin;

    this->enlargeBuffer(width, height);
    this->resizeScreen(width, height);

    this->pixmap_screen->fill(Qt::transparent);
    QPainter painter (this->pixmap_screen);
    painter.drawPixmap(0, 0, width, height, *this->pixmap_buffer,
                       0, 0, width, height);

    this->setPixmap(*this->pixmap_screen);
}

bool QCanvas::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseMove)
        emit this->mouseMoved(this->adjustMousePosition(*static_cast<QMouseEvent *>(event)));

    return QLabel::eventFilter(object, event);
}

void QCanvas::mousePressEvent(QMouseEvent *event)
{
    emit this->clicked(this->adjustMousePosition(*event));
    QLabel::mousePressEvent(event);
}

void QCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    emit this->released(this->adjustMousePosition(*event));
    QLabel::mouseReleaseEvent(event);
}

void QCanvas::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);

    int width = this->width() - 2 * this->margin,
        height = this->height() - 2 * this->margin;

    this->enlargeBuffer(width, height);
    this->update();
}

void QCanvas::setupConnections(void)
{
    this->installEventFilter(this);
    QWidget::setMouseTracking(true);
}

QMouseEvent QCanvas::adjustMousePosition(QMouseEvent &event)
{
    int x = event.x(),
        y = event.y();

    if (this->margin > x)
        x = 0;
    else if (this->width() - this->margin < x)
        x -= this->width() - 2 * this->margin;
    else
        x -= this->margin;

    if (this->margin > y)
        y = 0;
    else if (this->height() - this->margin < y)
        y -= this->height() - 2 * this->margin;
    else
        y -= this->margin;

    return QMouseEvent(event.type(), QPointF(x, y), event.button(),
                       event.buttons(), event.modifiers());
}

bool QCanvas::enlargeBuffer(const int width, const int height)
{
    return QCanvas::enlargePixmap(this->pixmap_buffer, width, height);
}

bool QCanvas::resizeScreen(const int width, const int height)
{
    if (this->pixmap_screen
        && this->pixmap_screen->width() == width
        && this->pixmap_screen->height() == height)
        return false;

    QCanvas::resizePixmap(this->pixmap_screen, width, height);

    return true;
}

bool QCanvas::enlargePixmap(QPixmap *(&pixmap), const int width, const int height)
{
    bool mark = false;
    int w = width,
        h = height;

    if (pixmap)
    {
        if (width > pixmap->width())
            mark = true;
        else
            w = pixmap->width();

        if (height > pixmap->height())
            mark = true;
        else
            h = pixmap->height();
    }
    else
        mark = true;

    if (mark)
        QCanvas::resizePixmap(pixmap, w, h, true);

    return mark;
}

void QCanvas::resizePixmap(QPixmap *(&pixmap), const int width, const int height,
                           bool save)
{
    QPixmap *new_pixmap = new QPixmap(width, height);
    new_pixmap->fill(Qt::transparent);

    if (pixmap)
    {
        if (save)
        {
            QPainter painter (new_pixmap);
            int w = width, h = height;

            if (pixmap->width() < w)
                w = pixmap->width();

            if (pixmap->height() < h)
                h = pixmap->height();

            painter.drawPixmap(0, 0, w, h, *pixmap, 0, 0, w, h);
        }

        delete pixmap;
    }

    pixmap = new_pixmap;
}

#include "moc_qcanvas.cpp"

