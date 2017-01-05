#pragma once

#ifndef XCALGORITHM_H
#define XCALGORITHM_H

#include "XCIterators.h"

namespace XC
{
    namespace Algorithm
    {
	template <typename T>
	inline T GetMin(T a, T b)
	{
	    return a > b ? b : a;
	}

	template <typename T>
	inline T GetMax(T a, T b)
	{
	    return a > b ? a : b;
	}

	template <typename InputIterator, typename T>
	InputIterator Find(InputIterator first, InputIterator last, const T & value)
	{
	    while (*first != value && first < last)
	    {
		++first;
	    }

	    return first;
	}

	template <typename I, typename T>
	typename IteratorTraits<I>::DifferenceType GetCount(I first, I last, const T & value)
	{
	    typename IteratorTrists<I>::DifferenceType n = 0;
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
    }
}

#endif // XCALGORITHM_H