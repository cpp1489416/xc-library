#pragma once

#include "NativeWindow.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class UserNativeWindow : public NativeWindow
    {
    public:
        UserNativeWindow(Application* application = nullptr);

        UserNativeWindow(const UserNativeWindow&) = delete;

        UserNativeWindow& operator=(const UserNativeWindow&) = delete;

        ~UserNativeWindow();

    public:
        UserNativeWindow* GetParent();

        void AddUserNativeWindow(NativeWindow& widget);

    public:
        virtual void Show();

    protected:

    private:
        static LRESULT CALLBACK StaticWindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        LRESULT WindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);

        ATOM RegisterClassWin32();

        void CreateWindowWin32();

        void ShowWin32();

    private:
        /* static */ WCHAR * mClassName = L"CXCUserNativeWindowClassName";

    private:
        UserNativeWindow* mMainUserNativeWindow = nullptr;
        Application * mApplication;
        HINSTANCE mHInstance;
        Drawing2D::Rectangle mBoundary;
        UserNativeWindow* mParent = nullptr;
//        XC::Array<NativeWindow*> mChildUserNativeWindows;
    };



} XC_END_NAMESPACE_2;