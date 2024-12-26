#ifndef _SCATTERING_FRAME_H_
#define _SCATTERING_FRAME_H_

#include <QFrame>
#include <QWidget>

#include "interface_handle.h"

class ScatteringFrame : public QFrame
{
    Q_OBJECT

    public:
        ScatteringFrame(QWidget *parent = nullptr);
        virtual ~ScatteringFrame(void) = 0;
        virtual void save(scattering_t &scattering) = 0;
        virtual void set(scattering_t &scattering) = 0;
};

#endif

