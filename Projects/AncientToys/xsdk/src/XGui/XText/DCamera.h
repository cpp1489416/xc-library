#pragma once
#include <DirectXMath.h>

class DCamera
{
public:
    DCamera();
    ~DCamera();
    DirectX::XMFLOAT4X4 getView() const;
    DirectX::XMFLOAT4X4 getViewTranspose() const;
    DirectX::XMMATRIX getViewXM() const;
    void walk(float length = 10.0f);
    void strafe(float length = 10.0f);
    void fly(float length = 10.0f);
    void pitch(float angle);
    void yaw(float angle);
    void roll(float angle);
    void updateView();
    DirectX::XMVECTOR getPositionXM() const;
    DirectX::XMVECTOR getUpXM() const;
    DirectX::XMVECTOR getForwardXM() const;
    DirectX::XMVECTOR getRightXM() const;

private:
    DirectX::XMFLOAT4X4 view;
    DirectX::XMFLOAT4X4 viewTranspose;

    DirectX::XMFLOAT3 position;

    DirectX::XMFLOAT3 up;
    DirectX::XMFLOAT3 forward;
    DirectX::XMFLOAT3 right;
    
    DirectX::XMFLOAT3 defaultForward;
    DirectX::XMFLOAT3 defaultRight;
};

