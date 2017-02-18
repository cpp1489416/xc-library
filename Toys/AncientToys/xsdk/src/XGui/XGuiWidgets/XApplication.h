#pragma once
#include "XWindowsDefines.h"
#include <XAutoPointer.h>

class XApplicationPrivate;

class XApplication
{
public:
    XApplication();
    ~XApplication();
    void run();

private:
    XAutoPointer<XApplicationPrivate> m;
};

