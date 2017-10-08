#pragma once

#include "XFunctionParser.h"
#include <string>

class XNewton
{
public:
    XNewton();
    ~XNewton();
    void setFunction(XFunctionParser *f);
    void setVariable(std::string variable);
    void setTimes(int times);
    int getTimes() const;
    double newton(double x = 0.0, double y = 0.0, double z = 0.0);
    XFunctionParser *getDifferentiateParser() const;

private:
    XFunctionParser *f;
    XFunctionParser *d;
    std::string variable;
    int times;
};

