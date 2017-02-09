#pragma once 

#include "DirectX11Includes.h"
#include "DeviceResources.h"

namespace XC
{
    namespace DirectX11
    {
        namespace Common
        {
            class Renderer
            {
            public:
                Renderer(DeviceResources * deviceResources);
                Renderer(const Renderer &) = delete;
                Renderer & operator = (const Renderer &) = delete;
                virtual ~Renderer() {};

            protected:
                virtual void OnResize() {}
                virtual void OnUpdate() {}
                virtual void OnRender() {}

            protected:
                DeviceResources * mDeviceResources;
            };
        }
    }
}