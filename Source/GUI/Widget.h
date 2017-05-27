#include "../Core/Core.h"

#include <Windows.h>
#include <Drawing2D/Drawing2D.h>
#include <Drawing2D/GDI/GDI.h>
#include "Defines.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class Application;

    class Widget : public PaintEngine
    {
    public:
        Widget(Application* application = nullptr);

        Widget(const Widget&) = delete;
        
        Widget& operator=(const Widget&) = delete;

        ~Widget();

    public:
        void SetMainWidget(Widget* widget);

        const Drawing2D::Rectangle& GetBoundary();

        void SetBoundary(const Drawing2D::Rectangle& boundary);

        void Repaint();

    public:
        virtual void Show();
   
    protected:
        virtual void OnCreate(BasicEvent& event);

        virtual void OnResize(BasicEvent& event);

        virtual void OnPaint(PaintEvent& event); // override;

        virtual void OnMouseDown(MouseEvent& event); // override;

    private:
        static LRESULT CALLBACK StaticWindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        LRESULT WindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);

        ATOM RegisterClassWin32();
        
        void CreateWindowWin32();
        
        void ShowWin32();

    private:
        /* static */ WCHAR * mClassName = L"CXCWidgetClassName";
        
    private:
        Widget* mMainWidget = nullptr;
        Application * mApplication;
        HINSTANCE mHInstance;
        HWND mHWND;
        Canvas mCanvas;
        Drawing2D::Rectangle mBoundary;
        Widget* mParent = nullptr;
        XC::Array<Widget*> mChildWidgets;
    };

    class Button
    {
    public:
    };

} XC_END_NAMESPACE_2;