// UnitTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Pointers.h>
#include <Delegate.h>
#include <Property.h>
#include <functional>
#include <iostream>

using namespace std;
using namespace XC;

class A
{
public:
    void Get(Object *sender, EventArguments *arguments) const
    {
        std::cout << "A" << std::endl;
    }
};


class B
{
public:
    void Get(Object *sender, EventArguments *arguments)
    {
        std::cout << "B" << std::endl;
    }
};

void Get(Object *sender, EventArguments *arguments)
{
    std::cout << "Static" << std::endl;
}

class Test
{
public:
    Test()
    {
        Value.Create(this, &Test::GetValue, &Test::SetValue);
    }

public:
    Property<int> Value;

private:
    const int & GetValue() const
    {
        return mValue;
        std::cout << "Get Value" << std::endl;
    }

    void SetValue(const int & value)
    {
        mValue = value;
        std::cout << "Set Value" << std::endl;
    }

    int mValue;
};

int main()
{
    A a;
    B b;
    XC::EventHandler handler;
    handler.Add(&a, &A::Get);
    handler.Add(&b, &B::Get);
    handler.Add(&Get);
    handler.Invoke(nullptr, nullptr);

    Test test;
    test.Value = 5;
    int ad = test.Value;
    std::cout << ad << test.Value;
    system("Pause");
    return 0;
}

