#include "XNewton.h"

XNewton::XNewton()
{
    f = nullptr;
    d = nullptr;
    times = 50;
}

XNewton::~XNewton()
{
    delete d;
}

void XNewton::setFunction(XFunctionParser *f)
{
    delete d;
    d = nullptr;
    this->f = f;
}

void XNewton::setVariable(std::string variable)
{
    this->variable = variable;
    delete d;
    d = f->getDifferentiate(variable);
}

void XNewton::setTimes(int times)
{
    this->times = times;
}

int XNewton::getTimes() const
{
    return times;
}

double XNewton::newton(double x, double y, double z)
{
    double ans;
    if (variable == "x")
    {
        ans = x;    
        for (int i = 0; i < times; i++)
        {
            double valD = d->getFunction(ans, y, z);
            double  fVal = f->getFunction(ans, y, z);
            if (fabs(fVal) < 0.000001)
            {
                return ans;
            }
            if (fabs(valD) < 0.000001)
            {
                return 0.0;
            }
            if (fabs(ans - x) > 0.1)
            {
                return 0.0;
            }
            ans -= fVal / valD;
        }
        return 0.0;
    }
    else if (variable == "y")
    {
        ans = y;
        for (int i = 0; i < times; i++)
        {
            double valD = d->getFunction(x, ans, z);
            double  fVal = f->getFunction(x, ans, z);
            if (fabs(fVal) < 0.000001)
            {
                return ans;
            }
            if (fabs(valD) < 0.000001)
            {
                return 0.0;
            }  
            if (fabs(ans - y) > 0.1)
            {
                return 0.0;
            }
            ans -= fVal / valD;
        }
        return 0.0;
    }
    else
    {
        ans = x;
        for (int i = 0; i < times; i++)
        {
            double valD = d->getFunction(x, y, ans);
            if (fabs(valD) < 0.0001)
            {
                return 0.0;
            }
            ans = ans - f->getFunction(x, y, ans) / valD;
        }
        return ans;
    }
    return 0.0;
}

XFunctionParser *XNewton::getDifferentiateParser() const
{
    return d;
}