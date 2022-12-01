#include <QApplication>
#include <ctime>

#include "mainwindow.h"

int main(int argc, char **argv)
{
    srand(time(nullptr));

    QApplication app (argc, argv);
    MainWindow window;

    window.show();

    return app.exec();
}

