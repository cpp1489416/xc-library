
#pragma once

#include "DEQueue.h"

XC_BEGIN_NAMESPACE_1(XC)
{
    template <typename T, typename TContainer = DEQueue<T> >
    class Queue
    {
    public:
        using Self = Queue<T, TContainer>;
        using SizeType = typename TContainer::SizeType;

    public:
        Queue() = default;
        Queue(const Self & rhs) : mContanier(rhs.mContainer) {}
        ~Queue() = default;
        Self & operator = (const Self & rhs) { mContainer = rhs; }

    public:
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

} XC_END_NAMESPACE_1
