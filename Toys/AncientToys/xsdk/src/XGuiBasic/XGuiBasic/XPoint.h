#ifndef XPOINT_H
#define XPOINT_H

#include "XGlobal.h"

class XPoint
{
public:
    XPoint(xreal x = 0.0, xreal y = 0.0) : x(x), y(y) {}
    inline xreal getX() const { return x; }
    inline xreal getY() const { return y; }
    inline xreal & rX() { return x; }
    inline xreal & rY() { return y; }

private:
    xreal x;
    xreal y;
};

#endif