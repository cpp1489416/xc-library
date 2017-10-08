#include "TangQTTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TangQTTest w;
    w.show();
    return a.exec();
}
namespace XC
{
    namespace GUI
    {
        void Main()
        {
            main(0, nullptr);
        }
    }
}

