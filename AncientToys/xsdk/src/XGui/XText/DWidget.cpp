#include "DWidget.h"
#include <qevent.h>
#include "GeometryProvider.h"
#include "DSkymap.h"
#include <SpriteFont.h>
#include <SpriteBatch.h>
#include <DWidget.h>


using namespace DirectX;

namespace
{
    ID3D11Buffer *boolBuffer;
    ID3D11DepthStencilView* pDSV;
    struct ABCD
    {
        bool a;
    }isT;


    ID3D11Buffer *cylinderVertexBuffer;
    ID3D11Buffer *cylinderIndexBuffer;
    DSkymap *skymap;

    D3D11_VIEWPORT viewport1;
    D3D11_VIEWPORT viewport2;

    SpriteFont *spriteFont;
    SpriteBatch *spriteBatch;
}

DWidget::DWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NativeWindow, true);
    setAutoFillBackground(false);
    // setFocusPolicy(Qt::StrongFocus);
    hwnd = (HWND)winId();
    initializeD3D();
    depthStencilBuffer = nullptr;
    depthStencilView = nullptr;
    d3dPainter = new DPainter;
    d3dPainter->context = context;
    d3dPainter->device = device;
    d3dPainter->createSphere(10, 100);
    d3dPainter->createCube();
    skymap = new DSkymap(device);

    camera = new DCamera;

    spriteFont = new SpriteFont(device, L"Consolas.spritefont");
    spriteBatch = new SpriteBatch(context);
    // skymap->cubeTextureSamplerState = d3dPainter->cubeTextureSamplerState;
    // skymap->shaderResourceView = d3dPainter->skymapShaderResoureView;
}

DWidget::~DWidget()
{
    context->Release();
    device->Release();
}

void DWidget::rotateX()
{
    XMMATRIX tmpWord;// = XMLoadFloat4x4(&world);
    XMVECTOR anx = XMVectorSet(1, 0, 0, 0);
    tmpWord = XMMatrixRotationAxis(anx, 0.05f);
    multipyWorldMatrix(&tmpWord);
    update();
}

void DWidget::rotateY()
{
    XMMATRIX tmpWord;// = XMLoadFloat4x4(&world);
    XMVECTOR anx = XMVectorSet(0, 1, 0, 0);
    tmpWord = XMMatrixRotationAxis(anx, 0.01f);
    multipyWorldMatrix(&tmpWord);
    update();
}

void DWidget::rotateZ()
{
    XMMATRIX tmpWord;
    XMVECTOR anx = XMVectorSet(0, 0, 1, 0);
    tmpWord = XMMatrixRotationAxis(anx, 0.05f);
    multipyWorldMatrix(&tmpWord);
    update();
}

void DWidget::paintEvent(QPaintEvent * event) 
{
    FLOAT bgColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    context->ClearRenderTargetView(renderTargetView, bgColor);
    context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
    paint(&viewport1);
    context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
    paint(&viewport2);   
    swapChain->Present(0, 0);
}

void DWidget::paint(D3D11_VIEWPORT * viewport)
{
    context->RSSetViewports(1, viewport);

    {
        {
            pushWorldMatrix();
            XMMATRIX skyWorld = skymap->getWorldXM(*camera);
            skyWorld *= XMMatrixTranslation(
                1 * XMVectorGetX(camera->getForwardXM()),
                1 * XMVectorGetY(camera->getForwardXM()),
                1 * XMVectorGetZ(camera->getForwardXM())
            );
            setCurrentWorldMatrix(&skyWorld);
            skymap->draw(context);
            popWorldMatrix();
        }

        pushWorldMatrix();

        context->VSSetShader(VS, NULL, 0);
        context->PSSetShader(PS, NULL, 0);

        multipyWorldMatrix(&XMMatrixScaling(0.14f, 0.14f, 0.14f));

        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                for (int k = 1; k <= 9; k++)
                {
                    {
                        pushWorldMatrix();
                        multipyWorldMatrix(&XMMatrixTranslation(i, j, k));
                        multipyWorldMatrix(&XMMatrixScaling(0.1f, 0.1f, 0.1f));
                        d3dPainter->drawCube(i + j + k);
                        popWorldMatrix();
                    }
                }
            }
        }

        popWorldMatrix();
    }
}

void DWidget::updateWVP()
{
    XMStoreFloat4x4(&WVP.world, XMMatrixTranspose(XMLoadFloat4x4(&world)));
    XMStoreFloat4x4(&WVP.projection, XMMatrixTranspose(XMLoadFloat4x4(&projection)));
    WVP.view = camera->getViewTranspose();

    context->UpdateSubresource(constantBuffer, 0, NULL, &WVP, 0, 0);
    context->VSSetConstantBuffers(0, 1, &constantBuffer);
    ::isT.a = 0;
}

void DWidget::resizeEvent(QResizeEvent * event)
{
    int width = this->width();
    int height = this->height();

    if (swapChain == nullptr)
    {
        return;
    }

    if (renderTargetView)
    {
        renderTargetView->Release();
    }

    swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
    ID3D11Texture2D *buffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&buffer);
    device->CreateRenderTargetView(buffer, NULL, &renderTargetView);
    buffer->Release();
    context->OMSetRenderTargets(1, &renderTargetView, NULL);

    ZeroMemory(&viewport1, sizeof(D3D11_VIEWPORT));
    viewport1.TopLeftX = 0;
    viewport1.TopLeftY = 0;
    viewport1.Width = width;// / 2;
    viewport1.Height = height;// / 2;
    viewport1.MinDepth = 0;
    viewport1.MaxDepth = 1;
    //context->RSSetViewports(1, &viewport1);

    ZeroMemory(&viewport2, sizeof(D3D11_VIEWPORT));
    viewport2.TopLeftX = 0;
    viewport2.TopLeftY = 0;
    viewport2.Width = 500;
    viewport2.Height = 500;
    viewport2.MinDepth = 0;
    viewport2.MaxDepth = 1;

    D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
    ZeroMemory(&depthStencilBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
    depthStencilBufferDesc.Width = width;
    depthStencilBufferDesc.Height = height;
    depthStencilBufferDesc.MipLevels = 1;
    depthStencilBufferDesc.ArraySize = 1;
    depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilBufferDesc.SampleDesc.Count = 1;
    depthStencilBufferDesc.SampleDesc.Quality = 0;
    depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilBufferDesc.CPUAccessFlags = 0;
    depthStencilBufferDesc.MiscFlags = 0;

    device->CreateTexture2D(&depthStencilBufferDesc, NULL, &depthStencilBuffer);

    device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
    context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
    
    XMMATRIX tmpProjection = XMMatrixPerspectiveFovLH(XM_PIDIV2 / 2, (float)width / (float)height, 0.01f, 1000.0f);
    XMStoreFloat4x4(&projection, tmpProjection);
}

namespace
{
    int lastX;
    int lastY;
    bool isDown = false;
}

void DWidget::mousePressEvent(QMouseEvent * event)
{
    if (isDown)
    {

    }
    else
    {
        lastX = event->x();
        lastY = event->y();
        isDown = true;
    }
}

void DWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (isDown)
    {
        int curX = event->x();
        int curY = event->y();

        const float seed = 0.001f;

        camera->yaw(seed * (curX - lastX));
        camera->pitch(seed * (curY - lastY));

        lastX = curX;
        lastY = curY;

        update();
    }
}

void DWidget::mouseReleaseEvent(QMouseEvent * event)
{
    isDown = false;
}

void DWidget::initializeD3D()
{
    ::xBasicInitializeDirectX11(hwnd, &swapChain, &device, &context, &renderTargetView);
    ::xBasicCreateShader(device, context, L"Effects.fx", &VS_Buffer, &PS_Buffer, &VS, &PS);
    ::xBasicCreateBuffer(device, D3D11_BIND_CONSTANT_BUFFER, sizeof(CPerObject), &WVP, &constantBuffer);
    ::xBasicCreateBuffer(device, D3D11_BIND_CONSTANT_BUFFER, 16, &::isT, &::boolBuffer);

    XMMATRIX tmpWorld = XMMatrixScaling(0.1f, 0.1f, 0.1f) *XMMatrixTranslation(100.0f * 0, 100.0f * 0, 0.0f);
    XMStoreFloat4x4(&world, tmpWorld);


    //Create the Input Layout
    device->CreateInputLayout(layout, 2, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &vertexLayout);

    //Set the Input Layout
    context->IASetInputLayout(vertexLayout);

    GeometryProvider provider;
    std::vector<Vertex> vertices;
    std::vector<UINT> indices;
    GeometryProvider::MeshData data;
    provider.createCylinder(data, 36);
    for (size_t i = 0; i < data.vertices.size(); i++)
    {
        Vertex tmpV;
        tmpV.pos = data.vertices[i].position;
        tmpV.color = XMFLOAT4(rand() % 2, rand() % 2, rand() % 2, 1);
        vertices.push_back(tmpV);
    }

    for (size_t i = 0; i < data.indices.size(); i++)
    {
        indices.push_back(data.indices[i]);
    }

    ::xBasicCreateBuffer(device, D3D11_BIND_VERTEX_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], &cylinderVertexBuffer);
    ::xBasicCreateBuffer(device, D3D11_BIND_INDEX_BUFFER, indices.size() * sizeof(UINT), &indices[0], &cylinderIndexBuffer);
}

void DWidget::pushWorldMatrix()
{
    if (worldStack.empty())
    {
        worldMatrixIdentity();
    }
    worldStack.push(worldStack.top());
}

void DWidget::multipyWorldMatrix(DirectX::XMMATRIX * matrix)
{
    if (worldStack.empty())
    {
        worldMatrixIdentity();
    }

    XMMATRIX aMatrix = XMLoadFloat4x4(&worldStack.top());
    XMMATRIX ansMatrix = *matrix * aMatrix;
    XMStoreFloat4x4(&worldStack.top(), ansMatrix);

    world = worldStack.top();
    updateWVP();
}

void DWidget::popWorldMatrix()
{
    worldStack.pop();

    world = worldStack.top();

    updateWVP();
}

void DWidget::worldMatrixIdentity()
{
    while (!worldStack.empty())
    {
        worldStack.pop();
    }

    worldStack.push(XMFLOAT4X4());

    XMStoreFloat4x4(&worldStack.top(), XMMatrixIdentity());
    
    world = worldStack.top();
    updateWVP();
}

void DWidget::setCurrentWorldMatrix(DirectX::XMMATRIX * matrix)
{
    if (worldStack.empty())
    {
        worldMatrixIdentity();
    }

    XMMATRIX aMatrix = XMLoadFloat4x4(&worldStack.top());
    XMMATRIX ansMatrix = *matrix;
    XMStoreFloat4x4(&worldStack.top(), ansMatrix);

    world = worldStack.top();
    updateWVP();
}
