#pragma once

#include "Defines.h"


XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class NativeWindow;
                                                                         
    class Layout
    {
    public:
        void AddWindow(NativeWindow& window);

        void SetParent(NativeWindow& parent);

        XC::Array<NativeWindow*>& GetWindows();

    public:
        virtual void Resize(const Drawing2D::Rectangle& boundary);

    protected:
        XC::Array<NativeWindow*> mWindows;
        NativeWindow* mParent;
    };

    class HorizontalLayout : public Layout
    {
    public:
        void Resize(const Drawing2D::Rectangle& boundary) override;
    };

} XC_END_NAMESPACE_2;