#pragma once

#include "../Core/Core.h"
#include "Events/Events.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class Widget : public Object
    {
    public:
        
    protected:
        virtual void OnLoad(EventArguments * eventArguments);
        virtual void OnResize(EventArguments * eventArguments);
        virtual void OnPaint(EventArguments * eventArguments);
        virtual void OnDestroy(EventArguments * eventArguments);
        virtual void OnMouseDown(EventArguments * eventArguments);
        virtual void OnMouseMove(EventArguments * eventArguments);
        virtual void OnMouseUp(EventArguments * eventArguments);
    
    private:
        class IMPL;
        IMPLPointer<IMPL> mIMPL;
    };

} XC_END_NAMESPACE_2