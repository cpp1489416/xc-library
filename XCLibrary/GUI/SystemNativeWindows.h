#pragma once

#include <Core/Core.h>
#include "NativeWindow.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class Button : public NativeWindow
    {
    public:
        Button();

        void SetParent(NativeWindow& window) override;

    public:
        void Win32OnCommand(WPARAM wParam, LPARAM lParam) override;

    public:
        XC::Delegate<void> MClickedSignal;
    };

    class Label : public NativeWindow
    {
    public:
        Label();

        void SetParent(NativeWindow& window) override;
    };

    class TextBox : public NativeWindow
    {
    public:
        TextBox();

        void SetParent(NativeWindow& window) override;

    public:
        void Win32OnCommand(WPARAM wParam, LPARAM lParam) override;

    public:
        Delegate<void> MTextChangedSignal;
    };

} XC_END_NAMESPACE_2;