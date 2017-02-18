#pragma once

#include "XGlobal.h"

class XSize
{
public:
    XSize(xreal width = 0.0, xreal height = 0.0) : width(0.0), height(0.0) {};

    xreal getWidth() const;
    xreal getHeight() const;
    xreal & rWidth();
    xreal & rHeight();

private:
    xreal width;
    xreal height;
};

