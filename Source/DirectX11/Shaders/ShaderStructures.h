#pragma once

#include <DirectXMath.h>

namespace XC
{
    namespace DirectX11
    {
        namespace Shaders
        {
            namespace ShaderStructures
            {
                class ModelViewProjectionConstantBuffer
                {
                public:
                    DirectX::XMFLOAT4X4 mModel;
                    DirectX::XMFLOAT4X4 mView;
                    DirectX::XMFLOAT4X4 mProjection;
                };

				class VertexPosition
				{
				public:
					DirectX::XMFLOAT3 mPosition;
				};

                class VertexPositionColor
                {
                public:
                    DirectX::XMFLOAT3 mPosition;
                    DirectX::XMFLOAT3 mColor;
                };
            }
        }
    }
}