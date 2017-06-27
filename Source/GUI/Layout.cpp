#include "Layout.h"
#include "NativeWindow.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    void Layout::AddWindow(NativeWindow& window)
    {
        mWindows.PushBack(&window);
    }

     Array<NativeWindow*>& Layout::GetWindows()
    {
        return mWindows;
    }

    void Layout::SetParent(NativeWindow& parent)
    {
        mParent = &parent;
    }

    void Layout::Resize(const Drawing2D::Rectangle& boundary)
    {
    }

    void HorizontalLayout::Resize(const Drawing2D::Rectangle& boundary)
    {
        double dx = boundary.RSize().RWidth() / mWindows.GetSize();
        double dy = boundary.RSize().RHeight();
        Drawing2D::Rectangle rect;
        rect.RStart() = boundary.RStart();
        rect.RSize().RWidth() = dx;
        rect.RSize().RHeight() = dy;
        for (NativeWindow* window : mWindows)
        {
            window->SetBoundary(rect);
            rect.RStart().RX() += dx;
        }
    }
} XC_END_NAMESPACE_2;