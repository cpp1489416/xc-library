#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

namespace Xc
{
    template <typename T>
    class RedBlackTree
    {
    public:
        struct Node;
        typedef Node *NodePointer;

        struct Node
        {
        public:
            typedef bool ColorType;
            static const ColorType RED = true;
            static const ColorType BLACK = false;

        public:
            ~Node();
            Node(const T & value, ColorType color = RED, Node * parent = nullptr, Node * left = nullptr, Node * right = nullptr);
            inline T &value() { return *mValue; }

        public:
            Node * mLeft;
            Node * mRight;
            Node * mParent;
            ColorType mColor;
            int mTimes;
            
            T *mValue;
            friend class RedBlackTree<T>;
        };

    public:
        class ConstantIterator
        {
        public:
            inline ConstantIterator() {}
            inline ~ConstantIterator() {}
            inline const T &operator *() { return mNode->value(); } // the only different between const and not const
            ConstantIterator &operator ++ ();
            ConstantIterator &operator -- ();
            bool operator == (const ConstantIterator &rhs) const { return mNode == rhs.mNode; }
            inline bool operator != (const ConstantIterator &rhs) const { return !(*this == rhs); }
            inline bool operator < (const ConstantIterator &rhs) const { return mNode->value() < rhs.mNode->value(); }
            inline bool operator > (const ConstantIterator &rhs) const { return mNode->value() > rhs.mNode->value(); }
            ConstantIterator operator ++ (int) const;
            ConstantIterator operator -- (int) const;
			inline int GetTimes() const { return mNode->mTimes; }
			inline void SetTimes(int times) { mNode->mTimes = times; }

        protected:
            ConstantIterator(RedBlackTree<T> *tree, typename RedBlackTree<T>::Node *node);

            typename RedBlackTree<T> *mTree;
            Node *mNode;                            // these variables will also used by Iterator class

            friend class RedBlackTree<T>;
        };

        class Iterator : public ConstantIterator
        {
        public:
            inline Iterator() {}
            inline ~Iterator() {}
            inline T &operator *() { return mNode->value(); }
            inline T &Get() { return mNode->value(); }
            Iterator &operator ++ ();
            Iterator &operator -- ();
            bool operator == (const Iterator &rhs) const { return mNode == rhs.mNode; }
            inline bool operator != (const Iterator &rhs) const { return !(*this == rhs); }
            inline bool operator < (const Iterator &rhs) const { return mNode->value() < rhs.mNode->value(); }
            inline bool operator > (const Iterator &rhs) const { return mNode->value() > rhs.mNode->value(); }
            Iterator operator ++ (int) const;
            Iterator operator -- (int) const;
        
        private:
            Iterator(RedBlackTree<T> *tree, typename RedBlackTree<T>::Node *node);

            friend class RedBlackTree<T>;
        };

    public:
        inline RedBlackTree() : mRoot(nullptr) {}
        inline ~RedBlackTree() { eraseAll(); }
        inline Iterator insert(const T & value) { return Iterator(this, insert(mRoot, value)); }
        inline NodePointer UNSAFERoot() { return mRoot; } // unsafe function
        inline bool isRoot(NodePointer node) const { return node->mParent == nullptr; }
        typename Node::ColorType color(NodePointer node) const;
        bool erase(const T &value);
        inline void eraseAll() { erase(mRoot); }
        void print(NodePointer node);
        bool test(Node * cur, Node * root);
        Iterator begin();
        Iterator end();
        ConstantIterator begin() const;
        ConstantIterator end() const;
        inline ConstantIterator invalidConstantIterator() const { return ConstantIterator(this, nullptr); }
        inline Iterator invalidIterator() const { return Iterator(this, nullptr); }
        bool isExist(const T &element) const;

    private:
        NodePointer insert(NodePointer & node, const T & value);
        void insertFix(NodePointer node);
        void eraseFix(NodePointer node);
        void eraseLeftLackFix(NodePointer node);
        void eraseRightLackFix(NodePointer node);
        NodePointer sibling(NodePointer node);
        NodePointer uncle(NodePointer node);
        NodePointer leftRotate(NodePointer fulcrum);
        NodePointer rightRotate(NodePointer fulcrum);
        inline void updateParentLeftChild(NodePointer node);
        inline void updateParentRightChild(NodePointer node);
        inline void updateParentDoubleChilds(NodePointer node);
        NodePointer & reference(NodePointer node);
        NodePointer * pointerOfNodePointer(NodePointer node);
        NodePointer minimumChild(NodePointer root) const;
        NodePointer maximumChild(NodePointer root) const;
        void erase(NodePointer root);

        // help functions
        template <typename U> void swap(U & a, U & b);
        void swapExceptValue(NodePointer a, NodePointer b);

        Node * mRoot;

        friend struct Node;
        friend class Iterator;
    };


    template <typename T>
    RedBlackTree<T>::Node::Node(const T & value, ColorType color, Node * parent, Node * left, Node * right) :
        mColor(color), mParent(parent), mLeft(left), mRight(right), mTimes(1)
    {
        mValue = new T(value);
    }

    template <typename T>
    RedBlackTree<T>::Node::~Node() 
    {
        delete mValue;
    }

    template <typename T>
    void RedBlackTree<T>::updateParentLeftChild(NodePointer node)
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->mLeft != nullptr)
        {
            node->mLeft->mParent = node;
        }
    }

    template <typename T>
    void RedBlackTree<T>::updateParentRightChild(NodePointer node)
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->mRight != nullptr)
        {
            node->mRight->mParent = node;
        }
    }

    template <typename T>
    void RedBlackTree<T>::updateParentDoubleChilds(NodePointer node)
    {
        if (node == nullptr)
        {
            if (mRoot != nullptr)
            {
                mRoot->mParent = nullptr;
            }
        }
        else
        {
            updateParentLeftChild(node);
            updateParentRightChild(node);
        }
    }

    template <typename T>
    typename RedBlackTree<T>::Node::ColorType RedBlackTree<T>::color(NodePointer node) const
    {
        if (node == nullptr)
        {
            return Node::BLACK;
        }
        else
        {
            return node->mColor;
        }
    }

    template <typename T>
    inline void RedBlackTree<T>::print(NodePointer node)
    {
        // this function should be deleted
        return;
        if (node == nullptr)
        {
            return;
        }

        print(node->mLeft);
        print(node->mRight);
    }

    template<typename T>
    bool RedBlackTree<T>::test(Node * cur, Node * root)
    {
        if (cur == nullptr)
        {
            return true;
        }

        if (cur->mParent != root)
        {
            return false;
        }
        cur->mParent = root;

        test(cur->mLeft, cur);
        test(cur->mRight, cur);
        return true;
    }

    template<typename T>
    typename RedBlackTree<T>::Iterator RedBlackTree<T>::begin()
    {
        return Iterator(this, minimumChild(mRoot));
    }

    template<typename T>
    typename RedBlackTree<T>::Iterator RedBlackTree<T>::end()
    {
        return Iterator(this, nullptr);
    }

    template<typename T>
    typename RedBlackTree<T>::ConstantIterator RedBlackTree<T>::begin() const
    {
        return ConstantIterator(this, minimumChild(mRoot));
    }

    template<typename T>
    typename RedBlackTree<T>::ConstantIterator RedBlackTree<T>::end() const
    {
        return ConstantIterator(this, nullptr);
    }

    template<typename T>
    bool RedBlackTree<T>::isExist(const T & element) const
    {
        int ans = false;
        auto lf = [=](Node *node) {
            if (ans == true)
            {
                return;
            }

            if (node->value() == element)
            {
                ans = true;
                return;
            }
            
            lf(node->mLeft);
            lf(node->mRight);
        };
        lf(mRoot);
        return ans;
    }

    template <typename T>
    typename RedBlackTree<T>::NodePointer RedBlackTree<T>::insert(typename RedBlackTree<T>::NodePointer & node, const T & value)
    {
        if (node == nullptr)
        {
            mRoot = new Node(value, Node::BLACK, nullptr);
            return mRoot;
        }
        else
        {
            NodePointer cur = node;
            while (true)
            {
                if (value < cur->value())
                {
                    if (cur->mLeft == nullptr)
                    {
                        cur->mLeft = new Node(value, Node::RED, cur);
                        cur = cur->mLeft;
                        break;
                    }
                    else
                    {
                        cur = cur->mLeft;
                    }
                }
                else if (value > cur->value())
                {
                    if (cur->mRight == nullptr)
                    {
                        cur->mRight = new Node(value, Node::RED, cur);
                        cur = cur->mRight;
                        break;
                    }
                    else
                    {
                        cur = cur->mRight;
                    }
                }
                else // value == cur->value()
                {
                    cur->mTimes++;
                    return cur;
                }
            }

            insertFix(cur);
            return cur;
        }
    }

    template <typename T>
    void RedBlackTree<T>::insertFix(typename RedBlackTree<T>::NodePointer node)
    {
        Node *parent = node->mParent;
        Node *grand = nullptr;
        if (parent != nullptr)
        {
            grand = parent->mParent;
        }

        if (parent == nullptr) // situation 1
        {
            node->mColor = Node::BLACK;
            return; // finished
        }
        else if (color(parent) == Node::BLACK && parent != nullptr) // situation 2, "parent != nullptr" is not a must.
        {
            return; // finished
        }
        else if (color(parent) == Node::RED
            && color(uncle(node)) == Node::RED) // situation 3
        {
            // Solution: Change the tree nodes colors.
            parent->mColor = Node::BLACK;
            uncle(node)->mColor = Node::BLACK;
            grand->mColor = Node::RED;
            insertFix(grand); // do it again
        }
        else if (color(parent) == Node::RED
            && color(uncle(node)) == Node::BLACK
            && node == parent->mRight
            && parent == grand->mLeft) // situation 4
        {
            leftRotate(parent);
            insertFix(parent);
        }
        else if (color(parent) == Node::RED
            && color(uncle(node)) == Node::BLACK
            && node == parent->mLeft
            && parent == grand->mRight) // situation 4
        {
            rightRotate(parent);
            insertFix(parent);
        }
        else if (color(parent) == Node::RED
            && color(uncle(node)) == Node::BLACK 
            && node == parent->mLeft 
            && parent == grand->mLeft) // situation 5
        {
            parent->mColor = Node::BLACK;
            grand->mColor = Node::RED;
            rightRotate(grand);
            insertFix(grand);
        }
        else if (color(parent) == Node::RED
            && color(uncle(node)) == Node::BLACK
            && node == parent->mRight
            && parent == grand->mRight) // situatuin 5
        {
            parent->mColor = Node::BLACK;
            grand->mColor = Node::RED;
            leftRotate(grand);
            insertFix(grand);
        }
    }

    template <typename T>
    typename RedBlackTree<T>::NodePointer RedBlackTree<T>::sibling(typename RedBlackTree<T>::NodePointer node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        Node *parent = node->mParent;
        if (parent == nullptr)
        {
            return nullptr;
        }

        if (parent->mLeft == node)
        {
            return parent->mRight;
        }
        else
        {
            return parent->mLeft;
        }
    }

    template <typename T>
    typename RedBlackTree<T>::NodePointer RedBlackTree<T>::uncle(NodePointer node)
    {
        return sibling(node->mParent);
    }

    // Rotate Description: k1 is always on the left.
    //           k1                    k2 
    //          /  \                  /  \
    //         0    k2      -->      k1  1111   
    //             /  \             /  \     
    //            0  1111          0    0  
    //--------------------------------------------------------
    template <typename T>
    typename RedBlackTree<T>::NodePointer RedBlackTree<T>::leftRotate(NodePointer fulcrum)
    {
        Node *masterParent = fulcrum->mParent;
        NodePointer &k1 = reference(fulcrum);
        Node *k2 = k1->mRight; // k2 is must not nullptr

        k1->mRight = k2->mLeft;
        k2->mLeft = k1;

        updateParentDoubleChilds(k1);
        updateParentDoubleChilds(k2);        
        k1 = k2;
        updateParentDoubleChilds(masterParent);
        test(mRoot, nullptr);
        return k1;
    }

    // Rotate Description: 
    //           k2                    k1 
    //          /  \                  /  \
    //         k1   0      -->      1111 k2   
    //        /  \                      /  \
    //      1111  0                    0    0
    //--------------------------------------------------------
    template <typename T>
    typename RedBlackTree<T>::NodePointer RedBlackTree<T>::rightRotate(NodePointer fulcrum)
    {
        Node *masterParent = fulcrum->mParent;
        NodePointer k2 = fulcrum;
        NodePointer k1 = k2->mLeft;
        reference(k2) = k1;

        k2->mLeft = k1->mRight;
        k1->mRight = k2;

        updateParentDoubleChilds(k1);
        updateParentDoubleChilds(k2);
      //  k2 = k1;
        updateParentDoubleChilds(masterParent);
        test(mRoot, nullptr);
        return k2;
    }

    template <typename T>
    typename RedBlackTree<T>::NodePointer & RedBlackTree<T>::reference(NodePointer node)
    {
        if (node == nullptr)
        {
            return mRoot;
        }

        if (node->mParent == nullptr)
        {
            return mRoot;
        }
        else
        {
            Node *parent = node->mParent;
            if (node == parent->mLeft)
            {
                return parent->mLeft;
            }
            else
            {
                return parent->mRight;
            }
        }
    }

    template<typename T>
    typename RedBlackTree<T>::NodePointer * RedBlackTree<T>::pointerOfNodePointer(NodePointer node)
    {
        if (node == nullptr)
        {
            return false;
        }

        NodePointer parent = node->mParent;
        if (parent == nullptr)
        {
            return &mRoot;
        }
        else if (node == parent->mLeft)
        {
            return &parent->mLeft;
        }
        else
        {
            return &parent->mRight;
        }

        
    }

    template<typename T>
    typename RedBlackTree<T>::NodePointer RedBlackTree<T>::minimumChild(typename RedBlackTree<T>::NodePointer root) const
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        while (root->mLeft != nullptr)
        {
            root = root->mLeft;
        }

        return root;
    }

    template<typename T>
    typename RedBlackTree<T>::NodePointer RedBlackTree<T>::maximumChild(typename RedBlackTree<T>::NodePointer root) const
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        while (root->mRight != nullptr)
        {
            root = root->mRight;
        }

        return root;
    }

    template<typename T>
    void RedBlackTree<T>::erase(NodePointer root)
    {
        if (root == nullptr)
        {
            return;
        }

        erase(root->mLeft);
        erase(root->mRight);
        reference(root) = nullptr;
        delete root;
    }

    template<typename T>
    void RedBlackTree<T>::swapExceptValue(NodePointer a, NodePointer b)
    {
        // this function should be deleted
        swap(a->mColor, b->mColor);
        swap(a->mLeft, b->mLeft);
        swap(a->mRight, b->mRight);
    }

    template <typename T>
    bool RedBlackTree<T>::erase(const T & value)
    {
       // reference(mRoot->mLeft) = nullptr;
       /// return true;
        NodePointer cur = mRoot;
        while (true)
        {
            if (cur == nullptr)
            {
                return false; // value not exist
            }
            else if (value < cur->value())
            {
                cur = cur->mLeft;
            }
            else if (value > cur->value())
            {
                cur = cur->mRight;
            }
            else // value == cur->value
            {
                break;
            }
        }

        Node *erasePos = nullptr;
        if (cur->mLeft == nullptr && cur->mRight == nullptr)
        {
            erasePos = cur;
        }
        else if (cur->mRight != nullptr)
        {
            Node * rightMin = minimumChild(cur->mRight);
            swap(cur->mValue, rightMin->mValue);
           // erasePos = cur;
            // swap(cur->value(), rightMin->value());
            test(mRoot, nullptr);
            erasePos = rightMin;
        }
        else if (cur->mLeft != nullptr)
        {
            Node *leftMax = maximumChild(cur->mLeft);
            swap(cur->mValue, leftMax->mValue);
            //erasePos = cur;
            // swap(cur->value(), leftMax->value());
            test(mRoot, nullptr);
            erasePos =leftMax;
        }

        if (color(erasePos) == Node::RED)
        {
            reference(erasePos) = nullptr;
            delete erasePos;
        }
        else 
        {
            Node *oldNode = erasePos;

            eraseFix(oldNode);
            Node *parent = erasePos->mParent;
            
            Node *fixPos = erasePos->mLeft != nullptr ? erasePos->mLeft : erasePos->mRight;
            reference(erasePos) = fixPos;
            updateParentDoubleChilds(parent);
            delete erasePos;
        }

        return true;
    }

    template<typename T>
    void RedBlackTree<T>::eraseFix(NodePointer node)
    {
        Node *curSibling = sibling(node); // sibling is must not nullptr
        if (node == nullptr)
        {
            return;
        }
        else if (node == mRoot)
        {
            node->mColor = Node::BLACK;
            return;
        }
        else if (color(node) == Node::RED)
        {
            node->mColor = Node::BLACK;
            return;
        }
        else if (curSibling == nullptr)
        {
            eraseFix(node->mParent);
            return;
        }
        else
        {
            Node *curSibling = sibling(node); // sibling is must not nullptr
            Node *curParent = node->mParent;
            if (node == curParent->mLeft)
            {
                if (color(curSibling) == Node::RED)
                {
                    curSibling->mColor = Node::BLACK;
                    curParent->mColor = Node::RED;
                    leftRotate(curParent);
                    eraseFix(node);
                }
                else if (color(curSibling->mLeft) == Node::BLACK
                    && color(curSibling->mRight) == Node::BLACK)
                {
                    curSibling->mColor = Node::RED;
                    eraseFix(curParent);
                }
                else
                {
                    if (color(curSibling->mRight) == Node::BLACK)
                    {
                        swap(curSibling->mColor, curSibling->mLeft->mColor);
                        rightRotate(curSibling);
                    }

                    swap(node->mParent->mColor, node->mParent->mRight->mColor);
                    node->mParent->mRight->mRight->mColor = Node::BLACK;
                    leftRotate(node->mParent);
                    return;
                }
            }
            else // node == curParent->mRight
            {
                if (color(curSibling) == Node::RED)
                {
                    curSibling->mColor = Node::BLACK;
                    curParent->mColor = Node::RED;
                    rightRotate(curParent);
                    eraseFix(node);
                }
                else if (color(curSibling->mLeft) == Node::BLACK
                    && color(curSibling->mRight) == Node::BLACK)
                {
                    curSibling->mColor = Node::RED;
                    eraseFix(curParent);
                }
                else
                {
                    if (color(curSibling->mLeft) == Node::BLACK)
                    {
                        swap(curSibling->mColor, curSibling->mRight->mColor);
                        leftRotate(curSibling);
                    }

                    swap(node->mParent->mColor, node->mParent->mLeft->mColor);
                    rightRotate(node->mParent);
                    return;
                }
            }
        }
    }

    template <typename T>
    void RedBlackTree<T>::eraseLeftLackFix(NodePointer node)
    {
        for (int i = 0)
    }

    template<typename T>
    inline void RedBlackTree<T>::eraseRightLackFix(NodePointer node)
    {
    }


    template <typename T>
    template <typename U>
    void RedBlackTree<T>::swap(U & a, U & b)
    {
        test(mRoot, nullptr);
        U oldA = a;
        a = b;
        b = oldA;
    }

    template <typename T>
    RedBlackTree<T>::Iterator::Iterator(RedBlackTree<T> *tree, typename RedBlackTree<T>::Node *node) :
        ConstantIterator(tree, node)
    {
    }

    template <typename T>
    typename RedBlackTree<T>::Iterator &RedBlackTree<T>::Iterator::operator ++ ()
    {
        if (mNode == nullptr)
        {
            mNode = mTree->minimumChild(mTree->mRoot);
            return *this;
        }

        if (mNode->mRight != nullptr)
        {
            mNode = mNode->mRight;
            return *this;
        }
        else
        {
            Node *ans = mNode->mParent;
            while (ans != nullptr && ans->value() < mNode->value())
            {
                ans = ans->mParent;
            }

            mNode = ans;
            return *this;
        }

        return *this;
    }

    template <typename T>
    typename RedBlackTree<T>::Iterator &RedBlackTree<T>::Iterator::operator -- ()
    {
        if (mNode == nullptr)
        {
            mNode = mTree->maximumChild(mTree->mRoot);
            return *this;
        }

        if (mNode->mLeft != nullptr)
        {
            mNode = mNode->mLeft;
            return *this;
        }
        else
        {
            Node *ans = mNode->mParent;
            while (ans != nullptr && ans->value() > mNode->value())
            {
                ans = ans->mParent;
            }

            mNode = ans;
            return *this;
        }

        return *this;
    }

    template <typename T>
    typename RedBlackTree<T>::Iterator RedBlackTree<T>::Iterator::operator ++ (int) const
    {
        Iterator ans = *this;
        ++(*this);
        return ans;
    }

    template <typename T>
    typename RedBlackTree<T>::Iterator RedBlackTree<T>::Iterator::operator -- (int) const
    {
        Iterator ans = *this;
        --(*this);
        return ans;
    }


    template <typename T>
    RedBlackTree<T>::ConstantIterator::ConstantIterator(RedBlackTree<T> *tree, typename RedBlackTree<T>::Node *node) :
        mTree(tree), mNode(node)
    {
    }

    template <typename T>
    typename RedBlackTree<T>::ConstantIterator &RedBlackTree<T>::ConstantIterator::operator ++ ()
    {
        if (mNode == nullptr)
        {
            mNode = mTree->minimumChild(mTree->mRoot);
            return *this;
        }

        if (mNode->mRight != nullptr)
        {
            mNode = mNode->mRight;
            return *this;
        }
        else
        {
            Node *ans = mNode->mParent;
            while (ans != nullptr && ans->value() < mNode->value())
            {
                ans = ans->mParent;
            }

            mNode = ans;
            return *this;
        }

        return *this;
    }

    template <typename T>
    typename RedBlackTree<T>::ConstantIterator &RedBlackTree<T>::ConstantIterator::operator -- ()
    {
        if (mNode == nullptr)
        {
            mNode = mTree->maximumChild(mTree->mRoot);
            return *this;
        }

        if (mNode->mLeft != nullptr)
        {
            mNode = mNode->mLeft;
            return *this;
        }
        else
        {
            Node *ans = mNode->mParent;
            while (ans != nullptr && ans->value() > mNode->value())
            {
                ans = ans->mParent;
            }

            mNode = ans;
            return *this;
        }

        return *this;
    }

    template <typename T>
    typename RedBlackTree<T>::ConstantIterator RedBlackTree<T>::ConstantIterator::operator ++ (int) const
    {
        ConstantIterator ans = *this;
        ++(*this);
        return ans;
    }

    template <typename T>
    typename RedBlackTree<T>::ConstantIterator RedBlackTree<T>::ConstantIterator::operator -- (int) const
    {
        ConstantIterator ans = *this;
        --(*this);
        return ans;
    }

}

#endif // REDBLACKTREE_H