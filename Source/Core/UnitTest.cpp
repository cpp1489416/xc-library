
#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include "Containers/XCArray.h"
#include "XCAlgorithm.h"
#include "XCContainers.h"
#include "Tuples/XCTuple.h"
#include "Containers/XCDequeue.h"

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
        Tuple<int, double, int, char> tuple(0, 0.5f, 5, 'a');
        // Tuple<float> t = Tuples::MakeTuple(5.5f);
        //.//std::cout << "At : " << Tuples::Get<1>(tuple) << std::endl;
        //std::cout << "size : " << tuple.mSize << std::endl;
        auto bTuple = Tuples::MakeTuple(3, 3, 3.3);
        std::cout << Tuples::Get<0>(bTuple) << std::endl;
        std::cout << Tuples::Get<2>(bTuple);

        Tuple<int, float, int, double> other = tuple;
        other = tuple;
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

    void TestDEQueue()
    {

    }
}

int main()
{
    std::cout << "Test tuple : \n";
    TestTuple();
    std::cout << std::endl;

    std::cout << "Test list : \n";
    TestList();
    std::cout << std::endl;

    system("pause");
    return 0;
}
