#ifndef XCCONSTRUCTS_H
#define XCCONSTRUCTS_H

#include <new>
#include "../XCBasic.h"
#include "../XCTypeTraits.h"
#include "../XCIterators.h"

namespace XC
{
    namespace Memory
    {
        template <typename T1, typename T2>
        T1 * Construct(T1 * p, const T2 & value);

        template <typename T>
        void Destroy(T * p);

        template <typename ForwardIterator>
        void Destroy(ForwardIterator first, ForwardIterator last);

        template <typename ForwardIterator, typename ValueType>
        void DestroyPlus(ForwardIterator firsrt, ForwardIterator last, ValueType *);

        template <typename ForwardIterator>
        void DestroyPlusAUX(ForwardIterator first, ForwardIterator last, TrueTraitType);

        template <typename ForwardIterator>
        void DestroyPlusAUX(ForwardIterator first, ForwardIterator last, FalseTraitType);
    }

    namespace Memory
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
            // return DestroyPlus(first, last, Iterators::GetIteratorValuePointerType(first));
        }

        template <typename ForwardIterator, typename ValueType>
        inline void DestroyPlus(ForwardIterator first, ForwardIterator last, ValueType *)
        {
            typedef typename TypeTraits<ValueType>::IsPlainOldDataType IsPOD;
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
    }
}

#endif // XCCONSTRUCTFUNCTIONS_H
