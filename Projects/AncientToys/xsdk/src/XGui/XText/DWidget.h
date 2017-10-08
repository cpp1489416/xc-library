#ifndef DWIDGET_H
#define DWIDGET_H
#include "xBasic.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include "DPainter.h"
#include <QWidget>
#include <stack>
#include "DCamera.h"

using namespace DirectX;

class DPainter;

class DWidget final : public QWidget
{
    Q_OBJECT

public:
    DWidget(QWidget *parent = nullptr);
    ~DWidget();
    void rotateX();
    void rotateY();
    void rotateZ();
    DCamera *getCamera() const { return camera; }

protected:
    virtual void paintEvent(QPaintEvent *event) final;
    virtual void resizeEvent(QResizeEvent *event) final;
    virtual void mousePressEvent(QMouseEvent *event) final;
    virtual void mouseMoveEvent(QMouseEvent *event) final;
    virtual void mouseReleaseEvent(QMouseEvent *event) final;
    virtual QPaintEngine *paintEngine() const final { return nullptr; }

private:
    void paint(D3D11_VIEWPORT *viewport);
    void updateWVP();
    void initializeD3D();   
    void pushWorldMatrix();
    void multipyWorldMatrix(DirectX::XMMATRIX *matrix);
    void popWorldMatrix();
    void worldMatrixIdentity();
    void setCurrentWorldMatrix(DirectX::XMMATRIX *matrix);

    std::stack<XMFLOAT4X4> worldStack;
    DPainter *d3dPainter;
    HWND hwnd;
    
    ID3D11Device *device;
    ID3D11DeviceContext *context;
    IDXGISwapChain *swapChain;
    ID3D11RenderTargetView *renderTargetView;
    ID3D11VertexShader *VS;
    ID3D11PixelShader *PS;
    ID3D10Blob *VS_Buffer;
    ID3D10Blob *PS_Buffer;
    ID3D11Buffer *constantBuffer;
    ID3D11InputLayout *vertexLayout;
    ID3D11Buffer *worldBuffer;
    ID3D11Buffer *viewBuffer;
    ID3D11Buffer *projectionBuffer;
    ID3D11DepthStencilView *depthStencilView;
    ID3D11Texture2D *depthStencilBuffer;
   // ID3D11DepthStencilState *depthStencilState;

    XMFLOAT4X4 world;
    XMFLOAT4X4 view;
    XMFLOAT4X4 projection;
    XMFLOAT4 eye;
    XMFLOAT4 target;
    XMFLOAT4 up;
    CPerObject WVP;

    const D3D11_INPUT_ELEMENT_DESC layout[2] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    int numElements = 200;

    DCamera *camera;

   // final int a = 10;
};

#endif // DWIDGET_H
