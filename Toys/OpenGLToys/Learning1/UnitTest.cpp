#include <iostream>
#include <cstdio>
#include <QtWidgets/QApplication>

#include "QTGUI/MainWindow.h"
#include "../UnitTest/GUI/MagicCubeWidght.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MagicCubeWidght w(nullptr);
    w.show();
    return a.exec();
}
    