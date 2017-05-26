#include "../GUI/INativeWindow.h"
#include "../Core/Core.h"

XC_BEGIN_NAMESPACE_3(XC, GUI, Windows)
{
    class Application;

    class NativeWindow : INativeWindow
    {
    public:
        NativeWindow(Application * application = nullptr);
        ~NativeWindow();

    public:
        void Show() override;

    protected:
        virtual void OnPaint(const PaintEvent& paintEvent);

        virtual void OnMouseDown(const MouseEvent& mouseEvent);
    
    private:
        class IMPL;
        IMPLPointer<IMPL> mIMPL;
    };

} XC_END_NAMESPACE_3