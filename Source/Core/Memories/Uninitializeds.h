#ifndef XCUNINITIALIZEDS_H
#define XCUNINITIALIZEDS_H

#include "../Types/Types.h"
#include "../Iterators/Iterators.h"
#include "Construts.h"

namespace XC
{
    namespace Memories
    {
        template <typename ForwardIterator, typename Size, typename T>
        ForwardIterator UninitializedFillN(ForwardIterator first, Size n,
                                           const T & value);

        template <typename ForwardIterator, typename Size, typename T,
                  typename ValueType>
        ForwardIterator UninitializedFillNPlus(ForwardIterator first,
                                               ForwardIterator last, Size n, const T & value, ValueType *);

        template <typename ForwardIterator, typename Size, typename T>
        ForwardIterator UninitializedFillNPlusAUX(ForwardIterator first, Size n,
                                                  const T & value, FalseTraitType);

        template <typename ForwardIterator, typename Size, typename T>
        ForwardIterator UninitializedFillNPlusAUX(ForwardIterator first, Size n,
                                                  const T & value, TrueTraitType);

        template <typename ForwardIterator, typename T>
        void UninitializedFill(ForwardIterator first, ForwardIterator last, const T & value);

        template <typename ForwardIterator, typename T, typename ValueType>
        void UninitializedFillPlus(ForwardIterator first,
                                   const T & value, ValueType *);

        template <typename ForwardIterator, typename T>
        void UninitializedFillPlusAUX(ForwardIterator first, ForwardIterator last,
                                      const T & value, TrueTraitType);

        template <typename ForwardIterator, typename T>
        void UninitiallizedFillPlusAUX(ForwardIterator first, ForwardIterator last,
                                       const T & value, FalseTraitType);

        template <typename InputIterator, typename ForwardIterator>
        ForwardIterator UninitializedCopy(InputIterator first, InputIterator last,
                                          ForwardIterator result);

        template <typename InputIterator, typename ForwardIterator,
                  typename ValueType>
        ForwardIterator UninitializedCopyPlus(InputIterator first,
                                              InputIterator last, ForwardIterator result, ValueType *);

        template <typename InputIterator, typename ForwardIterator>
        ForwardIterator UninitializedCopyPlusAUX(InputIterator first, InputIterator last,
                                                 ForwardIterator result, FalseTraitType);

        template <typename InputIterator, typename ForwardIterator>
        ForwardIterator UninitializedCopyPlusAUX(InputIterator first, InputIterator last,
                                                 ForwardIterator result, TrueTraitType);
    }

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
            //                              Iterators::GetIteratorValuePointerType(first));
        }

        template<typename ForwardIterator, typename Size, typename T,
                 typename ValueType>
        inline ForwardIterator UninitializedFillNPlus(ForwardIterator first,
                                                      Size n, const T & value, ValueType *)
        {
            typedef typename TypeTraits<ValueType>::IsPlainOldDataType IsPOD;
            return UninitializedFillNPlusAUX(first, n, value, IsPOD());
        }

        template <typename ForwardIterator, typename Size, typename T>
        ForwardIterator UninitializedFillNPlusAUX(ForwardIterator first, Size n,
                                                  const T & value, FalseTraitType)
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
                                                  const T & value, TrueTraitType)
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

            //return UninitializedFillPlus(first, last, value,
            //                             Iterators::GetIteratorValuePointerType(first));
        }

        template <typename ForwardIterator, typename T, typename ValueType>
        inline void UninitializedFillPlus(ForwardIterator first, ForwardIterator last,
                                          const T & value, ValueType *)
        {
            typedef typename TypeTraits<ValueType>::IsPlainOldDataType IsPOD;
            return UninitializedFillPlusAUX(first, last, value, IsPOD());
        }

        template <typename ForwardIterator, typename T>
        void UninitializedFillPlusAUX(ForwardIterator first, ForwardIterator last,
                                      const T & value, TrueTraitType)
        {
            for (; first < last; ++first)
            {
                Construct(&*first, value);
            }
        }

        template <typename ForwardIterator, typename T>
        void UninitiallizedFillPlusAUX(ForwardIterator first, ForwardIterator last,
                                       const T & value, FalseTraitType)
        {
            for (; first < last; ++first)
            {
                Memories::Construct(&*first, value);
            }
        }

        template <typename InputIterator, typename ForwardIterator>
        ForwardIterator UninitializedCopy(InputIterator first, InputIterator last,
                                          ForwardIterator result)
        {
            /*
            ForwardIterator cur;
            for (cur = first; cur != last; ++cur)
            {
                std::cout << "in copy";
                Construct(&*result, *cur);
                ++result;
            }


            return result;
            */
            return UninitializedCopyPlus(first, last, result,
                                         Iterators::GetIteratorValuePointerType(first));
        }

        template <typename InputIterator, typename ForwardIterator, typename ValueType>
        ForwardIterator UninitializedCopyPlus(InputIterator first, InputIterator last,
                                              ForwardIterator result, ValueType *)
        {
            typedef typename TypeTraits<ValueType>::IsPlainOldDataType IsPOD;
            return UninitializedCopyPlusAUX(first, last, result, IsPOD());
        }

        template <typename InputIterator, typename ForwardIterator>
        ForwardIterator UninitializedCopyPlusAUX(InputIterator first, InputIterator last,
                                                 ForwardIterator result, FalseTraitType)
        {
            for (; first < last; ++first, ++result)
            {
                Memories::Construct(&*result, *first);
            }
            return result;
        }

        template <typename InputIterator, typename ForwardIterator>
        ForwardIterator UninitializedCopyPlusAUX(InputIterator first, InputIterator last,
                                                 ForwardIterator result, TrueTraitType)
        {
            for (; first < last; ++first, ++result)
            {
                Construct(&*result, *first);
            }
            return result;
        }
    }
}

#endif // XCUNINITIALIZEDS
