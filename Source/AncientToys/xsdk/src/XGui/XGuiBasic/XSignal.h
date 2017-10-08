#ifndef XSIGNAL_H
#define XSIGNAL_H
#include "XAutoPointer.h"

// begin namespace
class XAbstractSlot;

template <typename T>
class XClassSlot;

class XStaticSlot;

class XSignal;
// end namespace

class XAbstractSlot
{
public:
    virtual void execute() = 0;
};

template <typename T>
class XClassSlot : public XAbstractSlot
{
public:
    XClassSlot(T * object, void (T::*function)())
        : object(object), function(function)
    {
    }

    virtual void execute()
    {
        (object->*function)();
    }

private:
    T *object;
    void (T::*function)();
};

class XStaticSlot
    : public XAbstractSlot
{
public:
    inline XStaticSlot(void(*function)())
        : function(function)
    {
    }

    virtual void execute()
    {
        (*function)();
    }

private:
    void(*function)();
};

class XSignal
{
public:
    XSignal()
    {
    }

    ~XSignal()
    {
    }

    template <typename T>
    inline void connect(T *object, void (T::*function)())
    {
        slot.reset(new XClassSlot<T>(object, function));
    }

    inline void connect(void(*function)())
    {
        slot.reset(new XStaticSlot(function));
    }

    void emit()
    {
        if (slot.get() != nullptr)
        {
            slot->execute();
        }
    }

    inline void disconnect()
    {
        slot.release();
    }

private:
    XSignal(XSignal &);
    
    XSignal &operator=(const XSignal &)
    {
        return XSignal();
    }
 
    XAutoPointer<XAbstractSlot> slot;
};

#endif