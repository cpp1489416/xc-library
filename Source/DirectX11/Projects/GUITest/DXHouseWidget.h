#pragma once

#include <QObject>
#include "DirectX11/QTGUI/DirectX11Widget.h"
#include <DirectX11/Common/DeviceResources.h>

class DXHouseWidget : public XC::DirectX11::QTGUI::DirectX11Widget
{
	Q_OBJECT

public:
	explicit DXHouseWidget(QWidget *parent = 0);
	virtual ~DXHouseWidget();

protected:
	void OnInitializeDirectX11() override;
	void OnResizeDirectX11() override;
	void OnPaintDirectX11() override;

private:
	XC::DirectX11::Common::DeviceResources mDeviceResources;
	ID3D11Device * mDevice;
	ID3D11DeviceContext * mContext;
	ID3D11RenderTargetView * mRenderTargetView;
};
