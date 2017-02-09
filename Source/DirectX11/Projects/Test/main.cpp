#include "Test.h"
#include <QtWidgets/QApplication>
#include <Common\Basic.h>
#include <qmessagebox.h>
#include <cassert>

using namespace XC::DirectX11::Common;

XC_TEST_CASE(dfasf)
{
    XC_TEST_ASSERT(1 == 1);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Test w;
    w.show();

    int v = a.exec();
    //int * as = new int;
    _CrtDumpMemoryLeaks();
    XC::DirectX11::Common::Fuck();
    return v;
}
