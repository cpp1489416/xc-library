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
    AA *paa = new AA();
    AA & aa = *paa;
    //a->Get();
    B b;
    b.mEventHandler.Add(a, &A::Get);

    b.mEventHandler.Add(&aa, &AA::Get);

    b.mEventHandler.Invoke();

    delete a;
    b.mEventHandler.Invoke();

    delete paa; 
    b.mEventHandler.Invoke();
}

int main()
{
    system("pause");
    return 0;
}

XC_TEST_CASE(gegwgwe)
{
    std::cout << "main test" << std::endl;
}

XC_TEST_CASE(2)
{
    std::cout << "main test 2" << std::endl;
}

XC_TEST_CASE(2434)
{
    std::cout << "main test 3" << std::endl;
}