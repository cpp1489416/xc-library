#pragma once

#include "../GUI/GUI.h"
#include "Common.h"

XC_BEGIN_NAMESPACE_2(XC, DirectX11)
{
    using namespace XC::GUI;
    
    class DirectX11NativeWindow : public UserNativeWindow
    {
    public:
        DirectX11NativeWindow()
        {
            mDeviceResources.SetHWND(GetWindowID());
        }

    protected:
        void OnSizeChanged(BasicEvent* event)
        {
            mDeviceResources.SetSize(GetBoundary().RSize().RWidth(), GetBoundary().RSize().RHeight());
            mDeviceResources.Present();
        }


    private:
        Common::DeviceResources mDeviceResources;
    };

} XC_END_NAMESPACE_2;