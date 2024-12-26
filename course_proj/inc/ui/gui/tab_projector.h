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
        virtual ~TabProjector(void) override = default;

        virtual void set(object_t &object, handle_t &handle) override;
        virtual void save(object_t &object, handle_t &handle) override;

    private slots:
        void typeChanged(int index);

    private:
        QSharedPointer<Ui_tab_projector> ui = nullptr;
        ProjectorFrame *active_frame = nullptr;
        object_t *last = nullptr;
};

#endif

