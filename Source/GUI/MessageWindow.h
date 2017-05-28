#pragma once

#include "Defines.h"
#include "NativeWindow.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class MessageWindow
    {
    public:
        enum Type
        {
            Information, 
        };

        enum class Result
        {
            OK, Cancel,
        };

    public:
        static Result Show(NativeWindow* parent, const String& caption, const String& text, Type type = Type::Information);

    };
} XC_END_NAMESPACE_2