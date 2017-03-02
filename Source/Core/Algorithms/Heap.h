#ifndef XCHEAP_H
#define XCHEAP_H

#include "../SyntaxSugars/SyntaxSugars.h"
#include "../Iterators.h"

XC_BEGIN_NAMESPACE_2(XC, Algorithms)
{
    template <typename RandomAccessIterator>
    void PushHeap(RandomAccessIterator first, RandomAccessIterator last)
    {
        Detail::PushHeapAUX(first, last, Iterators::GetDifferencePointer(first), Iterators::GetValuePointer(first));
    }

    XC_BEGIN_NAMESPACE_1(Details)
    {
        template <typename RandomAccessIterator, typename Distance, typename T>
        void PushHeapAUX(RandomAccessIterator first, RandomAccessIterator last)
        {
            PushHeap__(first, Distance(last - first - 1), Distance(0), T(*(last - 1)));
        }

        template <typename RandomAccessIterator, typename Distance, typename T>
        void PushHeap__(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value)
        {
            // heap's parent is bigger than children, this function is in the condtion of the heap is made
            Distance parent = (holeIndex - 1) / 2;
            while (holeIndex > topIndex && *(first + parent) < value)
            {
                *(first + holeIndex) = *(first + parent);
                holeIndex = parent;
                parent = (holeIndex - 1) / 2;
            }

            *(first + holeIndex) = value;
        } XC_END_NAMESPACE_1
    }
} XC_END_NAMESPACE_2

#endif // XCHEAP_H