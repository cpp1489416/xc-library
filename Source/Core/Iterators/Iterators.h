#pragma once

#include "../Types/Types.h"

XC_BEGIN_NAMESPACE_2(XC, Iterators)
{
    template <typename TCategory, typename T, typename TDifference = xptrdiff, typename TPointer = T *, typename TReference = T &>
    class Iterator
    {
    public:
        typedef TCategory IteratorCategory;
        typedef T ValueType;
        typedef TDifference DifferenceType;
        typedef TPointer Pointer;
        typedef TReference Reference;
    };

    template <typename T> class IteratorTraits;
    template <typename T> class IteratorTraits<T *>;
    template <typename T> class IteratorTraits<const T *>;

    class InputIteratorTag {};
    class OutputIteratorTag {};
    class ForwardIteratorTag : public InputIteratorTag {};
    class BidirectionalIteratorTag : public ForwardIteratorTag {};
    class RandomAccessIteratorTag : public BidirectionalIteratorTag {};

    template <typename TIterator>
    class IteratorTraits
    {
    public:
        typedef typename TIterator::IteratorCategory IteratorCategory;
        typedef typename TIterator::ValueType ValueType;
        typedef typename TIterator::DifferenceType DifferenceType;
        typedef typename TIterator::Pointer Pointer;
        typedef typename TIterator::Reference Reference;
    };

    template <typename T>
    class IteratorTraits<T *>
    {
    public:
        typedef RandomAccessIteratorTag IteratorCategory;
        typedef T ValueType;
        typedef xptrdiff DifferenceType;
        typedef T * Pointer;
        typedef T & Reference;
    };

    template <typename T>
    class IteratorTraits<const T *>
    {
    public:
        typedef RandomAccessIteratorTag IteratorCategory;
        typedef T ValueType;
        typedef	xptrdiff DifferenceType;
        typedef const T * Pointer;
        typedef const T & Reference;
    };

    template <typename Iterator>
    inline typename IteratorTraits<Iterator>::IteratorCategory GetCategory(const Iterator &)
    {
        using Category = typename IteratorTraits<Iterator>::IteratorCategory;
        return Category();
    }

    template <typename Iterator>
    inline typename IteratorTraits<Iterator>::ValueType * GetValuePointerType(const Iterator &)
    {
        return static_cast<typename IteratorTraits<Iterator>::ValueType *>(nullptr);
    }

    template <typename Iterator>
    inline typename IteratorTraits<Iterator>::DifferenceType * GetDifferencePointerType(const Iterator &)
    {
        return static_cast<typename IteratorTraits<Iterator>::DifferenceType *>(nullptr);
    }

    XC_BEGIN_NAMESPACE_1(Details)
    {
        template <typename TInputIterator, typename TDistance>
        void Advance(TInputIterator & iterator, TDistance n, InputIteratorTag)
        {
            while (n--)
            {
                ++iterator;
            }
        }

        template <typename TForwardIterator, typename TDistance>
        void Advance(TForwardIterator & iterator, TDistance n, ForwardIteratorTag)
        {
            Advance(iterator, n, InputIteratorTag());
        }

        template <typename TBidirectionalIterator, typename TDistance>
        void Advance(TBidirectionalIterator & iterator, TDistance n, BidirectionalIteratorTag)
        {
            if (n > 0)
            {
                while (n--)
                {
                    ++iterator;
                }
            }
            else
            {
                while (n++)
                {
                    --iterator;
                }
            }
        }

        template <typename TRandomAccessIterator, typename TDistance>
        void Advance(TRandomAccessIterator & iterator, TDistance n, RandomAccessIteratorTag)
        {
            iterator += n;
        }

        template <typename TInputIterator>
        typename IteratorTraits<TInputIterator>::DifferenceType GetDistance(TInputIterator first, TInputIterator last, InputIteratorTag)
        {
            IteratorTraits<TInputIterator>::DifferenceType ans = 0;
            while (first != last)
            {
                ++first;
                ++ans;
            }

            return ans;
        }

        template <typename TRandomAccessIterator>
        typename IteratorTraits<TRandomAccessIterator>::DifferenceType GetDistance(TRandomAccessIterator first, TRandomAccessIterator last, RandomAccessIteratorTag)
        {
            return last - first;
        }

    } XC_END_NAMESPACE_1;

    template <typename TInputIterator, typename TDistance>
    void Advance(TInputIterator & iterator, TDistance n)
    {
        Details::Advance(iterator, n, IteratorTraits<TIterator>::IteratorCategory);
    }

    template <typename TInputIterator>
    typename IteratorTraits<TInputIterator>::DifferenceType GetDistance(TInputIterator first, TInputIterator last)
    {
        using Category = IteratorTraits<TInputIterator>::IteratorCategory;
        return Details::GetDistance(first, last, Category());
    }

} XC_END_NAMESPACE_2
