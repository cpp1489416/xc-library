#include "DCamera.h"
#include <DirectXMath.h>

using namespace DirectX;

DCamera::DCamera()
{
    XMStoreFloat3(&forward, XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
    XMStoreFloat3(&right, XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f));

    XMStoreFloat3(&position, XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f));
    XMStoreFloat3(&up, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
    updateView();

}

DCamera::~DCamera()
{
}

DirectX::XMFLOAT4X4 DCamera::getView() const
{
    return view;
}

DirectX::XMFLOAT4X4 DCamera::getViewTranspose() const
{
    XMFLOAT4X4 ans;
    XMStoreFloat4x4(&ans, XMMatrixTranspose(getViewXM()));
    return ans;
}

DirectX::XMMATRIX DCamera::getViewXM() const
{
    return XMLoadFloat4x4(&view);
}

void DCamera::walk(float length)
{
    XMVECTOR tmpPosition = XMLoadFloat3(&position);
    XMVECTOR tmpForward = XMLoadFloat3(&forward);
    XMVECTOR tmpValue = length * tmpForward;

    tmpPosition += tmpValue;
    XMStoreFloat3(&position, tmpPosition);

    updateView();
}

void DCamera::strafe(float length)
{
    XMVECTOR tmpPosition = XMLoadFloat3(&position);
    XMVECTOR tmpRight = XMLoadFloat3(&right);

    tmpPosition += length * tmpRight;

    XMStoreFloat3(&position, tmpPosition);

    updateView();
}

void DCamera::fly(float length)
{
    XMVECTOR tmpPosition = XMLoadFloat3(&position);
    XMVECTOR tmpUp = XMLoadFloat3(&up);

    tmpPosition += length * tmpUp;

    XMStoreFloat3(&position, tmpPosition);

    updateView();
}

void DCamera::pitch(float angle)
{
    XMMATRIX rotate = XMMatrixRotationAxis(getRightXM(), angle);
    
   // XMStoreFloat3(&right, XMVector3Transform(getRightXM(), rotate));
    XMStoreFloat3(&up, XMVector3Transform(getUpXM(), rotate));
    XMStoreFloat3(&forward, XMVector3Transform(getForwardXM(), rotate));


    updateView();
}

void DCamera::yaw(float angle)
{
    XMMATRIX rotate = XMMatrixRotationY(angle);//XMMatrixRotationAxis(getUpXM(), angle);

    XMStoreFloat3(&right, XMVector3Transform(getRightXM(), rotate));
    XMStoreFloat3(&forward, XMVector3Transform(getForwardXM(), rotate));
    XMStoreFloat3(&up, XMVector3Transform(getUpXM(), rotate));

    updateView();
}

void DCamera::roll(float angle)
{
    XMMATRIX rotate = XMMatrixRotationAxis(getForwardXM(), angle);

    XMStoreFloat3(&up, XMVector3TransformNormal(getUpXM(), rotate));
    XMStoreFloat3(&right, XMVector3Transform(getRightXM(), rotate));

    updateView();
}

void DCamera::updateView()
{
    XMVECTOR tmpPosition = XMLoadFloat3(&position);
    XMVECTOR tmpForward = XMLoadFloat3(&forward);
    XMVECTOR tmpUp = XMLoadFloat3(&up);
    XMStoreFloat4x4(&view, XMMatrixLookToLH(tmpPosition, tmpForward, tmpUp));
}

DirectX::XMVECTOR DCamera::getPositionXM() const
{
    return XMLoadFloat3(&position);
}

DirectX::XMVECTOR DCamera::getUpXM() const
{
    return XMLoadFloat3(&up);
}

DirectX::XMVECTOR DCamera::getForwardXM() const
{
    return XMLoadFloat3(&forward);
}

DirectX::XMVECTOR DCamera::getRightXM() const
{
    return XMLoadFloat3(&right);
}

