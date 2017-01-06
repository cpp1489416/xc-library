
#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include "Containers/XCArray.h"
#include "XCAlgorithm.h"
#include "XCContainers.h"
#include "Tuples/XCTuple.h"

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

    void TestList()
    {
        List<int> list;
        for (int i = 0; i < 50; i++)
        {
            list.PushBack(i);
        }

        Print(list);

        List<int> copied = list;
        Print(list);

        List<int> also;

        also = list;
        Print(also);

        List<int> aa;
        aa.PushBack(4);
        aa.PopFront();
        aa.PushFront(5);
        aa.PopBack();
    }
}

int main()
{
    TestList();

    system("pause");
    return 0;
}
