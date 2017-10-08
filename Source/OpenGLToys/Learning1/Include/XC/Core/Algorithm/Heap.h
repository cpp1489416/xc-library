#ifndef XCHEAP_H
#define XCHEAP_H

#include "../XCIterators.h"

namespace XC
{
    template <typename RandomAccessIterator>
    void PushHeaåp(RandomAccessIterator first, RandomAccessIterator last); // heap must make sure parent is bigger

    namespace Detail
    {
        template <typename RandomAccessIterator, typename Distance, typename T>
        void PushHeapAUX(RandomAccessIterator first, RandomAccessIterator last, Distance *, T *);

        template <typename RandomAccessIterator, typename Distance, typename T>
        void PushHeap__(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value);
    }
}

namespace XC
{

    template <typename RandomAccessIterator>
    void PushHeap(RandomAccessIterator first, RandomAccessIterator last)
    {
        Detail::PushHeapAUX(first, last, Iterators::GetDifferencePointer(first), Iterators::GetValuePointer(first));
    }

    namespace Detail
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
        }
    }
}

#endif // XCHEAP_H