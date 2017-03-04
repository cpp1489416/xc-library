#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"

XC_BEGIN_NAMESPACE_3(XC, Containers, Details)
{
    enum class RBTreeColorType : bool
    {
        Red = false, Black = true,
    };

    class RBTreeNode
    {
    public:
        using ColorType = RBTreeColorType;
        using BasePointer = RBTreeNode *;
        
    public:
        RBTreeNode * GetMinimum(RBTreeNode * node)
        {
            while (node->mLeft != nullptr)
            {
                node = node->mLeft;
            }

            return node;
        }

        RBTreeNode * GetMaximum(RBTreeNode * node)
        {
            while (node->mRight != nullptr)
            {
                node = node->mRight;
            }

            return node;
        }

    public:
        RBTreeNode * mParent;
        RBTreeNode * mLeft;
        RBTreeNode * mRight;
    };

    template <typename T>
    class RBTree
    {

    };

} XC_END_NAMESPACE_3;