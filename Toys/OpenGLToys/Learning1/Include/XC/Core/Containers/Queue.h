#ifndef XCQUEUE_H
#define XCQUEUE_H

#include "Dequeue.h"

namespace XC
{
	template <typename T, typename TContainer = Dequeue<T> >
	class Queue
	{
	public:
		typedef typename Queue<T, TContainer> Self;
		typedef typename TContainer::SizeType SizeType;

	public:
		Queue() = default;
		Queue(const Self & rhs) : mContanier(rhs.mContainer) {}
		~Queue() = default;
		Self & operator = (const Self & rhs) { mContainer = rhs; }

		const T & GetFront() const { return mContainer.GetFront(); }
		const T & GetBack() const { return mContainer.GetBack(); }
		SizeType GetSize() const { return mContainer.GetSize(); }
		bool IsEmpty() const { return mContainer.IsEmpty(); }
		bool operator == (const Self & rhs) const { return mContainer == rhs.mContainer; }
		bool operator != (const Self & rhs) const { return !(*this == rhs); }

		T & GetFront() { return mContainer.GetFront(); }
		T & GetBack() { return mContainer.GetBack(); }
		void Push(const T & value) { mContainer.PushBack(value); }
		void Pop() { mContainer.PopFront(); }
		void Clear() { mContainer.Clear(); }
	
	private:
		TContainer mContainer;
	};
}

#endif // XCQUEUE_H