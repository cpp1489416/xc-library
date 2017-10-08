#ifndef STACK_H
#define STACK_H

#include "List.h"

namespace Xc
{
    // Interface
    template <typename T>
    class AbstractStack
    {
    public:
        virtual const T &top() const = 0;
        virtual T &top() = 0;
        virtual void pop() = 0;
        virtual void push(const T &value) = 0;
        virtual bool isEmpty() const = 0;
    };

    template <typename T>
    class ListStack : public AbstractStack<T>
    {
    public:
        virtual const T &top() const final { return *--mList.end(); }
        virtual T &top() final { return *--mList.end(); }
        virtual void pop() final { mList.popBack(); }
        virtual void push(const T &value) final { mList.pushBack(value); }
        virtual bool isEmpty() const final { return mList.isEmpty(); }

    private:
        List<T> mList;
    };

    // Equals typedef, but templates do not support typedef.
    template <typename T> class Stack : public ListStack<T> {}; 

    template <typename T> 
    class VertorStack : public AbstractStack<T>
    {
    public:

    };
}

#endif // STACK_H