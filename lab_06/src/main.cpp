#include <QApplication>
#include "mainwindow.h"
#include <sys/time.h>

int main(int argc, char **argv)
{
    QApplication *app = new QApplication(argc, argv);
    MainWindow *window = new MainWindow();

    window->show();

    int rc = app->exec();

    delete window;
    delete app;

    return rc;
}

