#ifndef XCINITIALIZED_H
#define XCINITIALIZED_H

namespace XC
{
    namespace Memories
    {
	template <typename ForwardIterator, typename T>
	void Fill(ForwardIterator first, ForwardIterator last, const T & value)
	{
	    for (; first < last; ++first)
	    {
		*first = value;
	    }
	}


	template <typename InputIterator, typename ForwardIterator>
	ForwardIterator Copy(InputIterator first, InputIterator last, ForwardIterator result)
	{
	    for (; first < last; ++first)
	    {
            *result = *first;
            result++;
	    }
	    return result;
	}

	template <typename BidirectionalIterator1, typename BidirectionalIterator2>
	BidirectionalIterator1 CopyBackward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)
	{
	    while (last != first)
	    {
		*(--result) = *(--last);
	    }
	    return result;
	}
    }
}

#endif // XCINITIALIZED_H
