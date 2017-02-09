#include "DirectX11/QTGUI/DirectX11Widget.h"
#include "DXHouseWidget.h"
#include <QtWidgets/QApplication>

using namespace XC::DirectX11::QTGUI;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DXHouseWidget w;
    w.show();
    return a.exec();
}
