#pragma once

#include <QWidget>

namespace XC
{
	namespace DirectX11
	{
		namespace QTGUI
		{
			class DirectX11Widget : public QWidget // must override
			{
				Q_OBJECT

			public:
				explicit DirectX11Widget(QWidget *parent = 0);
				virtual ~DirectX11Widget();

			public:
				QPaintEngine * paintEngine() const override { return nullptr; }

			public:
				HWND GetHWND() const { return mHWND; }

			protected:
				virtual void OnInitializeDirectX11();
				virtual void OnResizeDirectX11();
				virtual void OnPaintDirectX11();

			protected:
				void showEvent(QShowEvent * event) override;
				void resizeEvent(QResizeEvent * event) override;
				void paintEvent(QPaintEvent * event) override;

			private:
				HWND mHWND;
				bool mCreated = false;
			};
		}
	}
}