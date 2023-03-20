#ifndef _BASE_TAB_H_
#define _BASE_TAB_H_

#include <QWidget>
#include <QString>

class BaseTab : public QWidget
{
    Q_OBJECT

    public:
        BaseTab(const QString &name, QWidget *parent = nullptr);
        virtual ~BaseTab(void) = 0;

        const QString &getName(void);

    private:
        QString name;
};

#endif

