#ifndef _PROJECTOR_FRAME_H_
#define _PROJECTOR_FRAME_H_

#include <QFrame>
#include <QWidget>
#include <QString>

#include "interface_handle.h"

class ProjectorFrame : public QFrame
{
    Q_OBJECT

    public:
        ProjectorFrame(QWidget *parent = nullptr);
        virtual ~ProjectorFrame(void) = 0;

        virtual void set(object_t &object) = 0;
        virtual void save(object_t &object) = 0;
};

#endif

