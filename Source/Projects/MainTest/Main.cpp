#include <GUIOnWindows/Application.h>
#include <GUIOnWindows/NativeWindow.h>

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    using namespace Windows;
    
    void Main()
    {
        Application a;
        NativeWindow window(&a);
        window.Show();
        a.Execute();
    }

} XC_END_NAMESPACE_2