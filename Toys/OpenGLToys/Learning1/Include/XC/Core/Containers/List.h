
#ifndef XCLIST_H
#define XCLIST_H

#include "../XCBasic.h"
#include "../XCMemory.h"
#include "../XCIterators.h"
#include "../XCTypeTraits.h"

namespace XC
{
    template <typename T, typename TAllocator = DefaultAllocator<T> > // The TAllocator typename is unused
    class List
    {
    public:
        struct Node
        {
            typedef Node * Pointer;
            Pointer mNext;
            Pointer mPrevious;
            T mData;
        };

        template <typename TReference, typename TPointer>
        class BaseIterator
        {
        public:
            typedef BaseIterator<const T &, const T *> ConstantIterator;
            typedef BaseIterator<T &, T *> Iterator;
            typedef BaseIterator<TReference, TPointer> Self;

            // These five typedefs are for the iterator traits.
            typedef BidirectionalIteratorTag IteratorCategory;
            typedef T ValueType;
            typedef xpointerdifference DifferenceType;
            typedef TPointer Pointer; // Pointer and reference type declares if it is const.
            typedef TReference Reference;

            typedef Node * LinkType;
            typedef xsize SizeType;

            BaseIterator() {}
            BaseIterator(Node * node) : mNode(node) {}
            BaseIterator(const Self & rhs) : mNode(rhs.mNode) {}
            Self & operator = (const Self & rhs);
            ~BaseIterator() {}
            bool operator == (const Self & rhs) const { return mNode == rhs.mNode; }
            bool operator != (const Self & rhs) const { return !(*this == rhs.mNode); }
            Reference operator * () const { return (*mNode).mData; }
            Pointer operator -> () const { return &(operator * ()); }
            Self & operator ++ ();
            Self & operator -- ();
            Self & operator ++ (int);
            Self & operator -- (int);

            Node * mNode;

            friend class List<T, TAllocator>; // List can visit mNode.
        };

    public:
        // These are basic defs.
        typedef T ValueType;
        typedef xpointerdifference DifferenceType;
        typedef T * Pointer;
        typedef T & Reference;
        typedef xsize SizeType;

        // The iterators.
        typedef BaseIterator<const T &, const T *> ConstantIterator;
        typedef BaseIterator<T &, T *> Iterator;

        typedef List<T, TAllocator> Self;
        typedef Node * LinkType;

    public:
        List() { EmptyInitialize(); }
        List(const Self & rhs);
        ~List() { ReleaseMemory(); }
        Self & operator = (const Self & rhs);
        bool operator == (const Self & rhs) const;
        bool operator != (const Self & rhs) const { return !(*this == rhs); }

        ConstantIterator GetBegin() const { return ConstantIterator(mNode->mNext); }
        Iterator GetBegin() { return Iterator(mNode->mNext); }
        ConstantIterator GetEnd() const { return ConstantIterator(mNode); }
        Iterator GetEnd() { return Iterator(mNode); }
        bool IsEmpty() const { return mNode->mNext == mNode; }
        xsize GetSize() const;
        const T & GetFront() const { return *GetBegin(); }
        T & GetFront() { return *GetBegin(); }
        const T & GetBack() const { return *(--GetEnd()); }
        T & GetBack() { return *(--GetEnd()); }
        Iterator Insert(Iterator position, const T & value);
        Iterator Erase(Iterator position);
        void PushBack(const T & value) { Insert(GetEnd(), value); }
        void PopBack() { Erase(--GetEnd()); }
        void PushFront(const T & value) { Insert(GetBegin(), value); }
        void PopFront() { Erase(GetBegin()); }
        void Clear();

        // These are for c++11 "for" statement.
        ConstantIterator begin() const { return GetBegin(); }
        Iterator begin() { return GetBegin(); }
        ConstantIterator end() const { return GetEnd(); }
        Iterator end() { return GetEnd(); }

    protected:
        typedef InsideAllocator<Node, DefaultAllocator<Node> > NodeAllocator;

        Node * AllocateNode() { return NodeAllocator::Allocate(); }
        void DeallocateNode(Node * node) { NodeAllocator::Deallocate(node); }
        Node * CreateNode(const T & value);
        void RemoveNode(Node * node);
        void EmptyInitialize();
        void ReleaseMemory();
        void CopyAll(const Self & rhs);

        Node * mNode;
    };

    template <typename T, typename TAllocator>
    template <typename TReference, typename TPointer>
    inline typename List<T, TAllocator>::template BaseIterator<TReference, TPointer>::Self &
    List<T, TAllocator>::BaseIterator<TReference, TPointer>::operator = (const Self & rhs)
    {
        mNode = rhs.mNode;
        return *this;
    }

    template <typename T, typename TAllocator>
    template <typename TReference, typename TPointer>
    inline typename List<T, TAllocator>::template BaseIterator<TReference, TPointer>::Self &
    List<T, TAllocator>::BaseIterator<TReference, TPointer>::operator ++ ()
    {
        mNode = mNode->mNext;
        return *this;
    }

    template <typename T, typename TAllocator>
    template <typename TReference, typename TPointer>
    inline typename List<T, TAllocator>::template BaseIterator<TReference, TPointer>::Self &
    List<T, TAllocator>::BaseIterator<TReference, TPointer>::operator -- ()
    {
        mNode = mNode->mPrevious;
        return *this;
    }

    template <typename T, typename TAllocator>
    template <typename TReference, typename TPointer>
    inline typename List<T, TAllocator>::template BaseIterator<TReference, TPointer>::Self &
    List<T, TAllocator>::BaseIterator<TReference, TPointer>::operator ++ (int)
    {
        Self ans = *this;
        ++this;
        return ans;
    }

    template <typename T, typename TAllocator>
    template <typename TReference, typename TPointer>
    inline typename List<T, TAllocator>::template BaseIterator<TReference, TPointer>::Self &
    List<T, TAllocator>::BaseIterator<TReference, TPointer>::operator -- (int)
    {
        Self ans = *this;
        --this;
        return ans; 
    }

    template <typename T, typename TAllocator>
    List<T, TAllocator>::List(const Self & rhs)
    {
        EmptyInitialize();
        CopyAll(rhs);
    }

    template <typename T, typename TAllocator>
    typename List<T, TAllocator>::Self & List<T, TAllocator>::operator = (const Self & rhs)
    {
        Clear();
        CopyAll(rhs);
        return *this;
    }

    template <typename T, typename TAllocator>
    inline xsize List<T, TAllocator>::GetSize() const
    {
        xsize ans = 0;
        Node * cur = mNode->mNext;
        while (cur != mNode)
        {
            ans++;
            cur = cur->mNext;
        }

        return ans;
    }

    template <typename T, typename TAllocator>
    inline typename List<T, TAllocator>::Iterator
    List<T, TAllocator>::Insert(Iterator position, const T & value)
    {
        Node * posNode = position.mNode;
        Node * node = CreateNode(value);
        node->mPrevious = posNode->mPrevious;
        node->mNext = posNode;
        posNode->mPrevious->mNext = node;
        posNode->mPrevious = node;

        return Iterator(node);
    }

    template <typename T, typename TAllocator>
    inline typename List<T, TAllocator>::Iterator
    List<T, TAllocator>::Erase(Iterator position)
    {
        Node * cur = position.mNode;
        Node * prev = cur->mPrevious;
        Node * next = cur->mNext;
        prev->mNext = next;
        next->mPrevious = prev;
        RemoveNode(cur);
        return Iterator(next);
    }

    template<typename T, typename TAllocator>
    inline void List<T, TAllocator>::Clear()
    {
        Node * cur = mNode->mNext;
        while (cur != mNode)
        {
            Node * tmp = cur;
            cur = tmp->mNext;
            RemoveNode(tmp);
        }

        mNode->mPrevious = mNode;
        mNode->mNext = mNode;
    }

    template <typename T, typename TAllocator>
    inline typename List<T, TAllocator>::Node *
    List<T, TAllocator>::CreateNode(const T & value)
    {
        Node * ans = AllocateNode();
        Memory::Construct(&ans->mData, value);
        return ans;
    }

    template <typename T, typename TAllocator>
    inline void List<T, TAllocator>::RemoveNode(Node * node)
    {
        Memory::Destroy(node);
        DeallocateNode(node);
    }

    template <typename T, typename TAllocator>
    inline void List<T, TAllocator>::EmptyInitialize()
    {
        mNode = AllocateNode();
        mNode->mNext = mNode;
        mNode->mPrevious = mNode;
    }

    template <typename T, typename TAllocator>
    inline void List<T, TAllocator>::ReleaseMemory()
    {
        Clear();
        NodeAllocator::Deallocate(mNode);
    }

    template <typename T, typename TAllocator>
    void List<T, TAllocator>::CopyAll(const Self & rhs)
    {
        for (ConstantIterator itr = rhs.GetBegin(); itr != rhs.GetEnd(); ++itr)
        {
            PushBack(*itr);
        }
    }
}

#endif // XCLIST_H
