#ifndef XCAUTOPOINTER_H
#define XCAUTOPOINTER_H

namespace XC
{
    template <typename T>
    class UniquePointer
    {
    public:
        explicit UniquePointer(T * pointer = nullptr) : mPointer(pointer) {}
        ~UniquePointer() { delete mPointer; }

        const T * Get() { return mPointer; }
        
        T * Get() { return mPointer; }
        void Reset(T * pointer = nullptr);
        void Release(); 

    private:
        T * mPointer;
    };

    template <typename T>
    inline void UniquePointer<T>::Reset(T * pointer)
    {
        Release();
        mPointer = pointer;
    }

    template <typename T>
    inline void UniquePointer<T>::Release()
    {
        delete mPointer;
        mPointer = nullptr;
    }
    
}

#endif // XCAUTOPOINTER_H
