#include "MessageWindow.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    MessageWindow::Result MessageWindow::Show(NativeWindow* parent, const String& caption, const String& text, Type type)
    {
        int ans = MessageBox(parent == nullptr ? NULL : parent->GetWindowID(), text.c_str(), caption.c_str(), MB_OKCANCEL | MB_ICONINFORMATION);
        
        switch (ans)
        {
        case IDOK:
            return Result::OK;
            break;
        case IDCANCEL:
            return Result::Cancel;
            break;
        default:
            break;
        }

        return Result::Cancel;
    }

} XC_END_NAMESPACE_2