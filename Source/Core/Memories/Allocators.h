#ifndef XCALLOCATORS_H
#define XCALLOCATORS_H

#include <new>
#include "../Types/Types.h"
#include "Construts.h"

namespace XC
{
    template <typename T> class StandardAllocator;
    template <typename T, typename Allocator> class InsideAllocator;
    template <typename T> class DefaultAllocator : public StandardAllocator<T> {};

    template <typename T>
    class StandardAllocator
    {
    public:
        static T * Allocate(xsize count) { return (T *)::operator new(count * sizeof(T)); }
        static void Deallocate(T * location) { ::operator delete(location); }
        static void Deallocate(T * location, xsize n) { if (n != 0) ::operator delete(location); }
        static void Construct(T * location, const T & value) { Memories::Construct(location, value); }
        static void Destroy(T * location) { Memories::Destroy(location); }
    };

    template <typename T, typename TAllocator> 
    class InsideAllocator
    {
    public:
        static T * Allocate(xsize count) { return count == 0 ? nullptr : (T *)TAllocator::Allocate(count); }
        static T * Allocate() { return (T *)TAllocator::Allocate(1); }
        static void Deallocate(T * location) { TAllocator::Deallocate(location); }
        static void Deallocate(T * location, xsize n) { if (n != 0) TAllocator::Deallocate(location, n); }
    };
}

#endif // XCALLOCATORS_H
