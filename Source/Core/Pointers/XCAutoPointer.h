
#ifndef XCAUTOPOINTER_H
#define XCAUTOPOINTER_H

namespace XC
{
    template <typename T>
    class AutoPointer
    {
    public:
	explicit AutoPointer(T * pointer = nullptr) mPointer(pointer) {}
	~AutoPointer();
	void Reset(T * pointer = nullptr);
	T * Get() { return mPointer; }
	const T * Get() { return mPointer; }
	void Release();

    private:
	T * mPointer;
    };

    template <typename T>
    inline AutoPointer<T>::~AutoPointer()
    {
	Release();
    }

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