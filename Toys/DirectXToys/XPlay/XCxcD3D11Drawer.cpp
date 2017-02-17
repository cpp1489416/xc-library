#include "XCxcD3D11Drawer.h"
#include <cmath>

XCxcD3D11Drawer::XCxcD3D11Drawer()
{
}

XCxcD3D11Drawer::~XCxcD3D11Drawer()
{
	delete ball;
    delete cube;
}

void XCxcD3D11Drawer::initializeScene()
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	D3DX11CompileFromFile(L"Effects.fx", NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &vertexShaderBuffer, NULL, NULL);
	D3DX11CompileFromFile(L"Effects.fx", NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pixelShaderBuffer, NULL, NULL);
	device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);
	device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);
	context->VSSetShader(vertexShader, NULL, NULL);
	context->PSSetShader(pixelShader, NULL, NULL);
	device->CreateInputLayout(layout, 2, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &vertexLayout);
	context->IASetInputLayout(vertexLayout);

	XCreateSimpleBufferNull(D3D11_BIND_CONSTANT_BUFFER, sizeof(ConstantBuffer), &constantBuffer);

//	XMStoreFloat4x4(&world, XMMatrixIdentity());

	//XMVECTOR eye = XMVectorSet(0.0f, 0.0f, 5.0f, 0.0f);
	//XMVECTOR at = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	//XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//XMStoreFloat4x4(&view, XMMatrixLookAtLH(eye, at, up));

	//XMMATRIX tpprojection = XMMatrixPerspectiveFovLH(XM_PIDIV2, width / (float)height, 0.01f, 100000.0f);
	//XMStoreFloat4x4(&projection, tpprojection);

	ball = new XD3D11Ball(this);
	ball->setSolid(false);
	ball->create(40);

    cube = new XD3D11Cube(this);
    cube->setSolid(true);
    cube->create();
    ConstantBuffer cb;
    	context->UpdateSubresource(constantBuffer, 0, NULL, &cb, 0, 0);
    	context->VSSetConstantBuffers(0, 1, &constantBuffer);

}

void XCxcD3D11Drawer::update()
{
}

void XCxcD3D11Drawer::draw()
{
	float backColors[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	context->ClearRenderTargetView(renderTargetView, backColors);
	// context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 10.0f, 0);

	//XMMATRIX wd = XMLoadFloat4x4(&world);

	for (int i = 0; i < 1; i++) 
	{
		ConstantBuffer cb;
		
		////XMMATRIX wd = XMLoadFloat4x4(&world);
		//wd *= XMMatrixTranslation(1.5 * i, 0, 0);

		//cb.Projection = 
       // XMStoreFloat4x4(&cb.Projection, XMMatrixTranspose(XMLoadFloat4x4(&projection)));
        //XMStoreFloat4x4(&cb.View, XMMatrixTranspose(XMLoadFloat4x4(&view)));
        //XMStoreFloat4x4(&cb.World, XMMatrixTranspose(wd));
		//cb.View = XMMatrixTranspose(XMLoadFloat4x4(&view));
		//cb.World = XMMatrixTranspose(wd);

	//	context->UpdateSubresource(constantBuffer, 0, NULL, &cb, 0, 0);
	//	context->VSSetConstantBuffers(0, 1, &constantBuffer);

		ball->draw();

		static float ang = 0.0;
		//	ang += 0.005f;
		if (ang >= 6.28f)
		{
			ang = 0.0f;
		}

		//XMVECTOR anxis = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
		//XMMATRIX ball2World =  XMMatrixRotationAxis(anxis, ang) * XMMatrixTranslation(20.0f, 0.0f, 0.0f)  *wd;
		//cb.World = XMMatrixTranspose(ball2World);

       // XMStoreFloat4x4(&cb.World, XMMatrixTranspose(ball2World));

		//context->UpdateSubresource(constantBuffer, 0, NULL, &cb, 0, 0);
		//context->VSSetConstantBuffers(0, 1, &constantBuffer);
		ball->draw();

		//anxis = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
		//XMMATRIX ball3World = XMMatrixTranslation(3.0f, 0.0f, 0.0f) * XMMatrixRotationAxis(anxis, ang) * ball2World;
        //XMStoreFloat4x4(&cb.World, XMMatrixTranspose(ball3World));
		//context->UpdateSubresource(constantBuffer, 0, NULL, &cb, 0, 0);
		//context->VSSetConstantBuffers(0, 1, &constantBuffer);

		ball->draw();
	}
	
	swapChain->Present(0, 0);
}

void XCxcD3D11Drawer::rotateY(float ang)
{
	XMVECTOR rotaxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//XMMATRIX m = XMLoadFloat4x4(&world);
	//m *= XMMatrixRotationAxis(rotaxis, ang);
	//XMStoreFloat4x4(&world, m);
}

void XCxcD3D11Drawer::rotateX(float ang)
{
	XMVECTOR rotaxis = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	//XMMATRIX m = XMLoadFloat4x4(&world);
	//m *= XMMatrixRotationAxis(rotaxis, ang);
	//XMStoreFloat4x4(&world, m);
}

void XCxcD3D11Drawer::rotateZ(float ang)
{
	XMVECTOR rotaxis = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	//XMMATRIX m = XMLoadFloat4x4(&world);
	///m *= XMMatrixRotationAxis(rotaxis, ang);
	//XMStoreFloat4x4(&world, m);
}
