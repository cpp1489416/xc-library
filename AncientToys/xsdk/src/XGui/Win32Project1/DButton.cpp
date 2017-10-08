#include "stdafx.h"
#include "DButton.h"
#include "XBasic.h"

// bool DButton::initialized = false;

DButton::DButton()
{
    //initialized = false;
    //if (!initialized)
    //{
    //    initializeD3D();
    //}
}


DButton::~DButton()
{
}

void DButton::onPaint(XPaintEvent * event)
{
    window->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
   // window->updateWVP();
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    window->context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

    window->context->Draw(5, 0);

    XMMATRIX tmpView = XMMatrixTranspose(XMLoadFloat4x4(&window->WVP.world));

    XMStoreFloat4x4(&window->WVP.world, XMMatrixTranspose(XMMatrixScaling(0.4, 0.4, 0) * tmpView));
    window->updateWVP();
    window->updateConstantBuffer();

    window->context->Draw(5, 0);
}

void DButton::onSize(XSizeEvent * event)
{
}

void DButton::onMouseDown(XMouseEvent * event)
{

}

void DButton::onCreate()
{
    initializeD3D();
}

void DButton::initializeD3D()
{
    initialized = true;

    Vertex vertice[] =
    {
        Vertex(0, 0, 0, 1, 1, 1, 0),
        Vertex(100, 0, 0, 1, 1, 1, 0),
        Vertex(100, 30, 0, 1, 1, 1, 0),
        Vertex(0, 30, 0, 1, 1, 1, 0),
        Vertex(0, 0, 0, 1, 1, 1, 0),
    };

    xBasicCreateBuffer(window->device, D3D11_BIND_VERTEX_BUFFER, sizeof(vertice), vertice, &vertexBuffer);
}
