#ifndef XCARRAY_H
#define XCARRAY_H

#include <iostream>

#include "../XCBasic.h"
#include "../XCMemory.h"
#include "../XCIterators.h"
#include "../XCAlgorithm.h"

namespace XC
{
    template <typename T, typename TAllocator = DefaultAllocator<T> >
    class Array
    {
    public:
	typedef T ValueType;
	typedef xpointerdifference DifferenceType;
	typedef T * Pointer;
	typedef T & Reference;
	typedef xsize SizeType;

	typedef const T * ConstantIterator;
	typedef T * Iterator;

	Array();
	Array(xsize count, const T & value) { FillInitialize(count, value); }
	explicit Array(xsize count) { FillInitialize(count, T()); }
	Array(const Array<T, TAllocator> & rhs) { Copy(rhs); }
	~Array();
	Array<T, TAllocator> & operator = (const Array<T, TAllocator> & rhs);
	bool operator == (const Array<T, TAllocator> & rhs) const;
	bool operator != (const Array<T, TAllocator> & rhs) const { return !(*this == rhs); }
	Array<T, TAllocator> & operator << (const T & value);

	ConstantIterator GetBegin() const { return mStart; }
	Iterator GetBegin() { return mStart; }
	ConstantIterator GetEnd() const { return mFinish; }
	Iterator GetEnd() { return mFinish; }
	xsize GetSize() const { return xsize(mFinish - mStart); }
	xsize GetCapacity() const { return xsize(mEndOfStorage - mStart); }
	void SetCapacity(xsize capacity);
	bool IsEmpty() const { return GetBegin() == GetEnd(); }
	const T & At(xsize index) const { return *(mStart + index); }
	T & At(xsize index) { return *(mStart + index); }
	const T & operator [] (xsize index) const { return At(index); }
	T & operator [] (xsize index) { return At(index); }
	const T & GetFront() const { return *GetBegin(); }
	T & GetFront() { return *GetBegin(); }
	const T & GetBack() const { return *(GetEnd() - 1); }
	T & GetBack() { return *(GetEnd() - 1); }
	void PushBack(const T & value);
	void PopBack();
	void Resize(xsize newSize, const T & value);
	void Resize(xsize newSize) { Resize(newSize, T()); }
	Iterator Erase(Iterator position);
	// Iterator Erase(xsize position) { return Erase(GetIteratorAt(position)); }
	Iterator Erase(Iterator first, Iterator last);
	// Iterator Erase(xsize first, xsize last) { return Erase(GetIteratorAt(first), GetIteratorAt(last)); }
	void Clear() { Erase(GetBegin(), GetEnd()); }
	ConstantIterator GetIteratorAt(xsize index) const { return GetBegin() + index; }
	Iterator GetIteratorAt(xsize index) { return GetBegin() + index; }
	void Insert(Iterator position, const T & value) { Insert(position, 1, value); }
	// void Insert(xsize position, const T & value) { Insert(GetIteratorAt(position), value); }
	Iterator Insert(Iterator position, xsize count, const T & value);
	// Iterator Insert(xsize position, xsize count, const T & value) { return Insert(GetIteratorAt(position), count, value); }
	void PushFront(const T & value) { Insert(GetBegin(), value); }
	void PopFront() { Erase(GetBegin()); }

	// these functions are provided for c++ for statement
	ConstantIterator begin() const { return GetBegin(); }
	Iterator begin() { return GetBegin(); }
	ConstantIterator end() const { return GetEnd(); }
	Iterator end() { return GetEnd(); }
    
    protected:
	typedef InsideAllocator<T, TAllocator> Allocator;

	void Deallocate();
	Iterator AllocateAndFill(xsize count, const T & value);
	void FillInitialize(xsize count, const T & value);
	void Copy(const Array<T, TAllocator> & rhs);

	Iterator mStart;
	Iterator mFinish;
	Iterator mEndOfStorage;
    };

    template <typename T, typename TAllocator>
    inline Array<T, TAllocator>::Array() : 
	mStart(nullptr), mFinish(nullptr), mEndOfStorage(nullptr)
    {
    }

    template <typename T, typename TAllocator>
    inline Array<T, TAllocator>::~Array()
    {
	Memory::Destroy(mStart, mFinish); // destroy the functions
	Deallocate(); // member function
    }

    template <typename T, typename TAllocator>
    Array<T, TAllocator> & Array<T, TAllocator>::operator = (const Array<T, TAllocator>& rhs)
    {
	if (mStart != nullptr)
	{
	    Memory::Destroy(mStart, mFinish);
	    Allocator::Deallocate(mStart, mEndOfStorage - mStart);
	}

	Copy(rhs);
	return *this;
    }

    template <typename T, typename TAllocator>
    bool Array<T, TAllocator>::operator == (const Array<T, TAllocator> & rhs) const
    {
	if (GetSize() != rhs.GetSize())
	{
	    return false;
	}

	ConstantIterator ia = GetBegin();
	ConstantIterator ib = rhs.GetBegin();
	for (; ia != GetEnd(); ++ia, ++ib)
	{
	    if (*ia != *ib)
	    {
		return false;
	    }
	}

	return true;
    }

    template <typename T, typename TAllocator>
    inline Array<T, TAllocator> & Array<T, TAllocator>::operator << (const T & value)
    {
	PushBack(value);
	return *this;
    }

    template <typename T, typename TAllocator>
    inline void Array<T, TAllocator>::SetCapacity(xsize capacity)
    {
	if (capacity <= GetCapacity())
	{
	    return;
	}

	Iterator newStart = Allocator::Allocate(capacity);
	Iterator newFinish = Memory::UninitializedCopy(mStart, mFinish, newStart);

	// destroy and deallocate
	if (mStart != nullptr)
	{
	    Memory::Destroy(mStart, mFinish);
	    Deallocate();
	}

	// update
	mStart = newStart;
	mFinish = newFinish;
	mEndOfStorage = newStart + capacity;
    }

    template <typename T, typename TAllocator>
    inline void Array<T, TAllocator>::PushBack(const T & value)
    {
	if (mFinish != mEndOfStorage)
	{
	    Memory::Construct(mFinish, value);
	    ++mFinish;
	}
	else
	{
	    const xsize oldSize = GetSize();
	    const xsize newCap = oldSize == 0 ? 1 : 2 * oldSize;
	    Iterator newStart = Allocator::Allocate(newCap);
	    Iterator newFinish = Memory::UninitializedCopy(mStart, mFinish, newStart);
	    Memory::Construct(newFinish, value);
	    ++newFinish;

	    Memory::Destroy(GetBegin(), GetEnd());
	    mStart = newStart;
	    mFinish = newFinish;
	    mEndOfStorage = newStart + newCap;
	}
    }

    template<typename T, typename TAllocator>
    inline void Array<T, TAllocator>::PopBack()
    {
	Memory::Destroy(--mFinish);
    }

    template <typename T, typename TAllocator>
    inline typename Array<T, TAllocator>::Iterator
	Array<T, TAllocator>::Erase(Iterator position)
    {
	if (position + 1 != mFinish)
	{
	    Iterator i = Memory::Copy(position + 1, mFinish, position);
	}
    
	Memory::Destroy(--mFinish);
	return position;
    }

    template <typename T, typename TAllocator>
    inline typename Array<T, TAllocator>::Iterator 
	Array<T, TAllocator>::Erase(Iterator first, Iterator last)
    {
	Iterator i = Memory::Copy(last, mFinish, first);
	Memory::Destroy(i, mFinish);
	mFinish -= last - first;
	return first;
    }

    template<typename T, typename TAllocator>
    inline void Array<T, TAllocator>::Resize(xsize newSize, const T & value)
    {
	Memory::Destroy(mStart, mFinish);
	Deallocate();
	FillInitialize(newSize, value);
    }

    template<typename T, typename TAllocator>
    inline typename Array<T, TAllocator>::Iterator
	Array<T, TAllocator>::Insert(Iterator position, xsize count, const T & value)
    {
	if (count <= 0)
	{
	    return position;
	}

	if (xsize(mEndOfStorage - mFinish) >= count) // have enough free space
	{
	    const xsize elemAfter = mFinish - position; 
	    Iterator oldFinish = mFinish;
	    if (elemAfter > count)
	    {
		Memory::UninitializedCopy(mFinish - count, mFinish, mFinish);
		Memory::CopyBackward(position, mFinish - count, mFinish);
		Memory::Fill(position, position + count, value);
		mFinish += count;
	    }
	    else
	    {
		Memory::UninitializedFillN(mFinish, count - elemAfter, value);
		mFinish += count - elemAfter;
		Memory::UninitializedCopy(position, oldFinish, mFinish);
		mFinish += elemAfter;
		Memory::Fill(position, oldFinish, value);
	    }
	}
	else // do not have enough space
	{   
	    // start copy
	    const xsize oldSize = GetSize();
	    const xsize newCap = oldSize + Algorithm::GetMax(oldSize, count);
	    Iterator newStart = Allocator::Allocate(newCap);
	    Iterator newFinish = Memory::UninitializedCopy(mStart, position, newStart);
	    newFinish = Memory::UninitializedFillN(newFinish, count, value);
	    newFinish = Memory::UninitializedCopy(position, mFinish, newFinish);
	    
	    // destory and deallocate
	    Memory::Destroy(mStart, mFinish);
	    Deallocate();

	    // update the three m values 
	    mStart = newStart;
	    mFinish = newFinish;
	    mEndOfStorage = newStart + newCap;
	}
	
	return position + count;
    }

    template <typename T, typename TAllocator>
    inline void Array<T, TAllocator>::Deallocate()
    {
	if (mStart != nullptr)
	{
	    Allocator::Deallocate(mStart, mEndOfStorage - mStart);
	}
    }

    template <typename T, typename TAllocator>
    inline typename Array<T, TAllocator>::Iterator
	Array<T, TAllocator>::AllocateAndFill(xsize count, const T & value)
    {
	Iterator ans = Allocator::Allocate(count);
	Memory::UninitializedFillN(ans, count, value);
	return ans;
    }

    template <typename T, typename TAllocator>
    inline void Array<T, TAllocator>::FillInitialize(xsize count, const T & value)
    {
	mStart = AllocateAndFill(count, value);
	mFinish = mStart + count;
	mEndOfStorage = mFinish;
    }

    template <typename T, typename TAllocator>
    inline void Array<T, TAllocator>::Copy(const Array<T, TAllocator> & rhs)
    {
	if (rhs.IsEmpty())
	{
	    mStart = mFinish = mEndOfStorage = nullptr;
	}

	mStart = Allocator::Allocate(rhs.GetCapacity());
	mEndOfStorage = mStart + rhs.GetCapacity();
	mFinish = Memory::UninitializedCopy(rhs.GetBegin(), rhs.GetEnd(), mStart);
    }
}

#endif // XCARRAY_H