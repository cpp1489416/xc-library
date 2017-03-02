// UnitTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Pointers/Pointers.h>
#include <Delegates/Delegates.h>
#include <SyntaxSugars/SyntaxSugars.h>
#include <functional>
#include <iostream>
#include <Containers/Containers.h>

using namespace std;
using namespace XC;

class A
{
public:
    void Get(CallableObject *sender, void *arguments) const
    {
        std::cout << "A" << std::endl;
    }
};


class B
{
public:
    void Get(CallableObject *sender, void *arguments)
    {
        std::cout << "B" << std::endl;
    }
};

void Get(CallableObject *sender, void *arguments)
{
    std::cout << "Static" << std::endl;
}

class Test
{
public:
    Test()
    {
    }

public:
//    Property<int> Value = Property<int>(this, &Test::GetValue, &Test::SetValue);
//    BasicProperty<double> BasicValue;

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
    XC::Array<int> arrays(10);

    A a;
    B b;
    system("Pause");
    return 0;
}

