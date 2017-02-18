#include "DWidget.h"
#include <QtWidgets/QApplication>

#include <d3d11sdklayers.h>
#include "MainWindow.h"
#include <qmessagebox.h>

class A
{
public:
    A() = delete;

    
};

int main(int argc, char *argv[])
{
    QApplication::setFont(QFont("consolas", 9));
    // D3D11CreateDevice(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
