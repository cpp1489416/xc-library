#ifndef XCAUTOPOINTER_H
#define XCAUTOPOINTER_H

namespace XC
{
    template <typename T>
    class AutoPointer
    {
    public:
        explicit AutoPointer(T * pointer = nullptr) : mPointer(pointer) {}
        ~AutoPointer() { delete mPointer; }

        const T * Get() { return mPointer; }
        
        T * Get() { return mPointer; }
        void Reset(T * pointer = nullptr);
        void Release();

    private:
        T * mPointer;
    };

    template <typename T>
    inline void AutoPointer<T>::Reset(T * pointer)
    {
        Release();
        mPointer = pointer;
    }

    template <typename T>
    inline void AutoPointer<T>::Release()
    {
        delete mPointer;
        mPointer = nullptr;
    }
    
}

#endif // XCAUTOPOINTER_H
