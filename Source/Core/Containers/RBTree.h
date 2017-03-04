#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"
#include "../Iterators/Iterators.h"

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
        RBTreeNodeBase * GetMinimum(RBTreeNodeBase * node)
        {
            while (node->mLeft != nullptr)
            {
                node = node->mLeft;
            }

            return node;
        }

        RBTreeNodeBase * GetMaximum(RBTreeNodeBase * node)
        {
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

                if (mNode->mRight != parent)
                {
                    mNode = parent;     
                }
            }

            void Decrement()
            {

            }
        }
    public:
        RBTreeNodeBase * mNode;
    };

    template <typename T>
    class RBTree
    {

    };

} XC_END_NAMESPACE_3;