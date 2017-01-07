#pragma once

#ifndef XCBASIC_H
#define XCBASIC_H

#include <cstddef>
#include <new>

namespace XC
{
    // the basic size type basied on the platform
    typedef std::ptrdiff_t xpointerdifference;
    typedef std::size_t xsize;
    typedef int xinteger;
}

#endif // XCBASIC_H