//#include "..\Containers\XCList.h"
//#ifndef LIST_H
//#define LIST_H
//
//namespace Xc
//{
//    template <typename T>
//    class List
//    {
//    private:
//        struct Node
//        {
//            Node(T *value, Node *next = nullptr, Node *previous = nullptr);
//            virtual ~Node();
//            T *value;
//            Node *previous;
//            Node *next;
//        };
//
//    public:
//        class ConstantIterator
//        {
//        public:
//            inline ConstantIterator() {}
//            ConstantIterator &operator ++();
//            ConstantIterator &operator --();
//            bool operator ==(const ConstantIterator &rhs) const;
//            bool operator !=(const ConstantIterator &rhs) const;
//            bool operator <(const ConstantIterator &rhs) const; // bug
//            bool operator >(const ConstantIterator &rhs) const; // bug
//            ConstantIterator operator ++(int);
//            ConstantIterator operator --(int);
//            inline const T &operator *() const { return *mNode->value; }
//            inline int index() const { return mIndex; }
//            inline bool isValid() const { return mNode != nullptr; }
//            ConstantIterator operator +(int count);
//            ConstantIterator operator -(int count);
//
//        protected:
//            ConstantIterator(Node *node = nullptr, int index = -1);
//
//            Node *mNode;
//            int mIndex;
//
//            friend class List<T>;
//        };
//
//        class Iterator : public ConstantIterator
//        {
//        public:
//            inline Iterator() {}
//            Iterator &operator ++();
//            Iterator &operator --();
//            Iterator operator ++(int);
//            Iterator operator --(int);
//            inline T &operator *() { return *mNode->value; }
//            Iterator operator +(int count);
//            Iterator operator -(int count);
//
//        private:
//            Iterator(Node *node = nullptr, int index = -1) : ConstantIterator(node, index) {}
//
//            friend class List<T>;
//        };
//
//    public:
//        List();       
//        ~List();
//        List(const List &rhs);
//        List operator =(const List &rhs);
//        inline ConstantIterator begin() const { return ConstantIterator(mFirst->next, 1); }
//        inline ConstantIterator end() const { return ConstantIterator(mLast, mSize + 1); }
//        inline ConstantIterator reserveBegin() const { return ConstantIterator(mLast->previous, mSize); }
//        inline ConstantIterator reserveEnd() const { return ConstantIterator(mFirst, 0); }
//        inline bool isEmpty() const { return size() == 0; }
//        inline int size() const { return mSize; }
//        inline const T &front() const { return *begin(); }
//        inline const T &back() const { return *--end(); }
//        ConstantIterator iteratorAt(int index) const;
//        inline const T &at(int index) const { return *iteratorAt(index); }
//
//        inline Iterator begin() { return Iterator(mFirst->next, 1); }
//        inline Iterator end() { return Iterator(mLast, mSize + 1); }
//        inline Iterator reserveBegin() { return Iterator(mLast->previous, mSize); }
//        inline Iterator reserveEnd() { return Iterator(mFirst, 0); }
//        inline void pushBack(const T &value) { insert(end(), value); }
//        inline void pushFront(const T &value) { insert(begin(), value); }
//        inline void popBack() { erase(--end()); }
//        inline void popFront() { erase(begin()); }
//        inline T &front() { return *begin(); }
//        inline T &back() { return *--end(); }
//        ConstantIterator insert(const ConstantIterator &after, const T &value);
//        ConstantIterator erase(const ConstantIterator &location);
//        ConstantIterator erase(const ConstantIterator &from, const ConstantIterator &to);
//        void clear();
//        Iterator iteratorAt(int index);
//        inline T &at(int index) { return *iteratorAt(index); }
//    
//    private:
//        Node *mFirst; // first is kept because there may be 0 elements
//        Node *mLast;  // also
//        int mSize;
//    };
//
//    // Node functions
//    template <typename T>
//    List<T>::Node::Node(T *value, Node *next, Node *previous)
//        : value(value), next(next), previous(previous)
//    {
//    }
//
//
//    // ConstantIterator functions
//    template <typename T>
//    typename List<T>::ConstantIterator &List<T>::ConstantIterator::operator ++()
//    {
//        if (mNode->next == nullptr)
//        {
//            // std::cout << "too young too simple" << std::endl;
//            return *this;
//        }
//
//        mNode = mNode->next;
//        mIndex++;
//        return *this;
//    }
//
//    template <typename T>
//    typename List<T>::ConstantIterator &List<T>::ConstantIterator::operator --()
//    {
//        if (mNode->previous == nullptr)
//        {
//            // std::cout << "too young too simple" << std::endl;
//            return *this;
//        }
//
//        mNode = mNode->previous;
//        mIndex--;
//        return *this;
//    }
//
//    template <typename T>
//    bool List<T>::ConstantIterator::operator ==(const ConstantIterator &rhs) const
//    {
//        return mNode == rhs.mNode;
//    }
//
//    template <typename T>
//    bool List<T>::ConstantIterator::operator !=(const ConstantIterator &rhs) const
//    {
//        return mNode != rhs.mNode;
//    }
//
//    template <typename T>
//    inline bool List<T>::ConstantIterator::operator<(const ConstantIterator & rhs) const
//    {
//        return mIndex < rhs.mIndex;
//    }
//
//    template <typename T>
//    inline bool List<T>::ConstantIterator::operator>(const ConstantIterator & rhs) const
//    {
//        return mIndex > rhs.mIndex;
//    }
//
//    template <typename T>
//    typename List<T>::ConstantIterator List<T>::ConstantIterator::operator++(int)
//    {
//        ConstantIterator itr = *this;
//        ++(*this);
//        return itr;
//    }
//
//    template <typename T>
//    typename List<T>::ConstantIterator List<T>::ConstantIterator::operator--(int)
//    {
//        ConstantIterator itr = *this;
//        --(*this);
//        return itr;
//    }
//
//    template <typename T>
//    typename List<T>::ConstantIterator List<T>::ConstantIterator::operator+(int count)
//    {
//        ConstantIterator ans = *this;
//        while (count--)
//        {
//            ++ans;
//        }
//
//        return ans;
//    }
//
//    template <typename T>
//    typename List<T>::ConstantIterator List<T>::ConstantIterator::operator-(int count)
//    {
//        ConstantIterator ans = *this;
//        while (count--)
//        {
//            --ans;
//        }
//
//        return ans;
//    }
//
//    template <typename T>
//    List<T>::ConstantIterator::ConstantIterator(Node *node, int index)
//    {
//        mNode = node;
//        mIndex = index;
//    }
//
//    template <typename T>
//    typename List<T>::Iterator & List<T>::Iterator::operator++()
//    {
//        if (mNode->next == nullptr)
//        {
//            // std::cout << "not const" << std::endl;
//            return *this;
//        }
//
//        mNode = mNode->next;
//        mIndex++;
//        return *this;
//    }
//
//    // Iterator functions
//    template <typename T>
//    typename List<T>::Iterator & List<T>::Iterator::operator--()
//    {
//        if (mNode->previous == nullptr)
//        {
//            // std::cout << "node const" << ::endl;
//            return *this;
//        }
//
//        mNode = mNode->previous;
//        mIndex--;
//        return *this;
//    }
//
//    template <typename T>
//    typename List<T>::Iterator List<T>::Iterator::operator++(int)
//    {
//        Iterator ans = *this;
//        ++(*this);
//        return ans;
//    }
//
//    template <typename T>
//    typename List<T>::Iterator List<T>::Iterator::operator--(int)
//    {
//        Iterator ans = *this;
//        --(*this);
//        return ans;
//    }
//
//    template <typename T>
//    typename List<T>::Iterator List<T>::Iterator::operator+(int count)
//    {
//        Iterator ans = *this;
//        while (count--)
//        {
//            ++ans;
//        }
//
//        return ans;
//    }
//
//    template <typename T>
//    typename List<T>::Iterator List<T>::Iterator::operator-(int count)
//    {
//        Iterator ans = *this;
//        while (count--)
//        {
//            --ans;
//        }
//
//        return ans;
//    }
//
//    // List functions
//    template <typename T>
//    List<T>::List() :
//        mSize(0)
//    {
//        mFirst = new Node(nullptr, nullptr, nullptr);
//        mLast = new Node(nullptr, nullptr, nullptr);
//        mFirst->next = mLast;
//        mLast->previous = mFirst;
//    }
//
//    template <typename T>
//    List<T>::~List()
//    {
//        clear();
//        delete mFirst;
//        delete mLast;
//    }
//
//    template<typename T, typename TAllocator>
//    inline Iterator XC::List<T, TAllocator>::Insert(Iterator position, const T & value)
//    {
//	return Iterator();
//    }
//
//    template<typename T>
//    List<T>::List(const List & rhs) :
//        mSize(0)
//    {
//        mFirst = new Node(nullptr, nullptr, nullptr);
//        mLast = new Node(nullptr, nullptr, nullptr);
//        mFirst->next = mLast;
//        mLast->previous = mFirst;
//
//        for (auto itr = rhs.begin(); itr != rhs.end(); ++itr)
//        {
//            pushBack(*itr);
//        }
//
//    }
//
//    template<typename T>
//    typename List<T> List<T>::operator=(const List & rhs)
//    {
//        List ans;
//        for (auto itr = rhs.begin(); itr != rhs.end(); ++itr)
//        {
//            ans.pushBack(*itr);
//        }
//
//        return ans;
//    }
//
//    template <typename T>
//    typename List<T>::ConstantIterator List<T>::insert(typename const List<T>::ConstantIterator &after, const T &value)
//    {
//        Node *left = after.mNode->previous;
//        Node *right = after.mNode;
//        Node *node = new Node(new T(value), right, left);
//        left->next = node;
//        right->previous = node;
//        mSize++;
//
//        return ConstantIterator(node, after.mIndex);
//    }
//
//    template <typename T>
//    typename List<T>::ConstantIterator List<T>::erase(typename const ConstantIterator &location)
//    {
//        if (size() == 0)
//        {
//            return location;
//        }
//
//        Node *node = location.mNode;
//        Node *left = location.mNode->previous;
//        Node *right = location.mNode->next;
//        left->next = right;
//        right->previous = left;
//        delete node;
//        mSize--;
//
//        return ConstantIterator(right, location.mIndex);
//    }
//
//    template <typename T>
//    typename List<T>::ConstantIterator List<T>::erase(typename const ConstantIterator & from, typename const ConstantIterator & to)
//    {
//        int count = 0;
//        for (auto itr = from; itr != to; ++itr)
//        {
//            count++;
//            erase(itr);
//        }
//
//        return ConstantIterator(to.mNode, to.mIndex - count);
//    }
//
//    template <typename T>
//    void List<T>::clear()
//    {
//        for (ConstantIterator itr = begin(); itr != end(); )
//        {
//            itr = erase(itr);
//        }
//    }
//
//    template <typename T>
//    typename List<T>::ConstantIterator List<T>::iteratorAt(int index) const
//    {
//        ConstantIterator itr = begin();
//        for (int i = 0; i < index; i++)
//        {
//            ++itr;
//        }
//
//        return itr;
//    }
//
//    template<typename T>
//    typename List<T>::Iterator List<T>::iteratorAt(int index)
//    {
//        Iterator itr = begin();
//        for (int i = 0; i < index; i++)
//        {
//            ++itr;
//        }
//
//        return itr;
//    }
//
//} // namespace Xc
//
//#endif // LIST_H
