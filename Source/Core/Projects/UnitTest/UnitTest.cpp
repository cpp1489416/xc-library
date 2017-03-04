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
    Array<int *> array(21);
    for (int i = 0; i < 21; ++i)
    {
        array[i] = new int(i);
    }

    for (int i = 0; i < 21; ++i)
    {
        std::cout << *array[i] << " ";
    }
    std::cout << std::endl;

    auto itr = array.GetIteratorAt(2);
    delete *itr;
    array.Erase(array.GetIteratorAt(2));

    for (int i = 0; i < array.GetSize(); ++i)
    {
        std::cout << *array[i] << " ";
    }
    std::cout << std::endl;

    system("pause");
}