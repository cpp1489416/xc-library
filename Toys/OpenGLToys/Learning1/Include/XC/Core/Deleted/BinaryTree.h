#ifndef BINARYTREE_H
#define BINARYTREE_H

namespace Xc
{
    template <typename T>
    class BinarySearchTree
    {
    public:
        struct Node
        {
            T value;
            
            Node *left;
            Node *right;
            int count;

            Node(T value, Node *left = nullptr, Node *right = nullptr);
        };

        typedef Node *NodePointer;

    public:
        BinarySearchTree();
        ~BinarySearchTree();
        BinarySearchTree(const BinarySearchTree &rhs);
        BinarySearchTree &operator =(const BinarySearchTree &rhs);
        int count(const T &value) const { return count(mRoot, value); }
        void insert(const T &value) { return insert(mRoot, value); }
        void erase(const T &value) { return erase(mRoot, value); }
        Node *root() const { return mRoot; }
        Node *findMin(Node *root) const;
        Node *findMax(Node *root) const;
        void print();
       

    private:
        void insert(Node * &root, const T &value); // help function
        void erase(Node * &root, const T &value); // help function
        T eraseMin(Node * &root, const T &value); // second delete
        void eraseMax(Node * &root, const T &value); // second erase
        int count(const Node *root, const T &value); // help function
        Node *clone(const Node *root) const;
        void erase(Node * &root);

        int mSize;
        Node *mRoot;
    };

    template <typename T>
    BinarySearchTree<T>::Node::Node(T value, Node *left, Node *right)
        : value(value), left(left), right(right), count(0)
    {
    }


    template <typename T>
    BinarySearchTree<T>::BinarySearchTree() :
        mRoot(nullptr), mSize(0)
    {
    }

    template<typename T>
    inline BinarySearchTree<T>::~BinarySearchTree()
    {
        erase(mRoot);
    }

    template<typename T>
    BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree & rhs)
    {
        mRoot = clone(rhs.root());
    }

    template<typename T>
    BinarySearchTree<T> &BinarySearchTree<T>::operator =(const BinarySearchTree & rhs)
    {
        erase(mRoot);
        mRoot = rhs.clone();
        return *this;
    }

    template<typename T>
    typename BinarySearchTree<T>::Node * BinarySearchTree<T>::findMin(Node * root) const
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
    typename BinarySearchTree<T>::Node * BinarySearchTree<T>::findMax(Node * root) const
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
    inline void BinarySearchTree<T>::print()
    {
        // this function should be deleted
    }
    
    template<typename T>
    void BinarySearchTree<T>::insert(Node * &root, const T & value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
        }

        if (value < root->value)
        {
            insert(root->left, value);
        }
        else if (value > root->value)
        {
            insert(root->right, value);
        }
        else
        {
            root->count++;
        }
    }

    template<typename T>
    void BinarySearchTree<T>::erase(Node * &root, const T & value)
    {
        if (root == nullptr)
        {
            return;
        }

        if (value < root->value)
        {
            erase(root->left, value);
        }
        else if (value > root->value)
        {
            erase(root->right, value);
        }
        else if (root->count > 1)
        {
            root->count--;
        }
        else if (root->left != nullptr && root->right != nullptr) // start delete
        {
            root->value = eraseMin(root->right, value);
        }
        else // have only one child, just delete it.
        {
            Node *oldNode = root;
            root = root->left != nullptr ? root->left : root->right;
            delete oldNode;
        }
    }

    template<typename T>
    inline void BinarySearchTree<T>::erase(Node * &root)
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
    T BinarySearchTree<T>::eraseMin(Node * &root, const T & value)
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
    inline void BinarySearchTree<T>::eraseMax(Node * &root, const T & value)
    {
    }

    template<typename T>
    int BinarySearchTree<T>::count(const Node * root, const T & value)
    {
        if (root == nullptr)
        {
            return 0;
        }

        if (value < root->value)
        {
            return count(root->left, value);
        }
        else
        {
            return count(root->right, value);
        }
        else
        {
            return root->count;
        }
    }

    template<typename T>
    typename BinarySearchTree<T>::Node * BinarySearchTree<T>::clone(const Node *root) const
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        return new Node(root->value, clone(root->left), clone(root->right));
    }

}

#endif // BINARYTREE_H
