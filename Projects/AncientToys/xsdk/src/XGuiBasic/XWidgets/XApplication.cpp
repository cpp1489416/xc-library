#include "stdafx.h"
#include "XApplication.h"
#include <Windows.h>

XApplication::XApplication()
{
}


XApplication::~XApplication()
{
}

HINSTANCE XApplication::hInstance;

HINSTANCE XApplication::getCurrentHInstance()
{
    return HINSTANCE();
}

void XApplication::setHInstance(HINSTANCE hInstance)
{
    XApplication::hInstance = hInstance;
}

void XApplication::run()
{
}
