#ifndef AVLTREE_H
#define AVLTREE_H

#include "Stack.h"

namespace Xc
{
    template <typename T>
    class AVLTree
    {
    public:
        struct Node
        {
            T value;

            Node *left;
            Node *right;
            Node *father;
            int count;
            int height; // Height is updated dymatically.

            Node(T value, int height  = 0, Node *father = nullptr, Node *left = nullptr, Node *right = nullptr);
        };

        typedef Node *NodePointer;

        class ConstantIterator
        {
        public:

        protected:
            ConstantIterator(AVLTree<T> &tree, typename AVLTree<T>::Node *node) {}
            
            friend class AVLTree<T>;
        };

        class Iterator 
        {
        public:
            Iterator() {}
            Iterator &operator ++();
            Iterator &operator --();
            Iterator operator ++(int);
            Iterator operator --(int);
            Iterator operator +(int count) const;
            Iterator operator -(int count) const;
            inline bool operator ==(const Iterator &rhs) const { return mNode == rhs.mNode; }
            inline bool operator !=(const Iterator &rhs) const { return !(*this == rhs); }
            inline Iterator operator >(const Iterator &rhs) const { return mNode->value > rhs.mNode->value; }
            inline T operator *() { return mNode->value; }
            inline AVLTree *tree() { return mTree; }

        private:
            Iterator(AVLTree *tree, typename AVLTree<T>::Node *node);
            AVLTree<T> *mTree;
            typename AVLTree<T>::Node *mNode;

            
            friend class AVLTree<T>;
        };

    public:
        AVLTree();
        ~AVLTree();
        AVLTree(const AVLTree &rhs);
        AVLTree &operator =(const AVLTree &rhs);
        int count(const T &value) const { return count(mRoot, value); }
        Iterator insert(const T &value);
        void erase(const T &value) { erase(mRoot, value); }
        Iterator erase(const Iterator &rhs);
        inline bool empty() const { return mRoot == nullptr; }
        Node *root() const { return mRoot; }
        T &min();
        T &max();
        Iterator begin();
        Iterator end();
        inline int height() const { return height(mRoot); }

    private:
        Iterator insert(NodePointer &node, const T &value); // help function
        Iterator insertStack(NodePointer &node, const T &value); // using stark instead of 
        void erase(Node * &node, const T &value); // help function
        T eraseMin(Node * &root, const T &value); // second delete
        void eraseMax(Node * &root, const T &value); // second erase
        int count(const Node *root, const T &value); // help function
        Node *clone(const Node *root) const;
        void erase(Node * &root);
        inline int height(const Node *node) const { return node == nullptr ? -1 : node->height; }
        void rotateWithLeftChild(NodePointer &node);
        void rotateWithRightChild(NodePointer &node);
        void doubleWithLeftChild(NodePointer &node);
        void doubleWithRightChild(NodePointer &node);

        Node *findMin(Node *root) const;
        Node *findMax(Node *root) const;

        // help functions
        void updateLeftChildFather(Node *node);
        void updateRightChildFather(Node *node);
        void updateDoubleChildsFather(Node *node);
        inline int max(int a, int b) const { return a > b ? a : b; }
        inline int min(int a, int b) const { return a < b ? a : b; }

        int mSize;
        Node *mRoot;

        friend class Iterator;
    };

    template <typename T>
    AVLTree<T>::Node::Node(T value, int height, Node *father, Node *left, Node *right)
        : value(value), height(height), father(father), left(left), right(right), count(1)
    {
    }

    template <typename T>
    AVLTree<T>::AVLTree() :
        mRoot(nullptr), mSize(0)
    {
    }

    template<typename T>
    inline AVLTree<T>::~AVLTree()
    {
        erase(mRoot);
    }

    template<typename T>
    AVLTree<T>::AVLTree(const AVLTree & rhs)
    {
        mRoot = clone(rhs.root());
    }

    template<typename T>
    AVLTree<T> &AVLTree<T>::operator =(const AVLTree & rhs)
    {
        erase(mRoot);
        mRoot = rhs.clone();
        return *this;
    }

    template<typename T>
    typename AVLTree<T>::Iterator AVLTree<T>::insert(const T & value)
    {
        Iterator ans = insertStack(mRoot, value);
        if (mRoot != nullptr)
        {
            mRoot->father = nullptr;
        }

        return ans;
    }

    template<typename T>
    typename AVLTree<T>::Iterator AVLTree<T>::erase(const Iterator & rhs)
    {
        Iterator ans = rhs + 1;
        Node *father = rhs.mNode->father;
        if (father == nullptr)
        {
            erase(mRoot, rhs.mNode->value);
            mRoot->father = nullptr;
        }
        else
        {
            NodePointer &node = father->left == rhs.mNode ? father->left : father->right;
            erase(node, rhs.mNode->value);
            updateDoubleChildsFather(father);
        }

        return ans;
    }

    template<typename T>
    typename AVLTree<T>::Iterator AVLTree<T>::insert(typename AVLTree<T>::NodePointer & node, const T & value)
    {
        Iterator ans;
        if (node == nullptr)
        {
            node = new Node(value);
            ans = Iterator(this, node);
        }
        else if (value < node->value)
        {
            ans = insert(node->left, value);
            if (height(node->left) - height(node->right) >= 2) // Start rotation because rotation starts from bottom.
            {
                if (value < node->left->value) // on the very left
                {
                    rotateWithLeftChild(node);
                }
                else
                {
                    doubleWithLeftChild(node);
                }
            }

            updateLeftChildFather(node);
            // node->left->father = node;
        }
        else if (value > node->value)
        {
            ans = insert(node->right, value);
            if (height(node->right) - height(node->left) >= 2)
            {
                if (value > node->right->value)
                {
                    rotateWithRightChild(node);
                }
                else
                {
                    rotateWithRightChild(node);
                }
            }

            updateRightChildFather(node);
        }
        else // value == node->value
        {
            node->count++; // like set;

        }

        node->height = max(height(node->left), height(node->right)) + 1; // update height from bottom to top
    
        return Iterator(this, node);                                  // mRoot->father = nullptr;
    }

    template<typename T>
    typename AVLTree<T>::Iterator AVLTree<T>::insertStack(typename AVLTree<T>::NodePointer & node, const T & value)
    {
        Stack<NodePointer> stack;
        stack.push(node);

        while (true)
        {
            NodePointer &curNode = stack.top();
            
            if (curNode == nullptr)
            {
                curNode = new Node(value);
                break;
            }

            if (value < curNode->value)
            {
                stack.push(curNode->left);
            }
            else if (value > curNode->value)
            {
                stack.push(curNode->right);
            }
            else // same value, just count++
            {
                curNode->count++;
                return Iterator(this, node);
            }
        }

        while (true)
        {
            NodePointer child = stack.top();
            stack.pop();
            if (stack.isEmpty())
            {
                mRoot = child;
                break;
            }

            NodePointer father = stack.top();
            stack.pop();

            child->father = father; // useful???
            if (value < father->value)
            {
                father->left = child;
                if (height(father->left) - height(father->right) >= 2)
                {
                    if (value < father->left->value)
                    {
                        rotateWithLeftChild(father);
                    }
                    else
                    {
                        doubleWithLeftChild(father);
                    }
                }
       
                updateLeftChildFather(father); // must update
                stack.push(father); // must push
            }
            else if (value > father->value)
            {
                father->right = child;

                if (height(father->right) - height(father->left) >= 2)
                {
                    if (value > father->right->value)
                    {
                        rotateWithRightChild(father);
                    }
                    else
                    {
                        doubleWithRightChild(father);
                    }
                }

                updateRightChildFather(father);
                stack.push(father);
            }
            else // impossible
            {
            }

            father->height = max(height(father->left), height(father->right)) + 1;
        }

        return Iterator(this, node);
    }

    // Rotate Description: 
    //           k2                    k1 
    //          /  \                  /  \
    //         k1   0      -->      1111 k2   
    //        /  \                      /  \
    //      1111  0                    0    0
    //--------------------------------------------------------
    template<typename T>
    inline void AVLTree<T>::rotateWithLeftChild(NodePointer & node)
    {
        NodePointer &k2 = node;
        Node *k1 = k2->left;
        if (k1 == nullptr)
        {
            return; // This is a big bug.
        }

        k2->left = k1->right;
        k1->right = k2;
        
        k2->height = max(height(k2->left), height(k2->right)) + 1; // height update here!!! From bottom to top.
        k1->height = max(height(k1->left), height(k1->right)) + 1; // height update here!!!

        // update fathers
        updateLeftChildFather(k2);
        updateRightChildFather(k1);
        // k2->left->father = k2;
        // k1->right->father = k1;

        k2 = k1;
    }

    // Rotate Description: k1 is always on the left.
    //           k1                    k2 
    //          /  \                  /  \
    //         0    k2      -->      k1  1111   
    //             /  \             /  \     
    //            0  1111          0    0  
    //--------------------------------------------------------
    template<typename T>
    void AVLTree<T>::rotateWithRightChild(NodePointer & node)
    {
        NodePointer &k1 = node;
        Node *k2 = k1->right;
        if (k2 == nullptr)
        {
            return;
        }

        k1->right = k2->left;
        k2->left = k1;

        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->left), height(k2->right)) + 1;

        // update fathers
        updateRightChildFather(k1);
        updateLeftChildFather(k2);
        // k1->right->father = k1;
        // k2->left->father = k2;

        k1 = k2;
    }

    // Rotate Description:
    //           k3                    k3                        k2
    //          /  \                  /  \                      /  \
    //         /    \                /    \                    /    \
    //        k1     D      -->     k2     D      -->         k1     k3
    //       / \                   / \                       / \    /  \ 
    //      A   k2                k1  C                     A   B  C    D 
    //         /  \              /
    //        B    C            A
    //--------------------------------------------------------
    template<typename T>
    void AVLTree<T>::doubleWithLeftChild(NodePointer & node)
    {
        NodePointer &k3 = node;
        NodePointer &k1 = k3->left;
        NodePointer &k2 = k1->right; // unused

        rotateWithRightChild(k1);
        rotateWithLeftChild(k3);

        // update fathers
        updateDoubleChildsFather(k1);
        updateDoubleChildsFather(k2);
        updateDoubleChildsFather(k3);
        // rubbish:
        //k1->left->father = k1; // unuseful
        //k1->right->father = k1;
        //k2->left->father = k1;
        //k2->right->father = k2;
        //k3->left->father = k3;
        //k3->right->father = k3;  // unuseful
    }

    // Rotate Description:
    //           k1                    k1                        k2
    //          /  \                  /  \                      /  \
    //         /    \                /    \                    /    \
    //        A      k3      -->    A      k2      -->        k1     k3
    //              /  \                  /  \               / \    /  \ 
    //             k2   D                B    k3            A   B  C    D 
    //            /  \                       /  \
    //           B    C                     C    D
    //--------------------------------------------------------
    template<typename T>
    void AVLTree<T>::doubleWithRightChild(NodePointer & node)
    {
        NodePointer &k1 = node;
        NodePointer &k3 = k1->right;
        NodePointer &k2 = k3->left; // unused

        rotateWithLeftChild(k3);
        rotateWithRightChild(k1);

        // update fathers
        updateDoubleChildsFather(k1);
        updateDoubleChildsFather(k2);
        updateDoubleChildsFather(k3);
    }

    template<typename T>
    T & AVLTree<T>::min()
    {
        Node *node = mRoot;    
        while (node->left != nullptr)
        {
            node = node->left;
        }

        return node->value;
    }

    template<typename T>
    T & AVLTree<T>::max()
    {
        Node *node = mRoot;
        while (node->right != nullptr)
        {
            node = node->right;
        }

        return node->value;
    }

    template<typename T>
    typename AVLTree<T>::Iterator AVLTree<T>::begin()
    {
        return Iterator(this, findMin(mRoot));
    }

    template<typename T>
    typename AVLTree<T>::Iterator AVLTree<T>::end()
    {
        Iterator ans(this, nullptr);
        return ans;
    }

    template<typename T>
    void AVLTree<T>::erase(Node * &node, const T & value)
    {
        if (node == nullptr)
        {
            return;
        }

        if (value < node->value)
        {
            erase(node->left, value);
        }
        else if (value > node->value)
        {
            erase(node->right, value);
        }
        else if (node->count > 1)
        {
            node->count--;
        }
        else if (node->left != nullptr && node->right != nullptr) // start delete
        {
            node->value = eraseMin(node->right, value);
        }
        else // just one, delete
        {
            Node *oldNode = node;
            node = node->left != nullptr ? node->left : node->right;
            if (node != nullptr)
            {
                node->father = oldNode->father; // update father
            }

            delete oldNode;
        }
    }

    template<typename T>
    inline void AVLTree<T>::erase(Node * &root)
    {
        if (root == nullptr)
        {
            return;
        }

        erase(root->left);
        delete root->left;
        erase(root->right);
        delete root->right;
        root = nullptr;
    }

    template<typename T>
    T AVLTree<T>::eraseMin(Node * &root, const T & value)
    {
        if (root->left != nullptr)
        {
            return eraseMin(root->left, value);
        }
        else
        {
            T ans = root->value;
            Node *oldNode = root;
            root = root->right;
            delete oldNode;
            return ans;
        }
    }

    template<typename T>
    inline void AVLTree<T>::eraseMax(Node * &root, const T & value)
    {
        if (root->right != nullptr)
        {
            return eraseMin(root->right, value);
        }
        else
        {
            T ans = root->value;
            Node *oldNode = root;
            root = root->left;
            delete oldNode;
            return ans;
        }
    }

    template<typename T>
    int AVLTree<T>::count(const Node * root, const T & value)
    {
        if (root == nullptr)
        {
            return 0;
        }

        if (value < root->value)
        {
            return count(root->left, value);
        }
        else if (value > root->value)
        {
            return count(root->right, value);
        }
        else
        {
            return root->count;
        }
    }

    template<typename T>
    typename AVLTree<T>::Node * AVLTree<T>::clone(const Node *root) const
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        return new Node(root->value, clone(root->left), clone(root->right));
    }


    template<typename T>
    typename AVLTree<T>::Node * AVLTree<T>::findMin(Node * root) const
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        while (root->left != nullptr)
        {
            root = root->left;
        }

        return root;
    }

    template<typename T>
    typename AVLTree<T>::Node *AVLTree<T>::findMax(Node * root) const
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        while (root->right != nullptr)
        {
            root = root->right;
        }

        return root;
    }

    template<typename T>
    inline void AVLTree<T>::updateLeftChildFather(Node * node)
    {
        if (node != nullptr && node->left != nullptr)
        {
            node->left->father = node;
        }
    }

    template<typename T>
    inline void AVLTree<T>::updateRightChildFather(Node * node)
    {
        if (node != nullptr && node->right != nullptr)
        {
            node->right->father = node;
        }
    }

    template<typename T>
    inline void AVLTree<T>::updateDoubleChildsFather(Node * node)
    {
        updateLeftChildFather(node);
        updateRightChildFather(node);
    }

    template <typename T>
    AVLTree<T>::Iterator::Iterator(AVLTree<T> *tree, typename AVLTree<T>::Node * node) :
        mTree(tree), mNode(node)
    {
    }

    template <typename T>
    typename AVLTree<T>::Iterator &AVLTree<T>::Iterator::operator ++()
    {
        if (mNode == nullptr)
        {
            mNode = mTree->findMin(mTree->mRoot);
            return *this;
        }

        if (mNode->right != nullptr)
        {
            Node *node = mNode->right;
            while (node->left != nullptr)
            {
                node = node->left;
            }

            mNode = node;
            return *this;
        }
        else
        {
            Node *father = mNode->father;
            while (father != nullptr && father->value < mNode->value)
            {
                father = father->father;
            }

            mNode = father;
            return *this;
        }

        return *this;
    }

    template <typename T>
    typename AVLTree<T>::Iterator &AVLTree<T>::Iterator::operator --()
    {
        if (mNode == nullptr)
        {
            mNode = mTree->findMax(mTree->mRoot);
            return *this;
        }

        if (mNode->left != nullptr)
        {
            Node *node = mNode->left;
            while (node->right != nullptr)
            {
                node = node->right;
            }

            mNode = node;
            return *this;
        }
        else
        {
            Node *father = mNode->father;
            while (father != nullptr && father->value > mNode->value)
            {
                father = father->father;
            }

            mNode = father;
            return *this;
        }
    }

    template <typename T>
    typename AVLTree<T>::Iterator AVLTree<T>::Iterator::operator ++(int)
    {
        Iterator ans = *this;
        ++(*this);
        return ans;
    }

    template <typename T>
    typename AVLTree<T>::Iterator AVLTree<T>::Iterator::operator --(int) 
    {
        Iterator ans = *this;
        --(*this);
        return ans;
    }

    template <typename T>
    typename AVLTree<T>::Iterator AVLTree<T>::Iterator::operator +(int count) const
    {
        Iterator ans = *this;
        while (count--)
        {
            ++ans;
        }

        return ans;
    }

    template <typename T>
    typename AVLTree<T>::Iterator AVLTree<T>::Iterator::operator -(int count) const
    {
        Iterator ans = *this;
        while (count--)
        {
            --ans;
        }

        return ans;
    }
}

#endif // AVLTREE_H
