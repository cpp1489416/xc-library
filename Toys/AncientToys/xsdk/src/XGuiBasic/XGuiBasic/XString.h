#ifndef XSTRING_H
#define XSTRING_H

class XStringPrivate;

class XString
{
public:
    XString();
    ~XString();


private:
    XStringPrivate * m;
};

#endif