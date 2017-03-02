#ifndef XCSTACK_H
#define XCSTACK_H

#include "DEQueue.h"

namespace XC
{
	template <typename T, typename TContainer = DEQueue<T> >
	class Stack
	{
	public:
        using Self = Stack<T, TContainer>;
        using SizeType = typename TContainer::SizeType;

	public:
		Stack() = default;
		Stack(const Self & other) : mContainer(other.mContainer) {}
		~Stack() = default;
		Self & operator = (const Self & rhs) { mContainer = rhs.mContainer; }

    public:
		const T & GetTop() const { return mContainer.GetFront(); }
		SizeType GetSize() const { return mContainer.GetSize(); }
		bool IsEmpty() const { return mContainer.IsEmpty(); }
		bool operator == (const Self & rhs) const { return mContainer == rhs.mContainer; }
		bool operator != (const Self & rhs) const { return !(*this == rhs); }
		T & GetTop() { return mContainer.GetFront(); }
		void Push(const T & value) { mContainer.PushBack(value); }
		void Pop() { mContainer.PopBack(); }
		void Clear() { mContainer.Clear(); }

	private:
		TContainer mContainer;	
    };
}

#endif // XCSTACK_H