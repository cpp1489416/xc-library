
#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include "Containers\XCArray.h"
#include "XCAlgorithm.h"
#include "XCContainers.h"
#include "Tuples\XCTuple.h"

using namespace XC;

//void foo(int * v)
//{
//
//}
//
//int main()
//{
//    Array<int> ar;
//    int a = 5;
//    const int * p = &a;
//    system("pause");
//}

namespace
{
    template <typename T>
    void Print(const T & arr)
    {
	for (auto i : arr)
	{
	    std::cout << i << " ";
	}
	std::cout << std::endl;
    }

    void TestTuple()
    {
        Tuple<int, double, int *> tuple(0, 0.5f, nullptr);
        // Tuple<float> t = Tuples::MakeTuple(5.5f);
        std::cout << "At : " << Tuples::Get<1>(tuple) << std::endl;
        std::cout << "size : " << tuple.mSize << std::endl;
    }
}

int main()
{
    TestTuple();

    List<int> list;
    for (int i = 0; i < 100; i++)
    {
	list.PushBack(i);
    }

    List<int>::Iterator itr = list.GetBegin();

    int times = 10;
    while (times--)
    {
	list.PopBack();
    }

    times = 10;
    while (times--)
    {
	list.PopFront();
    }
    //list.Clear();
    
    std::cout << list.GetSize() << std::endl;
    Print(list);
    system("pause");
    return 0;
}