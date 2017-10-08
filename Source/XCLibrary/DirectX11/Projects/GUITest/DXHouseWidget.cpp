#include "DXHouseWidget.h"

DXHouseWidget::DXHouseWidget(QWidget *parent)
    : DirectX11Widget(parent)
{
}

DXHouseWidget::~DXHouseWidget()
{
}

void DXHouseWidget::OnInitializeDirectX11()
{
    mDeviceResources.SetHWND(GetHWND());
    mDeviceResources.SetSize(width(), height());
    mDeviceResources.Initialize();
    mDevice = mDeviceResources.GetD3DDevice();
    mContext = mDeviceResources.GetD3DDeviceContext();
    mRenderTargetView = mDeviceResources.GetBackBufferRenderTarGetView();
}

void DXHouseWidget::OnResizeDirectX11()
{
}

void DXHouseWidget::OnPaintDirectX11()
{
    // mDeviceResources.GetD3DDevice()->cldouble 
    float color[] = { 0.0f, 1.0f, 0.0f, 1.0f, };
    mContext->ClearRenderTargetView(mRenderTargetView, color);
    mDeviceResources.Present();
}
