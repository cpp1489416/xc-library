#ifndef XCALGORITHM_H
#define XCALGORITHM_H

#include "../SyntaxSugars/SyntaxSugars.h"
#include "../Iterators/Iterators.h"

XC_BEGIN_NAMESPACE_2(XC, Algorithms)
{
    template <typename T>
    inline T GetMin(T a, T b)
    {
        return a > b ? b : a;
    }

    template <typename T>
    inline T GetMax(T a, T b)
    {
        return a > b ? a : b;
    }

    template <typename T1, typename T2>
    void Swap(T1 a, T2 b)
    {
        T1 tmp = a;
        a = b;
        b = a;
    }

    template <typename InputIterator, typename T>
    InputIterator Find(InputIterator first, InputIterator last, const T & value)
    {
        InputIterator current = first;
        while (*current != value && current < last)
        {
            ++current;
        }

        return current;
    }

    template <typename I, typename T>
    typename IteratorTraits<I>::DifferenceType GetCount(I first, I last, const T & value)
    {
        typename IteratorTraits<I>::DifferenceType n = 0;
        for (; first < last; ++first)
        {
            if (*first == value)
            {
                ++n;
            }
        }
        return n;
    }

    template <typename InputIterator, typename T>
    InputIterator GetLowerBound(InputIterator first, InputIterator last, const T & value)
    {
        return first;
    }

    // Heap Algorithms
    template <typename RandomAccessIterator>
    void PushHeap(RandomAccessIterator first, RandomAccessIterator last);

    namespace Details // The detail namespace means the functions or class in it must be used inside.
    {
        // Heap Algorithms
        template <typename RandomAccessIterator, typename Distance, typename T>
        void PushHeapAUX(RandomAccessIterator first, RandomAccessIterator last, Distance *, T *);

        template <typename RandomAccessIterator, typename Distance, typename T>
        void PushHeap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value);
    }

    template <typename RandomAccessIterator>
    void PushHeap(RandomAccessIterator first, RandomAccessIterator last)
    {
        Details::PushHeapAUX(first, last,
            Iterators::GetIteratorDifferencePointerType(first), Iterators::GetIteratorValuePointerType(first));
    }

    namespace Details
    {
        template <typename RandomAccessIterator, typename Distance, typename T>
        void PushHeapAUX(RandomAccessIterator first, RandomAccessIterator last, Distance *, T *)
        {
            PushHeap(first, Distance(last - first) - 1, Distance(0), T(*last - 1));
        }

        // The real push heap function.
        template <typename RandomAccessIterator, typename Distance, typename T>
        void PushHeap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value)
        {

        }
    }

} XC_END_NAMESPACE_2


#endif // XCALGORITHM_H
