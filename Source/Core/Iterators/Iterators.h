#pragma once

#include "../Types/Types.h"

XC_BEGIN_NAMESPACE_2(XC, Iterators)
{
    // 
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
    class FordwardIteratorTag : public InputIteratorTag {};
    class BidirectionalIteratorTag : public FordwardIteratorTag {};
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

} XC_END_NAMESPACE_2