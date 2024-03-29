// RBTree is base class for set and map

#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"
#include "../Iterators/Iterators.h"
#include "../Memories/Allocators.h"
#include "Pair.h"
#include "../Iterators/Iterators.h"
#include "../Delegates/Delegates.h"

XC_BEGIN_NAMESPACE_3(XC, Containers, Details)
{
    enum class RBTreeColorType : bool
    {
        Red = false, Black = true,
    };

    template <typename T>
    class RBTreeNode
    {
    public:
        using LinkType = RBTreeNode<T> *;
        using ColorType = RBTreeColorType;
        using BasePointer = RBTreeNode *;

    public:
        RBTreeNode* GetMinimum()
        {
            RBTreeNode * node = this;
            while (node->mLeft != nullptr)
            {
                node = node->mLeft;
            }

            return node;
        }

        RBTreeNode* GetMaximum()
        {
            RBTreeNode * node = this;
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
        RBTreeColorType mColor;
        T mValue;
    };

    template <typename T, typename TReference, typename TPointer>
    class RBTreeIterator
    {
    public:
        using ValueType = T;
        using Reference = TReference;
        using Pointer = TPointer;
        using Self = RBTreeIterator<T, TReference, TPointer>;
        using Iterator = RBTreeIterator<T, T &, T *>;
        using ConstantIterator = RBTreeIterator<T, const T &, const T *>;
        using LinkType = RBTreeNode<T> *;
        using IteratorCategory = Iterators::BidirectionalIteratorTag;
        using DifferenceType = xptrdiff;
        using Node = RBTreeNode<T>;

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

        Self& operator = (const Self& rhs)
        {
            mNode = rhs.mNode;
            return *this;
        }

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
                Node* y = mNode->mParent;
                while (mNode == y->mRight)
                {
                    mNode = y;
                    y = y->mParent;
                }

                if (mNode->mRight != y) // header
                {
                    mNode = y;
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
                Node* y = mNode->mLeft;
                while (y->mRight != nullptr)
                {
                    y = y->mRight;
                }
                mNode = y;
            }
            else
            {
                Node* y = mNode->mParent;
                while (mNode == y->mLeft)
                {
                    mNode = y;
                    y = y->mParent;
                }
                mNode = y;
            }
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

        Self operator ++ (int)
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

        Self operator -- (int)
        {
            Self ans = *this;
            --(*this);
            return ans;
        }

        bool operator == (const Self& rhs) const
        {
            return mNode == rhs.mNode;
        }

        bool operator != (const Self& rhs) const
        {
            return !(*this == rhs);
        }

    public:
        Node* mNode;
    };

    template <typename TKey, typename TValue, typename TKeyOfValue, typename TCompare, typename TAllocator = XC::DefaultAllocator<TValue>>
    class RBTree // TKeyOfValue is a functor
    {
    public:
        using KeyType = TKey;
        using ValueType = TValue;
        using Pointer = TValue *;
        using ConstantPointer = const ValueType *;
        using Reference = ValueType &;
        using ConstantReference = const ValueType &;
        using SizeType = xsize;
        using DifferenceType = xptrdiff;
        using VoidPointer = void *;
        using Node = RBTreeNode<ValueType>;
        using LinkType = Node *;
        using ConstantIterator = RBTreeIterator<ValueType, ConstantReference, ConstantPointer>;
        using Iterator = RBTreeIterator<ValueType, Reference, Pointer>;
        using Self = RBTree<TKey, TValue, TKeyOfValue, TCompare, TAllocator>;

        // allocators :
        using RBTreeNodeAllocator = DefaultAllocator<Node>;

    public:
        RBTree(const TCompare & compare = TCompare()) :
            mCountNodes(0), mKeyCompare(compare)
        {
            EmptyInitialize();
        }

        RBTree(const typename Self&) = delete;

        virtual ~RBTree()
        {
            Clear();
            PutNode(mHeader);
        }

        Self& operator = (const Self & rhs)
        {
            return *this;
        }

    public:
        ConstantIterator begin() const
        {
            return GetBegin();
        }

        Iterator begin()
        {
            return GetBegin();
        }

        ConstantIterator end() const
        {
            return GetEnd();
        }

        Iterator end()
        {
            return GetEnd();
        }

    public:
        ConstantIterator GetBegin() const
        {
            return GetMostLeft();
        }

        Iterator GetBegin()
        {
            return GetMostLeft();
        }

        ConstantIterator GetEnd() const
        {
            return mHeader;
        }

        Iterator GetEnd()
        {
            return mHeader;
        }

        xsize GetSize() const
        {
            return mCountNodes;
        }

        bool IsEmpty() const
        {
            return GetSize() == 0;
        }

        void Clear()
        {

        }

        // insert functions
        Iterator InsertEqual(const TValue& value)
        {
            Node* y = mHeader;
            Node* x = GetRoot();
            while (x != nullptr)
            {
                y = x;
                x = mKeyCompare(TKeyOfValue()(value), GetKey(x)) ? GetLeft(x) : GetRight(x);
            }
            return Insert(x, y, value);
        }

        // bool claims if it is inserted success
        Pair<Iterator, bool> InsertUnique(const TValue& value)
        {
            Node* y = mHeader;
            Node* x = GetRoot();
            bool comp = true;
            while (x != nullptr)
            {
                y = x;
                comp = mKeyCompare(TKeyOfValue()(value), GetKey(x));
                x = comp ? GetLeft(x) : GetRight(x);
            }

            Iterator j = Iterator(y);
            if (comp)
            {
                if (j == GetBegin())
                {
                    return Pair<Iterator, bool>(Insert(x, y, value), true);
                }
                else
                {
                    --j;
                }
            }

            if (mKeyCompare(GetKey(j.mNode), TKeyOfValue()(value)))
            {
                return Pair<Iterator, bool>(Insert(x, y, value), true);
            }
            else
            {
                return Pair<Iterator, bool>(j, false);
            }
        }

        ConstantIterator Find(const TKey& key) const
        {
            Node* y = mHeader; // y is greaterequal than key
            Node* x = GetRoot();
            while (x != nullptr)
            {
                if (!mKeyCompare(GetKey(x), key))
                {
                    y = x;
                    x = GetLeft(x);
                }
                else
                {
                    x = GetRight(x);
                }
            }

            ConstantIterator j = ConstantIterator(y);
            return j == GetEnd() || mKeyCompare(key, GetKey(j.mNode)) ? GetEnd() : j; // key cannot greater than node's key
        }

        Iterator Find(const TKey& key)
        {
            Node* y = mHeader; // y is greaterequal than key
            Node* x = GetRoot();
            while (x != nullptr)
            {
                if (!mKeyCompare(GetKey(x), key))
                {
                    y = x;
                    x = GetLeft(x);
                }
                else
                {
                    x = GetRight(x);
                }
            }

            Iterator j = Iterator(y);
            return j == GetEnd() || mKeyCompare(key, GetKey(j.mNode)) ? GetEnd() : j; // key cannot greater than node's key
        }

        ConstantIterator GetLowerBoound(const TKey& key) const
        {
            Node* y = mHeader; // y is greaterequal than key
            Node* x = GetRoot();
            while (x != nullptr)
            {
                if (!mKeyCompare(GetKey(x), key))
                {
                    y = x;
                    x = GetLeft(x);
                }
                else
                {
                    x = GetRight(x);
                }
            }

            return ConstantIterator(y);
        }

        Iterator GetLowerBound(const TKey& key)
        {
            Node* y = mHeader; // y is greaterequal than key
            Node* x = GetRoot();
            while (x != nullptr)
            {
                if (!mKeyCompare(GetKey(x), key))
                {
                    y = x;
                    x = GetLeft(x);
                }
                else
                {
                    x = GetRight(x);
                }
            }

            return Iterator(y);
        }

        ConstantIterator GetUpperBound(const TKey& key) const
        {
            Node* y = mHeader; // y is less than key
            Node* x = GetRoot();
            while (x != nullptr)
            {
                if (mKeyCompare(key, GetKey(x)))
                {
                    y = x;
                    x = GetLeft(x);
                }
                else
                {
                    x = GetRight();
                }
            }

            return ConstantIterator(y);
        }

        Iterator GetUpperBound(const TKey& key)
        {
            Node* y = mHeader; // y is less than key
            Node* x = GetRoot();
            while (x != nullptr)
            {
                if (mKeyCompare(key, GetKey(x)))
                {
                    y = x;
                    x = GetLeft(x);
                }
                else
                {
                    x = GetRight(x);
                }
            }

            return Iterator(y);
        }

        Pair<ConstantIterator, ConstantIterator> GetEqualRange(const TKey& key) const
        {
            return Pair<ConstantIterator, ConstantIterator>(GetLowerBound(key), GetUpperBound(key));
        }

        Pair<Iterator, Iterator> GetEqualRange(const TKey& key)
        {
            return Pair<Iterator, Iterator>(GetLowerBound(key), GetUpperBound(key));
        }

        xsize GetCount(const TKey& key) const
        {
            Pair<ConstantIterator, ConstantIterator> p = GetEqualRange(key);
            xsize n = 0;
            n = Iterators::GetDistance(p.mFirst, p.mSecond);
            return n;
        }

        bool Contains(const TKey& key) const
        {
            return Find(key) != GetEnd();
        }

        void Erase(Iterator position)
        {
            Node* y = EraseRebalance(position.mNode, mHeader->mParent, mHeader->mLeft, mHeader->mRight);
            DestroyNode(y);
            --mCountNodes;
        }

        void Erase(Iterator first, Iterator last)
        {
            while (first != last)
            {
                Erase(first++);
            }
        }

        SizeType Erase(const TKey& key)
        {
            Pair<Iterator, Iterator>  p = GetEqualRange(key);
            SizeType n = 0;
            n = Iterators::GetDistance(p.mFirst, p.mSecond);
            Erase(p.mFirst, p.mSecond);
            return n;
        }

    protected: public:
        Node* GetNode()
        {
            return RBTreeNodeAllocator::Allocate();
        }

        void PutNode(Node* node)
        {
            RBTreeNodeAllocator::Deallocate(node);
        }

        Node* CreateNode(const TValue & value)
        {
            LinkType ans = GetNode();
            Memories::Construct(&ans->mValue, value);
            return ans;
        }

        Node* CloneNode(Node* node)
        {
            Node* ans = CreateNode(node->mValue);
            ans->mColor = node->mColor;
            ans->mLeft = nullptr;
            ans->mRight = nullptr;
            return ans;
        }

        void DestroyNode(Node* node)
        {
            Memories::Destroy(&node->mValue);
            PutNode(node);
        }

        // node functions, static like
        TValue& GetValue(Node* node) const
        {
            return node->mValue;
        }

        Node* & GetLeft(Node* node) const
        {
            return node->mLeft;
        }

        Node* & GetRight(Node* node) const
        {
            return node->mRight;
        }

        const TKey& GetKey(Node* node) const
        {
            return TKeyOfValue()(GetValue(node));
        }

        Node* & GetParent(Node* node) const
        {
            return node->mParent;
        }

        RBTreeColorType& GetColor(Node* node) const
        {
            return node->mColor;
        }

        Node* & GetRoot() const
        {
            return mHeader->mParent;
        }

        Node* & GetMostLeft() const
        {
            return mHeader->mLeft;
        }

        Node* & GetMostRight() const
        {
            return mHeader->mRight;
        }

        Node* & GetMaximum(Node* node) const
        {
            return node->GetMaximum();
        }

        Node* & GetMinimum(Node* node) const
        {
            return node->GetMinimum();
        }

        void EmptyInitialize()
        {
            mHeader = GetNode();
            mHeader->mColor = RBTreeColorType::Red;
            GetRoot() = nullptr;
            GetMostLeft() = mHeader;
            GetMostRight() = mHeader;
        }

        Iterator Insert(Node* x, Node* y, const TValue& value)
        {
            Node* z = nullptr;
            if (y == mHeader || x != nullptr || mKeyCompare(TKeyOfValue()(value), GetKey(y)))
            {
                z = CreateNode(value);
                GetLeft(y) = z;
                if (y == mHeader)
                {
                    GetRoot() = z;
                    GetMostRight() = z;
                }
                else if (y == GetMostLeft())
                {
                    GetMostLeft() = z;
                }
            }
            else
            {
                z = CreateNode(value);
                GetRight(y) = z;
                if (y == GetMostRight())
                {
                    GetMostRight() = z;
                }
            }

            GetParent(z) = y;
            GetLeft(z) = nullptr;
            GetRight(z) = nullptr;

            Rebalance(z, mHeader->mParent);
            ++mCountNodes;
            return Iterator(z);
        }

        void Rebalance(Node* x, Node* & root)
        {
            x->mColor = RBTreeColorType::Red;
            while (x != root && x->mParent->mColor == RBTreeColorType::Red)
            {
                if (x->mParent == x->mParent->mParent->mLeft)
                {
                    Node* y = x->mParent->mParent->mRight;
                    if (y != nullptr && y->mColor == RBTreeColorType::Red)
                    {
                        x->mParent->mColor = RBTreeColorType::Black;
                        y->mColor = RBTreeColorType::Black;
                        x->mParent->mParent->mColor = RBTreeColorType::Red;
                        x = x->mParent->mParent;
                    }
                    else
                    {
                        if (x == x->mParent->mRight)
                        {
                            x = x->mParent;
                            LeftRotate(x, root);
                        }
                        x->mParent->mColor = RBTreeColorType::Black;
                        x->mParent->mParent->mColor = RBTreeColorType::Red;
                        RightRotate(x->mParent->mParent, root);
                    }
                }
                else
                {
                    Node* y = x->mParent->mParent->mLeft;
                    if (y != nullptr && y->mColor == RBTreeColorType::Red)
                    {
                        x->mParent->mColor = RBTreeColorType::Black;
                        y->mColor = RBTreeColorType::Black;
                        x->mParent->mParent->mColor = RBTreeColorType::Red;
                        x = x->mParent->mParent;
                    }
                    else
                    {
                        if (x == x->mParent->mLeft)
                        {
                            x = x->mParent;
                            RightRotate(x, root);
                        }
                        x->mParent->mColor = RBTreeColorType::Black;
                        x->mParent->mParent->mColor = RBTreeColorType::Red;
                        LeftRotate(x->mParent->mParent, root);
                    }
                }
            }
            root->mColor = RBTreeColorType::Black;
        }

        Node* EraseRebalance(Node* node, Node* & root, Node* & mostLeft, Node* & mostRight)
        {
            Node* z = node;
            Node* y = z;
            Node* x = 0;
            Node* xParent = 0;
            if (y->mLeft == 0)     // z has at most one non-null child. y == z.
            {
                x = y->mRight;     // x might be null.
            }
            else
            {
                if (y->mRight == 0)  // z has exactly one non-nul	l child. y == z.
                {
                    x = y->mLeft;    // x is not null.
                }
                else
                {                   // z has two non-null children.  Set y to
                    y = y->mRight;   //   z's successor.  x might be null.
                    while (y->mLeft != 0)
                    {
                        y = y->mLeft;
                    }
                    x = y->mRight;
                }
            }

            if (y != z)
            {          // relink y in place of z.  y is z's successor
                z->mLeft->mParent = y;
                y->mLeft = z->mLeft;
                if (y != z->mRight)
                {
                    xParent = y->mParent;
                    if (x)
                    {
                        x->mParent = y->mParent;
                    }
                    y->mParent->mLeft = x;      // y must be a child of mLeft
                    y->mRight = z->mRight;
                    z->mRight->mParent = y;
                }
                else
                {
                    xParent = y;
                }

                if (root == z)
                {
                    root = y;
                }
                else if (z->mParent->mLeft == z)
                {
                    z->mParent->mLeft = y;
                }
                else
                {
                    z->mParent->mRight = y;
                }

                y->mParent = z->mParent;
                Algorithms::Swap(y->mColor, z->mColor);
                y = z;
                // y now points to node to be actually deleted
            }
            else
            {                        // y == z
                xParent = y->mParent;
                if (x)
                {
                    x->mParent = y->mParent;
                }

                if (root == z)
                {
                    root = x;
                }
                else
                {
                    if (z->mParent->mLeft == z)
                    {
                        z->mParent->mLeft = x;
                    }
                    else
                    {
                        z->mParent->mRight = x;
                    }
                }

                if (mostLeft == z)
                {
                    if (z->mRight == 0)        // z->mLeft must be null also
                    {
                        mostLeft = z->mParent;
                        // makes mostLeft == _M_header if z == root
                    }
                    else
                    {
                        mostLeft = x->GetMinimum();
                    }
                }

                if (mostRight == z)
                {
                    if (z->mLeft == 0)         // z->mRight must be null also
                    {
                        mostRight = z->mParent;
                        // makes mostRight == _M_header if z == root
                    }
                    else                      // x == z->mLeft
                    {
                        mostRight = x->GetMaximum();
                    }
                }
            }

            if (y->mColor != RBTreeColorType::Red)
            {
                while (x != root && (x == 0 || x->mColor == RBTreeColorType::Black))
                {
                    if (x == xParent->mLeft)
                    {
                        Node* w = xParent->mRight;
                        if (w->mColor == RBTreeColorType::Red)
                        {
                            w->mColor = RBTreeColorType::Black;
                            xParent->mColor = RBTreeColorType::Red;
                            LeftRotate(xParent, root);
                            ChangedEvent.Invoke();
                            w = xParent->mRight;
                        }

                        if ((w->mLeft == 0 || w->mLeft->mColor == RBTreeColorType::Black) &&
                            (w->mRight == 0 || w->mRight->mColor == RBTreeColorType::Black)
                            )
                        {
                            w->mColor = RBTreeColorType::Red;
                            x = xParent;
                            xParent = xParent->mParent;
                        }
                        else
                        {
                            if (w->mRight == 0 || w->mRight->mColor == RBTreeColorType::Black)
                            {
                                if (w->mLeft)
                                {
                                    w->mLeft->mColor = RBTreeColorType::Black;
                                }
                                w->mColor = RBTreeColorType::Red;
                                RightRotate(w, root);
                                w = xParent->mRight;
                            }
                            w->mColor = xParent->mColor;
                            xParent->mColor = RBTreeColorType::Black;
                            if (w->mRight)
                            {
                                w->mRight->mColor = RBTreeColorType::Black;
                            }
                            LeftRotate(xParent, root);
                            break;
                        }
                    }
                    else
                    {                  // same as above, with mRight <-> mLeft.
                        Node* w = xParent->mLeft;
                        if (w->mColor == RBTreeColorType::Red)
                        {
                            w->mColor = RBTreeColorType::Black;
                            xParent->mColor = RBTreeColorType::Red;
                            RightRotate(xParent, root);
                            w = xParent->mLeft;
                        }

                        if ((w->mRight == 0 || w->mRight->mColor == RBTreeColorType::Black) &&
                            (w->mLeft == 0 || w->mLeft->mColor == RBTreeColorType::Black)
                            )
                        {
                            w->mColor = RBTreeColorType::Red;
                            x = xParent;
                            xParent = xParent->mParent;
                        }
                        else
                        {
                            if (w->mLeft == 0 || w->mLeft->mColor == RBTreeColorType::Black)
                            {
                                if (w->mRight)
                                {
                                    w->mRight->mColor = RBTreeColorType::Black;
                                }
                                w->mColor = RBTreeColorType::Red;
                                LeftRotate(w, root);
                                w = xParent->mLeft;
                            }
                            w->mColor = xParent->mColor;
                            xParent->mColor = RBTreeColorType::Black;
                            if (w->mLeft)
                            {
                                w->mLeft->mColor = RBTreeColorType::Black;
                            }
                            RightRotate(xParent, root);
                            break;
                        }
                    }
                }

                if (x)
                {
                    x->mColor = RBTreeColorType::Black;
                }
            }
            return y;
        }

        void LeftRotate(Node* x, Node* & root)
        {
            Node* y = x->mRight;
            x->mRight = y->mLeft;
            if (y->mLeft != nullptr)
            {
                y->mLeft->mParent = x;
            }
            y->mParent = x->mParent;
            if (x == root)
            {
                root = y;
            }
            else if (x == x->mParent->mLeft)
            {
                x->mParent->mLeft = y;
            }
            else
            {
                x->mParent->mRight = y;
            }
            y->mLeft = x;
            x->mParent = y;
        }

        void RightRotate(Node* x, Node* & root)
        {
            Node* y = x->mLeft;
            x->mLeft = y->mRight;
            if (x->mRight != nullptr)
            {
                y->mRight->mParent = x;
            }

            y->mParent = x->mParent;
            if (x == root)
            {
                root = y;
            }
            else if (x == x->mParent->mRight)
            {
                x->mParent->mRight = y;
            }
            else
            {
                x->mParent->mLeft = y;
            }
            y->mRight = x;
            x->mParent = y;
        }

    private: public:
        Delegate<void> ChangedEvent;
        xsize mCountNodes;
        Node* mHeader;
        TCompare mKeyCompare;
    };

} XC_END_NAMESPACE_3;

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "../Functors/Functors.h"

XC_BEGIN_NAMESPACE_1(XC_RBTREE_TEST)
{
    using namespace std;
    using namespace XC::Containers::Details;
    using namespace XC::Functors;

    class KeyOfValue
    {
    public:
        const int& operator () (const int& value) const
        {
            return value;
        }
    };

    class Compare
    {
    public:
        bool operator () (const int& lhs, const int& rhs) const
        {
            return lhs > rhs;
        }
    };

    using Tree = RBTree<int, int, KeyOfValue, Less<int> >;

    template <typename T>
    void Print(T & t)
    {
        std::cout << "gerg ";
        for (auto itr = t.begin(); itr != t.end(); ++itr)// : t)// : t)
        {
            std::cout << *itr << " ";
        }
        std::cout << std::endl;
    }

    static int arr[100] =
    { 
        59,58,9,37,96,56,68,28,92,66,26,31,90,8,69,38,47,33,51,4,49,51,27,19,86,94,91,24,
        66,62,74,36,20,22,82,96,13,94,36,58,85,75,74,72,10,65,48,24,42,26,55,
        97,80,74,63,65,82,41,28,32,38,48,10,16,74,54,47,97,69,82,45,26,70,43,5,21,83,
        15,27,72,7,96,83,36,47,22,24,22,35,80,27,95,31,18,50,76,51,67,1,15,
    };

    XC_TEST_CASE(FSGEIWEG)
    {
        return;
        int times = 1000;
        while (times--)
        {
            srand(time(nullptr));
            std::cout << std::endl;
            std::cout << "Begin RBTree test" << std::endl;

            // Less compare;
            Tree tree;
            Tree::Iterator begin = tree.GetBegin();
            /*    for (int i = 0; i < 100; ++i)
                {
                    arr[i] = rand() % 100;
                    tree.InsertUnique(arr[i]);
                }
                */
            for (auto i : arr)
            {
                tree.InsertUnique(i);
            }
            Print(tree);
            std::cout << std::endl;
            Tree::Iterator itr = ++tree.GetBegin();
            ++itr;
            ++itr;
            ++itr;
            tree.Erase(itr);
            Print(tree);
            std::cout << std::endl;
            for (int i = 0; i < 50; ++i)
            {
                tree.Erase(i);
            }
            Print(tree);
            std::cout << "end RBTree test" << std::endl;
        }

    }

} XC_END_NAMESPACE_1;