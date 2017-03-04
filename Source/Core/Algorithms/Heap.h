#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"
#include "../Iterators/Iterators.h"

XC_BEGIN_NAMESPACE_2(XC, Algorithms)
{
    XC_BEGIN_NAMESPACE_1(Details)
    {
        template <typename RandomAccessIterator, typename Distance, typename T>
        void PushHeapAUX(RandomAccessIterator first, RandomAccessIterator last)
        {
            // attention : new object is inserted to the end of the heap
            PushHeap(first, Distance(last - first - 1), Iterators::GetDifferencePointerType(first), Iterators::getiterator);
        }

        template <typename RandomAccessIterator, typename Distance, typename T>
        void PushHeap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value)
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
        }

    } XC_END_NAMESPACE_1

    template <typename RandomAccessIterator>
    void PushHeap(RandomAccessIterator first, RandomAccessIterator last)
    {
        Details::PushHeapAUX(first, last, Iterators::GetDifferencePointerType(first), Iterators::GetValuePointer(first));
    }

} XC_END_NAMESPACE_2
