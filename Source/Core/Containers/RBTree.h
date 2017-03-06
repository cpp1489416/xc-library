#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"
#include "../Iterators/Iterators.h"
#include "../Memories/Allocators.h"

XC_BEGIN_NAMESPACE_3(XC, Containers, Details)
{
    enum class RBTreeColorType : bool
    {
        Red = false, Black = true,
    };

    class RBTreeNodeBase
    {
    public:
        using ColorType = RBTreeColorType;
        using BasePointer = RBTreeNodeBase *;

    public:
        RBTreeNodeBase * GetMinimum()
        {
            RBTreeNodeBase * node = this;
            while (node->mLeft != nullptr)
            {
                node = node->mLeft;
            }

            return node;
        }

        RBTreeNodeBase * GetMaximum()
        {
            RBTreeNodeBase * node = this;
            while (node->mRight != nullptr)
            {
                node = node->mRight;
            }

            return node;
        }

    public:
        RBTreeNodeBase * mParent;
        RBTreeNodeBase * mLeft;
        RBTreeNodeBase * mRight;
        RBTreeColorType mColor;
    };

    template <typename T>
    class RBTreeNode : public RBTreeNodeBase
    {
    public:
        using LinkType = RBTreeNode<T> *;

    public:
        T mValue;
    };

    class RBTreeBaseIterator
    {
    public:
        using IteratorCategory = Iterators::BidirectionalIteratorTag;
        using DifferenceType = xptrdiff;

    public:
        void Increment()
        {
            if (mNode->mRight != nullptr)
            {
                mNode = mNode->mRight;
                while (mNode->mLeft != nullptr)
                {
                    mNode = mNode->mLeft;
                }
            }
            else
            {
                RBTreeNodeBase * parent = mNode->mParent;
                while (mNode == parent->mRight)
                {
                    mNode = parent;
                    parent = parent->mParent;
                }

                if (mNode->mRight != parent) // header
                {
                    mNode = parent;
                }
            }
        }

        void Decrement()
        {
            if (mNode->mColor == RBTreeColorType::Red && mNode->mParent->mParent == mNode)
            {
                mNode = mNode->mRight; // header 
            }
            else if (mNode->mLeft != nullptr)
            {
                RBTreeNodeBase * y = mNode->mLeft;
                while (y->mRight != nullptr)
                {
                    y = y->mRight;
                }
                mNode = y;
            }
            else
            {
                RBTreeNodeBase * y = mNode->mParent;
                while (mNode == y->mLeft)
                {
                    mNode = y;
                    y = y->mParent;
                }
                mNode = y;
            }
        }

    public:
        RBTreeNodeBase * mNode;
    };

    template <typename T, typename TReference, typename TPointer>
    class RBTreeIterator : public RBTreeBaseIterator
    {
    public:
        using ValueType = T;
        using Reference = TReference;
        using Pointer = TPointer;
        using Self = RBTreeIterator<T, TReference, TPointer>;
        using Iterator = RBTreeIterator<T, T &, T *>;
        using ConstantIterator = RBTreeIterator<T, const T &, const T *>;
        using LinkType = RBTreeNode<T> *;

    public:
        RBTreeIterator() = default;

        RBTreeIterator(RBTreeNode<T> * node)
        {
            mNode = node;
        }

        RBTreeIterator(const Iterator & iterator)
        {
            mNode = iterator.mNode;
        }

    public:
        Reference operator * () const
        {
            return mNode->mValue;
        }

        Pointer operator -> () const
        {
            return &(operator *());
        }

        Self & operator ++ ()
        {
            Increment();
            return *this;
        }

        Self & operator ++ (int)
        {
            Self ans = *this;
            ++(*this);
            return ans;
        }

        Self & operator -- ()
        {
            Decrement();
            return *this;
        }

        Self & operator -- (int)
        {
            Self ans = *this;
            --(*this);
            return ans;
        }

    public:
        RBTreeNode<T> * mNode;
    };

    template <typename TKey, typename TValue, typename TKeyOfValue, typename TCompare, typename TAllocator = XC::DefaultAllocator<T> >
    class RBTree // TKeyOfValue is a functor
    {
    public:
        using KeyType = TKey;
        using ValueType = TValue;
        using Pointer = TValue *;
        using ConstanctPointer = const ValueType *;
        using Reference = ValueType &;
        using ConstantReference = const ValueType &;
        using SizeType = xsize;
        using DifferenceType = xptrdiff;
        using VoidPointer = void *;
        using LinkType = RBTreeNode<ValueType>  *;
        using RBTreeNodeAllocator = DefaultAllocator<RBTreeNode<ValueType> >;
        using Iterator = RBTreeIterator<ValueType, Reference, Pointer>;

    public:
        RBTree(const TCompare & compare = Compare()) :
            mCountNodes(0), mKeyCompare(compare)
        {
            Initialize();
        }

        virtual ~RBTree()
        {
            Clear();
            PutNode(mHeader);
        }

    protected:
        LinkType GetNode()
        {
            return RBTreeNodeAllocator::Allocate();
        }

        LinkType PutNode(LinkType node)
        {
            return RBTreeNodeAllocator::(node);
        }

        LinkType CreateNode(const TValue & value)
        {
            LinkType ans = GetNode();
            Memories::Construct(&ans->mValue, value);
            return ans;
        }

        LinkType CloneNode(LinkType node)
        {
            LinkType ans = CreateNode(node->mValue);
            ans->mColor = node->mColor;
            ans->mLeft = nullptr;
            ans->mRight = nullptr;
            return ans;
        }

        void DestroyNode(LinkType node)
        {
            Memories::Destroy(&node->mValue);
            PutNode(node);
        }

        LinkType & GetRoot() const
        {
            return mHeader->mParent;
        }

        LinkType & GetMostLeft() const
        {
            return mHeader->mLeft;
        }

        LinkType & GetMostRight() const
        {
            return mHeader->mRight;
        }

        TKey & GetKey(LinkType node) const
        {
            return TKeyOfValue()(node->mValue);
        }

    private:
        Iterator Insert(RBTreeNodeBase * x, RBTreeNodeBase * y, const ValueType & value)
        {
            return Iterator();
        }

        void Initialize()
        {
            mHeader = GetNode();
            mHeader->mColor = RBTreeColorType::Red;
            GetRoot() = nullptr;
            GetMostLeft() = mHeader;
            GetMostRight() = mHeader;
        }

    private:
        xsize mCountNodes;
        LinkType mHeader;
        TCompare mKeyCompare;
    };

} XC_END_NAMESPACE_3;