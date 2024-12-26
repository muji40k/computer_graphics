#ifndef _PHONG_SPECULAR_FRAME_H_
#define _PHONG_SPECULAR_FRAME_H_

#include <QSharedPointer>

#include "scattering_frame.h"
#include "ui_phong_specular_frame.h"

class PhongSpecularFrame : public ScatteringFrame
{
    Q_OBJECT

    public:
        PhongSpecularFrame(QWidget *parent = nullptr);
        virtual ~PhongSpecularFrame(void) override;
        virtual void save(scattering_t &scattering) override;
        virtual void set(scattering_t &scattering) override;

    private:
        QSharedPointer<Ui_phong_specular_frame> ui = nullptr;
};

#endif

