#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <Core.h>
using namespace XC;

XC_TEST_CASE(ARRAY_TEST)
{
}

class A : public CallableObject
{
public:
    void Get()
    {
        std::cout << mValue << "haha\n";

    }
private:
    int mValue = 5;
};

class AA : public CallableObject
{
public:
    ~AA()
    {

    }
    void Get()
    {
        std::cout << mValue << "haha AA\n";

    }
private:
    int mValue = 5;
};

using EventHandler = XC::Delegate<void>;

class B
{
public:
    void Get()
    {
    }

    void Invoke()
    {
        mEventHandler.Invoke();
    }

    EventHandler mEventHandler;
};

XC_TEST_CASE(DELEGATE_TESET)
{
    A * a = new A();
    AA aa;
    //a->Get();
    B b;
    b.mEventHandler.Add(a, &A::Get);

    b.mEventHandler.Add(&aa, &AA::Get);
    
    b.mEventHandler.Invoke();
    delete a;
    b.mEventHandler.Invoke();
}

int main()
{
    Array<int> array(21);
    system("pause");
}