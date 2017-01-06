#ifndef XCDEQUEUE_h
#define XCDEQUEUE_H

#include "../XCBasic.h"
#include "../XCMemory.h"
#include "../XCIterators.h"

namespace XC
{
    template <typename T, xsize TBufferSize = 0, typename TAllocator = DefaultAllocator<T> >
    class Dequeue
    {
    public:
        template <typename TReference, typename TPointer>
        class Iterator
        {
        public:
            typedef Iterator<TReference, TPointer> Self;
            typedef Iterator<const T &, const T *> ConstantIterator;
            typedef Iterator<T &, T *> Iterator;

            // Iterator traits :
            typedef RandomAccessIteratorTag IteratorCategory;
            typedef T ValueType;
            typedef TPointer Pointer;
            typedef TReference Reference;
            typedef xsize SizeType;
            typedef xpointerdifference DifferenceType;

            typedef T * * MapPointer; 

            T * mCurrent;
            T * mFirst;
            T * mLast;
            T * * mNode;
        };
    
    public:
        typedef T ValueType;
        typedef T * Pointer;

        typedef T * * MapPointer;

    protected:
        T * * mMapPointer;
        xsize mMapSize;
    };  
}

#endif // XCDEQUEUE_H
