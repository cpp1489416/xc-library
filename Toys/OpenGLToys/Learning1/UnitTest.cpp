#include <iostream>
#include <cstdio>
#include <QtWidgets/QApplication>

#include "QTGUI/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    w.show();
    return a.exec();
}
    