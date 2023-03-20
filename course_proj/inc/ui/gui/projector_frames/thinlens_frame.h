#ifndef _THINLENS_FRAME_H_
#define _THINLENS_FRAME_H_

#include "projector_frame.h"

#include <QSharedPointer>

#include "ui_thinlens_frame.h"

class ThinLensFrame : public ProjectorFrame
{
    Q_OBJECT

    public:
        ThinLensFrame(QWidget *parent = nullptr);
        virtual ~ThinLensFrame(void) override;

    private slots:
        void autofocus(void);

    private:
        QSharedPointer<Ui_frame_thinlens> ui;
};

#endif

