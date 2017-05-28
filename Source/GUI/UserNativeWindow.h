#pragma once

#include "NativeWindow.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class Layout;

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

        void SetLayout(Layout* layout);

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

        /* static */ WCHAR * mClassName = L"CXCUserNativeWindowClassName";

    private:
        UserNativeWindow* mMainUserNativeWindow = nullptr;

        Application * mApplication;
        
        HINSTANCE mHInstance;
        
        UserNativeWindow* mParent = nullptr;
        
        Layout* mLayout = nullptr;
//        XC::Array<NativeWindow*> mChildUserNativeWindows;
    };



} XC_END_NAMESPACE_2;