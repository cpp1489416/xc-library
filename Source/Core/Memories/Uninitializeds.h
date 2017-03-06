#pragma once

#include "../Iterators/Iterators.h"
#include "Construts.h"

namespace XC
{
    namespace Memories
    {
        template<typename ForwardIterator, typename Size, typename T>
        inline ForwardIterator UninitializedFillN(ForwardIterator first, Size n,
                                                  const T & value)
        {
            ForwardIterator cur = first;
            while (n--)
            {
                // std::cout << "haha";
                *cur = value;
                ++cur;
            }

            return first;
            // return UninitializedFillNPlus(first, n, value,
            //                              Iterators::GetValueType(first));
        }

        template<typename ForwardIterator, typename Size, typename T,
                 typename ValueType>
        inline ForwardIterator UninitializedFillNPlus(ForwardIterator first,
                                                      Size n, const T & value, ValueType *)
        {
            typedef typename Types::TypeTraits<ValueType>::IsPlainOldDataType IsPOD;
            return UninitializedFillNPlusAUX(first, n, value, IsPOD());
        }

        template <typename ForwardIterator, typename Size, typename T>
        ForwardIterator UninitializedFillNPlusAUX(ForwardIterator first, Size n,
                                                  const T & value, Types::FalseTraitType)
        {
            while (n--)
            {
                Construct(&*first, value);
                ++first;
            }
            return first;
        }

        template <typename ForwardIterator, typename Size, typename T>
        ForwardIterator UninitializedFillNPlusAUX(ForwardIterator first, Size n,
                                                  const T & value, Types::TrueTraitType)
        {
            while (n--)
            {
                Construct(&*first, value);
                ++first;
            }
            return first;
        }

        template <typename ForwardIterator, typename T>
        inline void UninitializedFill(ForwardIterator first, ForwardIterator last, const T & value)
        {
            ForwardIterator cur = first;
            for (; cur < last; ++cur)
            {
                Construct(&*cur, value);
            }
        }

        template <typename ForwardIterator, typename T, typename ValueType>
        inline void UninitializedFillPlus(ForwardIterator first, ForwardIterator last,
                                          const T & value, ValueType *)
        {
            typedef typename Types::TypeTraits<ValueType>::IsPlainOldDataType IsPOD;
            return UninitializedFillPlusAUX(first, last, value, IsPOD());
        }

        template <typename ForwardIterator, typename T>
        void UninitializedFillPlusAUX(ForwardIterator first, ForwardIterator last,
                                      const T & value, Types::TrueTraitType)
        {
            for (; first < last; ++first)
            {
                Construct(&*first, value);
            }
        }

        template <typename ForwardIterator, typename T>
        void UninitiallizedFillPlusAUX(ForwardIterator first, ForwardIterator last,
                                       const T & value, Types::FalseTraitType)
        {
            for (; first < last; ++first)
            {
                Memories::Construct(&*first, value);
            }
        }
        
        template <typename InputIterator, typename ForwardIterator>
        ForwardIterator UninitializedCopyPlusAUX(InputIterator first, InputIterator last,
                                                 ForwardIterator result, Types::FalseTraitType)
        {
            for (; first < last; ++first, ++result)
            {
                Memories::Construct(&*result, *first);
            }
            return result;
        }
        
        
        template <typename InputIterator, typename ForwardIterator>
        ForwardIterator UninitializedCopyPlusAUX(InputIterator first, InputIterator last,
                                                 ForwardIterator result, Types::TrueTraitType)
        {
            for (; first < last; ++first, ++result)
            {
                Construct(&*result, *first);
            }
            return result;
        }
        
        template <typename InputIterator, typename ForwardIterator, typename ValueType>
        ForwardIterator UninitializedCopyPlus(InputIterator first, InputIterator last,
                                              ForwardIterator result, ValueType *)
        {
            typedef typename Types::TypeTraits<ValueType>::IsPlainOldDataType IsPOD;
            return UninitializedCopyPlusAUX(first, last, result, IsPOD());
        }
        
        template <typename InputIterator, typename ForwardIterator>
        ForwardIterator UninitializedCopy(InputIterator first, InputIterator last,
                                          ForwardIterator result)
        {
            return UninitializedCopyPlus(first, last, result, Iterators::GetValuePointerType(first));
        }
            }
}
