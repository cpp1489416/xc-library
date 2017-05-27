#pragma once

#include "../Core/Core.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class Application 
    {
    public:
        Application();
        ~Application();
    
    public:
        void Execute();
        void Quit();

    private:
        class IMPL;
        IMPLPointer<IMPL> mIMPL;
    };

} XC_END_NAMESPACE_2;