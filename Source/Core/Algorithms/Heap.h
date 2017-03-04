#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"
#include "../Iterators/Iterators.h"

XC_BEGIN_NAMESPACE_2(XC, Algorithms)
{
    XC_BEGIN_NAMESPACE_1(Details)
    {
        template <typename TRandomAccessIterator, typename TDistance, typename T>
        void PushHeapAUX(TRandomAccessIterator first, TRandomAccessIterator last, TDistance *, T *)
        {
            // attention : new object is inserted to the end of the heap
            PushHeaMain(first, TDistance(last - first - 1), Iterators::GetDifferencePointerType(first), T(*(last - 1)));
        }

        template <typename TRandomAccessIterator, typename TDistance, typename T>
        void PushHeapMain(TRandomAccessIterator first, TDistance holeIndex, TDistance topIndex, T value)
        {
            // heap's parent is bigger than children, this function is in the condtion of the heap is made
            TDistance parent = (holeIndex - 1) / 2;
            while (holeIndex > topIndex && *(first + parent) < value)
            {
                *(first + holeIndex) = *(first + parent);
                holeIndex = parent;
                parent = (holeIndex - 1) / 2;
            }

            *(first + holeIndex) = value;
        }

        template <typename TRandomAccessIterator, typename T>
        void PopHeapAUX(TRandomAccessIterator first, TRandomAccessIterator last, T *)
        {
            PopHeapMain(first, last - 1, last - 1, T(*(last - 1)), Iterators::GetDifferencePointerType(first));
        }

        template <typename TRandomAccessIterator, typename T, typename TDistance>
        void PopHeapMain(
            TRandomAccessIterator first,
            TRandomAccessIterator last,
            TRandomAccessIterator result,
            T value,
            TDistance *)
        {
            *result = *first; // Poped value is last, later can use PopHeap function to get poped value.
            AdjustHeap(first, TDistance(0), last - first, value);
        }

        // Range from first to first + length, insert value to the heap.
        template <typename TRandomAccessIterator, typename TDistance, typename T>
        void AdjustHeap(TRandomAccessIterator first, TDistance holeIndex, TDistance length, T value)
        {
            TDistance topIndex = holeIndex;
            TDistance childIndex = 2 * holeIndex + 2;
            while (childIndex < length)
            {
                if (*(first + childIndex) < *(first + childIndex - 1))
                {
                    --childIndex; // child is the bigger child
                }

                *(first + holeIndex) = *(first + childIndex);
                holeIndex = childIndex;
                childIndex = 2 * childIndex + 2; // right child
            }

            if (childIndex == length) // childIndex cannot bigger than length
            {
                --childIndex;
                *(first + holeIndex) = *(first + childIndex);
                holeIndex = childIndex;
            }

            PushHeapMain(first, holeIndex, topIndex, value);
        }

        template <typename TRandomAccessIterator, typename T, typename TDistance>
        void MakeHeapMain(TRandomAccessIterator first, TRandomAccessIterator last, T *, TDistance *)
        {
            if (last - first < 2)
            {
                return;
            }

            TDistance length = last - first;
            TDistance holeIndex = (length - 2) / 2;
            while (true)
            {
                AdjustHeap(first, holeIndex, length, T(*(first + holeIndex)));
                if (holeIndex == 0)
                {
                    return;
                }

                --holeIndex;
            }
        }

    } XC_END_NAMESPACE_1;

    template <typename TRandomAccessIterator>
    void PushHeap(TRandomAccessIterator first, TRandomAccessIterator last)
    {
        Details::PushHeapAUX(first, last, Iterators::GetDifferencePointerType(first), Iterators::GetValuePointer(first));
    }

    template <typename TRandomAccessIterator>
    void PopHeap(TRandomAccessIterator first, TRandomAccessIterator last)
    {
        Details::PopHeapAUX(first, last, Iterators::GetValuePointerType(first));
    }

    template <typename TRandomAccessIterator>
    void SortHeap(TRandomAccessIterator first, TRandomAccessIterator last)
    {
        while (last - first > 1)
        {
            PopHeap(first, last--);
        }
    }

    template <typename TRandomAccessIterator>
    void MakeHeap(TRandomAccessIterator first, TRandomAccessIterator last)
    {
        Details::MakeHeapMain(first, last, Iterators::GetValuePointerType(first), Iterators::GetDifferencePointerType(first));
    }

} XC_END_NAMESPACE_2;

#include <iostream>

XC_TEST_CASE(HEAP_TEST)
{
    int arr[10] = { 1, 3432,3241,64,314,2,3,3,3,15 };
    XC::Algorithms::MakeHeap(arr, arr + 10);
    XC::Algorithms::SortHeap(arr, arr + 10);
    for (auto i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}