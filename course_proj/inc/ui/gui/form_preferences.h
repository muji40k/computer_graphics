#ifndef _FORM_PREFERENCES_H_
#define _FORM_PREFERENCES_H_

#include <QWidget>
#include <QSharedPointer>
#include <QCloseEvent>

#include "interface_handle.h"

#include "ui_form_preferences.h"

class FormPreferences : public QWidget
{
    Q_OBJECT

    public:
        FormPreferences(render_pref_t *preferences, QWidget *parent = nullptr);

    private:
        void initFields(void);
        void closeEvent(QCloseEvent* event);
        void saveFields(void);

    private slots:
        void tool_button_clicked(void);

    private:
        render_pref_t *preferences = nullptr;
        QSharedPointer<Ui_form_render_preferences> ui = nullptr;
};


#endif

