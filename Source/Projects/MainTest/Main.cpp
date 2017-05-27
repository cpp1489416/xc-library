#include <GUI/Application.h>
#include <GUI/Widget.h>

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    
    void Main()
    {
        Application a;
        Widget window(&a);
        window.Show();
        a.Execute();
    }

} XC_END_NAMESPACE_2