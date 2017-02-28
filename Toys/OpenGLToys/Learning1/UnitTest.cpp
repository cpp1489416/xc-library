#include <iostream>
#include <cstdio>
#include <QtWidgets/QApplication>

#include "QTGUI/MainWindow.h"
#include "../UnitTest/GUI/MagicCubeWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MagicCubeWidget w(nullptr);
    w.show();
    return a.exec();
}
    