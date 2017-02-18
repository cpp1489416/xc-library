#ifndef XAUTOPOINTER_H
#define XAUTOPOINTER_H

template <typename T>
class XAutoPointer
{
public:
    XAutoPointer(T * pointer = nullptr)
        : pointer(pointer)
    {
    }
    
    ~XAutoPointer()
    {
        release(); 
    }
    
    void reset(T * pointer)
    {
        release(); 
        this->pointer = pointer;
    }

    inline void release()
    { 
        delete pointer;
        pointer = nullptr; 
    }

    inline T *get() const 
    {
        return pointer; 
    }

    inline T *operator->() const 
    {
        return pointer; 
    }

    inline T &operator*() const
    {
        return *pointer; 
    }

    inline operator T *() const
    {
        return pointer; 
    }

    XAutoPointer<T> &operator=(const XAutoPointer<T> &rhs)
    {
        reset(rhs.get());
        return *this;
    }

private:
    T * pointer;
};

#endif