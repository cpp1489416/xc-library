#include "UnitTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UnitTest w;
    w.show();
    return a.exec();
}
