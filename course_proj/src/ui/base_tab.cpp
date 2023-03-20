#include "base_tab.h"

BaseTab::BaseTab(const QString &name, QWidget *parent)
    : QWidget(parent), name(name) {}

const QString &BaseTab::getName(void)
{
    return this->name;
}

BaseTab::~BaseTab(void) {}

#include "moc_base_tab.cpp"

