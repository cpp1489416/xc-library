#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"
#include "../Types/Types.h"
#include "../Iterators/Iterators.h"

XC_BEGIN_NAMESPACE_2(XC, Algorithms)
{
    template <typename T>
    inline T GetMin(const T& a, const T& b)
    {
        return a > b ? b : a;
    }

    template <typename T>
    inline T GetMax(const T& a, const T& b)
    {
        return a > b ? a : b;
    }

    template <typename T1, typename T2>
    void Swap(T1& a, T2& b)
    {
        T1 tmp = a;
        a = b;
        b = tmp;
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
    typename Iterators::IteratorTraits<I>::DifferenceType GetCount(I first, I last, const T & value)
    {
        typename Iterators::IteratorTraits<I>::DifferenceType n = 0;
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

} XC_END_NAMESPACE_2
