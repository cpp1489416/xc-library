#include "../Core/Core.h"

#include <Drawing2D/GDI/GDI.h>
#include "Defines.h"

XC_BEGIN_NAMESPACE_3(XC, GUI, Windows)
{
    class NativeGUIObject //: public IWidget
    {
    public:
        NativeGUIObject()
        {
        }

    public:
        void Show();//

    protected:
        void OnPaint(PaintEvent& paintEvent);// override;

        void OnMouseDown(MouseEvent& mouseEvent);// override;
    };

} XC_END_NAMESPACE_3