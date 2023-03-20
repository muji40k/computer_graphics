#ifndef _TAB_PROJECTOR_H_
#define _TAB_PROJECTOR_H_

#include "base_tab.h"
#include "projector_frame.h"

#include <QSharedPointer>
#include <QFrame>

#include "ui_tab_projector.h"

class TabProjector : public BaseTab
{
    Q_OBJECT

    public:
        TabProjector(QWidget *parent = nullptr);
        virtual ~TabProjector(void) = default;

    private slots:
        void typeChanged(int index);

    private:
        QSharedPointer<Ui_tab_projector> ui = nullptr;
        ProjectorFrame *active_frame = nullptr;
};

#endif

