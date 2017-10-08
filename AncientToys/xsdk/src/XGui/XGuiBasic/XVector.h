#ifndef XVECTOR_H
#define XVECTOR_H

template <typename T>
class XVector
{
public:
    typedef typename T value_type;
    typedef typename T *iterator;
    typedef typename T *const_iterator;

    XVector()
    {
        m_capacity = 1;
        m_begin = new T[m_capacity];
        m_end = m_tail = m_begin;
    }

    inline XVector(const XVector<T> &rhs) { copyContrust(rhs); }

    ~XVector()
    {
        release();
    }

    inline int capacity() { return m_capacity; }

    inline iterator begin() const { return m_begin; }
    
    inline iterator end() const { return m_end; }
    
    inline int size() const { return m_end - m_begin; }

    inline bool empty() const { return size() == 0; }

    void push_back(const T & value)
    {
        if (size() + 1 > capacity())
        {
            addHalfCapacity();
        }

        *m_end = value;
        m_end++;
    }

    void pop_back(const T & value)
    {
        if (m_end == m_begin)
        {
            return;
        }

        m_end--;
    }

    void reserve(int size)
    {
        if (size > m_capicity)
        {
            m_capicity = size;
            secondAllocate();
        }
    }

    inline T &operator[](int index) { return m_begin[index]; }

    inline T &at(int index) 
    { return index >= size() ? m_begin[0] : m_begin[index]; }
    

    XVector<T> &operator=(const XVector<T> &rhs)
    {
        release();
        copyContrust(rhs);
        return *this;
    }

    iterator insert(const_iterator location, int count, const T &value)
    {
        int index = location - m_begin;
        int nextSize = size() + count;
        while (m_capacity < nextSize)
        {
            addHalfCapacity();
        }
        const_iterator tmpLocation = &m_begin[index];

        for (iterator itr = m_end - 1; itr != tmpLocation; itr--)
        {
            *(itr + count) = *itr;
        }
        *(tmpLocation + count) = *tmpLocation;

        for (iterator itr = tmpLocation; itr != tmpLocation + count; itr++)
        {
            *itr = value;
        }

        m_end += count;
        
        return tmpLocation;
    }

    inline iterator insert(const_iterator location, const T &value)
    { return insert(location, 1, value); }
    

private:
    void addHalfCapacity()
    {
        m_capacity += m_capacity;
        secondAllocate();
    }

    void secondAllocate()
    {
        T *newBegin = new T[m_capacity];
        T *newEnd = newBegin + size();
        T *newTail = newBegin + m_capacity;
        for (int i = 0; i < size(); i++)
        {
            newBegin[i] = m_begin[i];
        }

        delete[] m_begin;
        m_begin = newBegin;
        m_end = newEnd;
        m_tail = newTail;
    }

    void release()
    {
        delete m_begin;
        m_begin = m_end = m_tail = nullptr;
    }

    void copyContrust(const XVector<T> &rhs)
    {
        m_capacity = rhs.m_capacity;
        m_begin = new T[rhs.m_capacity];
        m_end = m_begin + rhs.size();
        m_tail = m_begin + m_capacity;
        for (int i = 0; i < rhs.size(); i++)
        {
            m_begin[i] = rhs.m_begin[i];
        }
    }

    T * m_begin;
    T * m_end;
    T * m_tail;
    int m_capacity;
};

#endif;
