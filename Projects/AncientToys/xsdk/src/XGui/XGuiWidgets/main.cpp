#include "stdafx.h"
#include "XApplication.h"
#include "XWidget.h"
#include "MWidget.h"
void xMain()
{
    XApplication application;
    MWidget w;
    w.show();
    application.run();
}