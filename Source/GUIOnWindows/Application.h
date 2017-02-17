#pragma once

#include "../Core/Core.h"
#include "../GUI/IApplication.h"

XC_BEGIN_NAMESPACE_3(XC, GUI, Windows)
{
    class Application : public IApplication
    {
    public:
        Application();
        ~Application();
    
    public:
        void Execute() override;
        void Quit() override;

    private:
        class IMPL;
        IMPLPointer<IMPL> mIMPL;
    };

} XC_END_NAMESPACE_3