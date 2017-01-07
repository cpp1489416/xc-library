#ifndef XCDEQUEUE_H
#define XCDEQUEUE_H

#include "../XCBasic.h"
#include "../XCMemory.h"
#include "../XCBaseIterators.h"

namespace XC
{
    template <typename T, xsize TBufferSize = 5, typename TAllocator = DefaultAllocator<T> >
    class Dequeue
    {
    public:
        template <typename TReference, typename TPointer>
        class BaseIterator
        {
        public:
            typedef BaseIterator<TReference, TPointer> Self;
            typedef BaseIterator<const T &, const T *> ConstantIterator;
            typedef BaseIterator<T &, T *> Iterator;

            // BaseIterator traits :
            typedef RandomAccessIteratorTag IteratorCategory;
            typedef T ValueType;
            typedef TPointer Pointer;
            typedef TReference Reference;
            typedef xsize SizeType;
            typedef xpointerdifference DifferenceType;

            // The map pointer :
            typedef T * * MapPointer; 

        public:
            BaseIterator() {}
            BaseIterator(const ConstantIterator & rhs) : mCurrent(rhs.mCurrent), mFirst(rhs.mCurrent), mLast(rhs.mLast), mNode(rhs.mNode) {} // use constant BaseIterator to initialize all BaseIterators
            BaseIterator(const Iterator & rhs) : mCurrent(rhs.mCurrent), mFirst(rhs.mFirst), mLast(rhs.mLast), mNode(rhs.mNode) {} // This must write in case of moti definitions
            ~BaseIterator() {}
            Self & operator = (const Self &) = default;

            // The BaseIterator feunctions :
            Reference operator * () const { return *mCurrent; }
            Pointer operator -> () const { return &(operator * ()); }
            Self & operator ++ ();
            Self & operator -- ();
            Self operator ++ (int);
            Self operator -- (int);
            Self & operator += (xpointerdifference n);
            Self & operator -= (xpointerdifference n) { return *this += -n; }
            Self operator + (xpointerdifference n) const;
            Self operator - (xpointerdifference n) const;
            xpointerdifference operator - (const Self & rhs) const; // Two BaseIterators minus together is a pointer difference.
            Reference operator [] (xpointerdifference n) const { return *(this + n); } // operator * and opeartor +
            bool operator == (const Self & rhs) const { return mCurrent == rhs.mCurrent; }
            bool operator != (const Self & rhs) const { return !(*this == rhs); }
            bool operator < (const Self & rhs) const { return mNode == rhs.mNode ? mCurrent < rhs.mCurrent : mNode < rhs.mNode; }
            bool operator > (const Self & rhs) const { return !(*this < rhs && *this == rhs); }

            T * mCurrent;
            T * mFirst;
            T * mLast;
            T * * mNode; // Points to the location of the whole map;

        protected:
            xsize GetBufferSize(xsize count) const { return count != 0 ? count : xsize(512 / sizeof(T)); }
            void SetNode(T * * newNode);

            friend class Dequeue<T, TBufferSize, TAllocator>;
        };
    
    public:
        // Basic typedefs :
        typedef T ValueType;
        typedef T * Pointer;
        typedef xsize SizeType;

        // The BaseIterators :
        typedef BaseIterator<const T &, const T *> ConstantBaseIterator;
        typedef BaseIterator<T &, T *> BaseIterator;

        // The map pointer :
        typedef T * * MapPointer;

        typedef Dequeue<T, TBufferSize, TAllocator> Self;

    public:
        Dequeue() = default;
        Dequeue(const Self &) = default;
        ~Dequeue() = default;
        Self & operator = (const Self &) = default;

        ConstantIterator GetBegin() const { return ConstantIterator(mStart); }
        ConstantIterator GetEnd() const { return ConstantIterator(mLast); }
        const T & At(xsize index) const { return mStart[index]; }
        const T & operator [] (xsize index) const { return At(index); }
        const T & GetFront() const { return *GetBegin(); }
        const T & GetEnd() const { return *(GetEnd() - 1); }
        xsize GetSize() const { return xsize(mFinish - mStart); }

        BaseIterator GetBegin() { return mStart; }
        BaseIterator GetEnd() { return mLast; }
        T & At(xsize index) { return mStart[index]; }
        T & operator [] (xsize index) { return At(index); }
        T & GetFront() { return *GetBegin(); }
        T & GetEnd() { return *(GetEnd() - 1); }
        void PushBack(const T & value);
        void PopBack(const T & value);
        void PushFront(const T & value);
        void PopFront(const T & value);
        void Clear();
        Iterator Erase(Iterator location);
        Iterator Erase(Iterator first, Iterator last);
        Iterator Insert(Iterator location, const T & value);

        // These functions are for C++ 11 :
        ConstantBaseIterator begin() const { return GetBegin(); }
        ConstantBaseIterator end() const { return GetEnd(); }
        
        BaseIterator begin() { return GetBegin(); }
        BaseIterator end() { return GetEnd(); }

    protected:
        typedef InsideAllocator<T *, TAllocator> MapAllocator; // Allocate the whole map
        typedef InsideAllocator<T, TAllocator> DataAllocator; // Allocate element of each node

    protected:
        xsize GetBufferSize() const { return TBufferSize == 0 ? 512 : TBufferSize; }
        xsize GetInitianalMapSize() const { return xsize(8); }

        void EmptyInitialize();
        void FillInitialize(xsize count, const T & value);
        T * AllocateNode() { return DataAllocator::Allocate(GetBufferSize()); } // Allocate a node.
        T * * AllocateMap() { return MapAllocator::Allocate(mMapSize); }
        void ReserveIfMapAtBack();
        void ReserveIfMapAtFront();
        void OutOfMemorySolve(xsize nodesToAdd, bool isAddBack);
        void ReleaseMemory();

    protected:
        T * * mMapPointer; // Each element of the map contains a pointer of T type.
        xsize mMapSize; // The count of pointers in a map.
        BaseIterator mStart; // The start BaseIterator of the whole dequeue.
        BaseIterator mFinish; // The finish BaseIterator of the whole dequeue.
    };  

    template <typename T, xsize TBufferSize, typename TAllocator>
    template <typename TReference, typename TPointer>
    typename Dequeue<T, TBufferSize, TAllocator>::template BaseIterator<TReference, TPointer>::Self &
        Dequeue<T, TBufferSize, TAllocator>::BaseIterator<TReference, TPointer>::operator ++ ()
    {
        ++mCurrent;
        if (mCurrent == mLast)
        {
            SetNode(mNode + xpointerdifference(1));
            mCurrent = mFirst;
        }

        return *this;
    }

    template <typename T, xsize TBufferSize, typename TAllocator>
    template <typename TReference, typename TPointer>
    inline typename Dequeue<T, TBufferSize, TAllocator>::template BaseIterator<TReference, TPointer>::Self
        Dequeue<T, TBufferSize, TAllocator>::BaseIterator<TReference, TPointer>::operator ++ (int) 
    {
        Self ans = *this;
        ++(*this);
        return ans;
    }

    template <typename T, xsize TBufferSize, typename TAllocator>
    template <typename TReference, typename TPointer>
    inline typename Dequeue<T, TBufferSize, TAllocator>::template BaseIterator<TReference, TPointer>::Self
        Dequeue<T, TBufferSize, TAllocator>::BaseIterator<TReference, TPointer>::operator -- (int)
    {
        Self ans = *this;
        --(*this);
        return ans;
    }

    template <typename T, xsize TBufferSize, typename TAllocator>
    template <typename TReference, typename TPointer>
    typename Dequeue<T, TBufferSize, TAllocator>::template BaseIterator<TReference, TPointer>::Self &
        Deueue<T, TBufferSize, TAllocator>::BaseIterator<TReference, TPointer>::operator += (xpointerdifference n)
    {
        xpointerdifference offset = (mCurrent - mFirst) + n;
        if (offset >= 0 && offset < xpointerdifference(GetBufferSize()))
        {
            mCurrent += n;
        }
        else
        {
            xpointerdifference nodeOffset = offset > 0 ? 
                offset / xpointerdifference(GetBufferSize()) :
                (-offset - 1) / xpointerdifference(GetBufferSize()) - 1;
            SetNode(mNode + nodeOffset);
            mCurrent = mFirst + (offset - nodeOffset * xpointerdifference(GetBufferSize()));
        }

        return *this;
    }

    template <typename T, xsize TBufferSize, typename TAllocator>
    template <typename TReference, typename TPointer>
    inline typename Dequeue<T, TBufferSize, TAllocator>::template BaseIterator<TReference, TPointer>::Self
        Dequeue<T, TBufferSize, TAllocator>::BaseIterator<TReference, TPointer>::operator + (xpointerdifference n) const
    {
        Self ans = *this;
        return ans += n;
    }


    template <typename T, typename TBufferSize, typename TAllocator>
    template <typename TReference, typename TPointer>
    inline typename Dequeue<T, TBufferSize, TPointer>::template BaseIterator<TReference, TPointer>::Self
        Dequeue<T, TBufferSize, TAllocator>::BaseIterator<TReference, TPointer>::operator - (xpointerdifference n) const 
    {
        Self ans = *this;
        return ans += -n;
    }

    template <typename T, typename TBufferSize, typename TAllocator>
    template <TReference, typename TPointer>
    inline typename Dequeue<T, TBufferSize, TPointer>::template BaseIterator<TReference, TPointer>::DifferenceType
        Dequeue<T, TBufferSize, TPointer>::BaseIterator<TReference, TPointer>::operator - (const Self & rhs) const
    {
        return xpointerdifference((mNode - rhs.mNode) * xpointerdifference(GetBufferSize())
            + (mCurrent - rhs.mCurrent) + (rhs.mLast - mLast));        
    }

    template <typename T, xsize TBufferSize, typename TAllocator>
    template <typename TReference, typename TPointer>
    inline void Dequeue<T, TBufferSize, TAllocator>::template BaseIterator<TReference, TPointer>::SetNode(T * * newNode)
    {
        mNode = newNode;
        mFirst = *newNode;
        mLast = mFirst + xpointerdifference(GetBufferSize);
    }

    template <typename T, xsize TBufferSize, typename TAllocator>
    void Dequeue<T, TBufferSize, TAllocator>::PushBack(const T & value)
    {
        if (mFinish.mCurrent != mFinish.mLast - 1) // Should last - 1, make sure there will always be a node at the end.
        {
            Memory::Construct(mFinish.mCurrent, value);
            ++mFinish.mCurrent;
        }
        else // Should jump to next node.
        {
            ReserveIfMapAtBack();
            *(mFinish.mNode + 1) = AllocateNode();
            Memory::Construct(mFinish.mCurrent, value);
            mFinish.SetNode(mFinish.mNode + 1);
            mFinish.mCurrent = mFinish.mFirst;
        }
    }

    template <typename T, xsize TBufferSize, typename TAllocator>
    void Dequeue<T, TBufferSize, TAllocator>::PopBack()
    {
        if (mFinish.mCurrent != mFinish.mFirst)
        {
            --mLast.mCurrent;
            Memory::Destroy(mLast.mCurrent);
        }
        else
        {
            DeallocateNode(mFinish.mFirst);
            mFinish.SetNode(mFinish.mNode - 1);
            mFinish.mCur = mFinish.mLast - 1;
            Memory::Destroy(mFinish.mCurrent);
        }
    }

    // PushFront is different from PushBack
    template <typename T, xsize TBufferSize, typename TAllocator>
    void Dequeue<T, TBufferSize, TAllocator>::PushFront(const T & value)
    {
        if (mStart.mCurrent != mStart.mFirst) // do not need to have more free space.
        {
            Memory::Construct(mStart.mCurrent - 1, value);
            --mStart.mCurrent;
        }
        else
        {
            ReserveIfMapAtFront();
            *(mStart.mNode - 1) = AllocateNode();
            mStart.SetNode(mStart.mNode - 1);
            mStart.mCurrent = mStart.mLast - 1;
            Memory::Construct(mStart.mCurrent, value);
        }
    }

    template <typename T, xsize TBufferSize, typename TAllocator>
    void Dequeue<T, TBufferSize, TAllocator>::PopFront()
    {

    }

    template <typename T, xsize TBufferSize, typename TAllocator>
    void Dequeue<T, TBufferSize, TAllocator>::Clear()
    {

    }    

    template <typename T, xsize TBufferSize, typename TAllocator>
    typename Dequeue<T, TBufferSize, TAllocator>::Iterator 
        Dequeue<T, TBufferSize, TAllocator>::Erase(Iterator location)
    {

    }

    template <typename T, xsize TBufferSize, typename TAllocator>
    typename Dequeue<T, TBufferSize, TAllocator>::Iterator 
        Dequeue<T, TBufferSize, TAllocator>::Erase(Iterator first, Iterator last)
    {

    } 

    template <typename T, xsize TBufferSize, typename TAllocator>
    typename Dequeue<T, TBufferSize, TAllocator>::Iterator
        Dequeue<T, TBufferSize, TAllocator>::Insert(Iterator location, const T & value)
    {
        
    }
}

#endif // XCDEQUEUE_H
