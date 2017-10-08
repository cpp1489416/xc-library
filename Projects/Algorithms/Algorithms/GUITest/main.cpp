#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include <AVLTree.h>

int main(int argc, char * *argv)
{

    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();

    return 0;
}