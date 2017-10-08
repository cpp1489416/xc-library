#pragma once

#include <new>
#include "../Types/Types.h"
#include "../Iterators/Iterators.h"

XC_BEGIN_NAMESPACE_2(XC, Memories)
{
    template <typename T1, typename T2>
    inline T1 * Construct(T1 * p, const T2 & value)
    {
        return new (p) T1(value);
    }

    template <typename T>
    inline void Destroy(T * p)
    {
        p->~T();
    }

    template <typename ForwardIterator>
    inline void Destroy(ForwardIterator first, ForwardIterator last)
    {
        ForwardIterator cur = first;
        for (; cur < last; ++cur)
        {
            Destroy(&*cur);
        }
    }

    /*
    template <typename ForwardIterator, typename ValueType>
    inline void DestroyPlus(ForwardIterator first, ForwardIterator last, ValueType *)
    {
        using IsPOD = typename TypeTraits<ValueType>::IsPlainOldDataType;
        DestroyPlusAUX(first, last, IsPOD());
    }

    template <typename ForwardIterator>
    inline void DestroyPlusAUX(ForwardIterator first, ForwardIterator last, TrueTraitType)
    {
    }

    template <typename ForwardIterator>
    void DestroyPlusAUX(ForwardIterator first, ForwardIterator last, FalseTraitType)
    {
        for (; first < last; ++first)
        {
            Destroy(&*first);
        }
    }
    */
} XC_END_NAMESPACE_2

