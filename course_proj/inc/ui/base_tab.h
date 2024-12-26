#ifndef _BASE_TAB_H_
#define _BASE_TAB_H_

#include <QWidget>
#include <QString>

#include "interface_handle.h"

class BaseTab : public QWidget
{
    Q_OBJECT

    public:
        BaseTab(const QString &name, QWidget *parent = nullptr);
        virtual ~BaseTab(void) = 0;

        const QString &getName(void);

        virtual void set(object_t &object, handle_t &handle) = 0;
        virtual void save(object_t &object, handle_t &handle) = 0;

    private:
        QString name;
};

#endif

