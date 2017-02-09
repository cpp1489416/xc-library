#pragma once 

namespace XC
{
    namespace DirectX11
    {
        namespace Common
        {
            class Renderer
            {
            public:
                Renderer() = default;
                Renderer(const Renderer &) = delete;
                Renderer & operator = (const Renderer &) = delete;
                virtual ~Renderer();

            public:
                void* mNullPointer = nullptr;
            };
        }
    }
}