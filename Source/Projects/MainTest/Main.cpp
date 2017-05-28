
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include <GUI/GUI.h>

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    using namespace Drawing2D;

    class TUserNativeWindow : public UserNativeWindow
    {
    public:
        TUserNativeWindow();

    private:
        void OnClicked();
    private:
        Button* mButton;
    };

    TUserNativeWindow::TUserNativeWindow()
    {
        mButton = new Button();
        mButton->SetBoundary(Drawing2D::Rectangle(Drawing2D::Point(10, 10), Drawing2D::Size(300, 300)));
        AddUserNativeWindow(*mButton);
        Button* nButton = new Button();
        nButton->SetBoundary(Drawing2D::Rectangle(Drawing2D::Point(300, 300), Drawing2D::Size(300, 300)));
        nButton->SetText(L"我如尼玛");
        AddUserNativeWindow(*nButton);
        mButton->MClickedSignal.Add(this, &TUserNativeWindow::OnClicked);
    }

    void TUserNativeWindow::OnClicked()
    {
        mButton->SetText(L"我如防守打法啊尼玛");
        mButton->SetBoundary(Rectangle(Point(100, 100), Size(1000, 1000)));
    }


    void Main()
    {
        Application a;
        TUserNativeWindow window;
        window.Show();
        a.Execute();
    }

} XC_END_NAMESPACE_2;