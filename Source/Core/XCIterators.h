
#ifndef XCITERATORS_H
#define XCITERATORS_H

#include "XCBasic.h"

namespace XC
{
    class InputIteratorTag;
    class OutputIteratorTag;
    class FordwardIteratorTag;
    class BidirectionalIteratorTag;
    class RandomAccessIteratorTag;

    template <typename TCategory, typename T, typename TDistance,
	typename TPointer, typename TReference> 
    class Iterator;

    template <typename T> class IteratorTraits;
    template <typename T> class IteratorTraits<T *>;
    template <typename T> class IteratorTraits<const T *>;

    class InputIteratorTag {};
    class OutputIteratorTag {};
    class FordwardIteratorTag : public InputIteratorTag {};
    class BidirectionalIteratorTag : public FordwardIteratorTag	{};
    class RandomAccessIteratorTag : public BidirectionalIteratorTag {};

    template <typename TCategory, typename T, typename TDifference = xpointerdifference,
	typename TPointer = T *, typename TReference = T &>
    class Iterator
    {
    public:
	typedef TCategory IteratorCategory;
	typedef T ValueType;
	typedef TDifference DifferenceType;
	typedef TPointer Pointer;
	typedef TReference Reference;
    };

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
	typedef xpointerdifference DifferenceType;
	typedef T * Pointer;
	typedef T & Reference;
    };

    template <typename T>
    class IteratorTraits<const T *>
    {
    public:
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T ValueType;
	typedef	xpointerdifference DifferenceType;
	typedef const T * Pointer;
	typedef const T & Reference;
    };

    namespace Iterators
    {
	template <typename Iterator>
	typename IteratorTraits<Iterator>::IteratorCategory
	    GetIteratorCategory(const Iterator &);

	template <typename Iterator>
	typename IteratorTraits<Iterator>::ValueType *
	    GetIteratorValuePointerType(const Iterator &);

	template <typename Iterator>
	typename IteratorTraits<Iterator>::DifferenceType *
	    GetIteratorDifferencePointerType(const Iterator &);
    }

    namespace Iterators
    {
	template <typename Iterator>
	inline typename IteratorTraits<Iterator>::IteratorCategory
	    GetIteratorCategory(const Iterator &)
	{
	    typedef typename IteratorTraits<Iterator>::IteratorCategory category;
	    return category();
	}

	template <typename Iterator>
	typename IteratorTraits<Iterator>::ValueType *
	    GetIteratorValuePointerType(const Iterator &)
	{
	    return static_cast<typename IteratorTraits<Iterator>::ValueType *>(nullptr);
	}

	template <typename Iterator>
	typename IteratorTraits<Iterator>::DifferenceType *
	    GetIteratorDifferencePointerType(const Iterator &)
	{
	    return static_cast<typename IteratorTraits<Iterator>::DifferenceType *>(nullptr);
	}
    }
}

#endif // XCITERATORS_H