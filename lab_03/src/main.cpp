#include <QApplication>
#include "mainwindow.h"
#include <sys/time.h>

int main(int argc, char **argv)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    srand(time.tv_sec);

    QApplication *app = new QApplication(argc, argv);
    MainWindow *window = new MainWindow();

    window->show();

    int rc = app->exec();

    delete window;
    delete app;

    return rc;
}

