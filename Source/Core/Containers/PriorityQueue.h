#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"
#include "../Functors/Functors.h"
#include "../Algorithms/Algorithms.h"
#include "Array.h"

XC_BEGIN_NAMESPACE_2(XC, Containers)
{
    template <typename T, typename TSequeue = Array<T>, typename TCompare = Functors::Less<T> >
    class PriorityQueue
    {
    public:
        using ValueType = typename TSequeue::ValueType;
        using SizeType = typename TSequeue::SizeType;
        using Reference = typename TSequeue::Reference;
        using Self = PriorityQueue<T, TSequeue, TCompare>;

    public:
        PriorityQueue() : mCompare() {}
        
        explicit PriorityQueue(const TCompare & compare) : mSequeue(), mCompare(compare) {}

        template <typename TInputIterator>
        PriorityQueue(TInputIterator first, TInputIterator last) :
            mSequeue(first, last)
        {
            Algorithms::MakeHeap(first, last);
        }

        template <typename TInputIterator>
        PriorityQueue(TInputIterator first, TInputIterator last, TCompare compare) :
            mSqueue(first, last), mCompare(compare)
        {
            Algorithms::MakeHeap(first, last);
        }

        PriorityQueue(const Self &) = default;

        ~PriorityQueue() = default;

        Self & operator = (const Self &) = default;

    public:
        bool IsEmpty() const
        {
            return mSequeue.IsEmpty();
        }

        SizeType GetSize() const
        {
            return mSequeue.GetSize();
        }

        const T & GetTop() const
        {
            return mSequeue.GetFront();
        }

        void Push(const T & value)
        {
            mSequeue.PushBack(value);
            Algorithms::PushHeap(mSequeue.GetBegin(), mSequeue.GetEnd());
        }

        void Pop()
        {
            Algorithms::PopHeap(mSequeue.GetBegin(), mSequeue.GetEnd());
            mSequeue.PopBack();
        }

    protected:
        TSequeue mSequeue;
        TCompare mCompare;
    };

} XC_END_NAMESPACE_2;

XC_TEST_CASE(PRIORITY_QUEUE_TEST)
{
    XC::Containers::PriorityQueue<int> pq;
    int arr[] = { 342,23,2314,65432,5,3151,413,14 };
    for (XC::xsize i = 0; i < sizeof(arr) / sizeof(int); ++i)
    {
        pq.Push(arr[i]);
    }

    std::cout << "PriorityQueue:";
    while (!pq.IsEmpty())
    {
        std::cout << pq.GetTop() << " " ;
        pq.Pop();;
    }
}