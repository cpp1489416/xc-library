#ifndef XACLASS_H
#define XACLASS_H

class XAClassPrivate;

class XAClass
{
public:
    XAClass();
    ~XAClass();
    XAClassPrivate get();
private:
    
    XAClassPrivate m;
};


#endif