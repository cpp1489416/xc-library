#include "stdafx.h"
#include "XAClass.h"

class XAClassPrivate
{
public:
    int value;
};

XAClass::XAClass()
{
}

XAClass::~XAClass()
{
}

XAClassPrivate XAClass::get()
{
    return XAClassPrivate();
}
