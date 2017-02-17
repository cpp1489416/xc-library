#include "../GUI/INativeWindow.h"

XC_BEGIN_NAMESPACE_3(XC, GUI, Windows)
{
    class NativeWindow : INativeWindow
    {
    public:
        void Show() override;
    };

} XC_END_NAMESPACE_3