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
        double constantWidth = 0.0;
        int constantWidthWindowCount = 0;
        for (NativeWindow* window : mWindows)
        {
            if (window->IsSizeAutoChangeable() == false)
            {
                ++constantWidthWindowCount;
                constantWidth += window->GetBoundary().RSize().RWidth();
            }
        }


        double dx = (boundary.RSize().RWidth() - constantWidth) / (mWindows.GetSize() - constantWidthWindowCount);
        double dy = boundary.RSize().RHeight();
        Drawing2D::Rectangle rect;
        rect.RStart() = boundary.RStart();
        rect.RSize().RWidth() = dx;
        rect.RSize().RHeight() = dy;
        for (NativeWindow* window : mWindows)
        {
            if (window->IsSizeAutoChangeable())
            {
                rect.RSize().RWidth() = dx;
                window->SetBoundary(rect);
                rect.RStart().RX() += dx;
            }
            else
            {
                rect.RSize().RWidth() = window->GetBoundary().RSize().RWidth();
                window->SetBoundary(rect);
                rect.RStart().RX() += window->GetBoundary().RSize().RWidth();
            }

        }
    }
} XC_END_NAMESPACE_2;