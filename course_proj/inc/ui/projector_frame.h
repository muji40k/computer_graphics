#ifndef _PROJECTOR_FRAME_H_
#define _PROJECTOR_FRAME_H_

#include <QFrame>
#include <QWidget>
#include <QString>

class ProjectorFrame : public QFrame
{
    Q_OBJECT

    public:
        ProjectorFrame(QWidget *parent = nullptr);
        virtual ~ProjectorFrame(void) = 0;
};

#endif

