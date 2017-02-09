#pragma once

#include "../Common/Renderer.h"

namespace XC
{
	namespace DirectX11
	{
		namespace Renderers
		{
			class Basic2DRenderer : public Common::Renderer
			{
			public:
				Basic2DRenderer(Common::DeviceResources * deviceResources);

			protected:
				void OnUpdate() override;
				void OnRender() override;

			private:
				ID3D11Device * mDevice;
				ID3D11DeviceContext * mContext;

				// shaders
				Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
				Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
			};
		}
	}
}