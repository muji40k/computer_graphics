#ifndef _PINHOLE_FRAME_H_
#define _PINHOLE_FRAME_H_

#include "projector_frame.h"

#include <QSharedPointer>

#include "ui_pinhole_frame.h"

class PinholeFrame : public ProjectorFrame
{
    Q_OBJECT

    public:
        PinholeFrame(QWidget *parent = nullptr);
        virtual ~PinholeFrame(void) override;

    private:
        QSharedPointer<Ui_frame_pinhole> ui;
};

#endif

