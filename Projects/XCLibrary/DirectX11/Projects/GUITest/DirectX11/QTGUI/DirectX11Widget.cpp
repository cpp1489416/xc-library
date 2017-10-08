#include "DirectX11Widget.h"

namespace XC
{
	namespace DirectX11
	{
		namespace QTGUI
		{
			DirectX11Widget::DirectX11Widget(QWidget *parent) :
				QWidget(parent),
				mCreated(false)
			{
				setAttribute(Qt::WA_PaintOnScreen, true);
				setAttribute(Qt::WA_NativeWindow, true);
			}

			DirectX11Widget::~DirectX11Widget()
			{
			}

			void DirectX11Widget::OnInitializeDirectX11()
			{
				// must override
			}
			
			void DirectX11Widget::OnResizeDirectX11()
			{
				// must override
			}
			
			void DirectX11Widget::OnPaintDirectX11()
			{
				// must override
			}

			void DirectX11Widget::showEvent(QShowEvent * event)
			{
				if (!mCreated)
				{
					mCreated = true;
					mHWND = (HWND)winId();
					OnInitializeDirectX11();
				}
			}
			
			void QTGUI::DirectX11Widget::resizeEvent(QResizeEvent * event)
			{
				if (mCreated)
				{
					OnResizeDirectX11();
				}
			}

			void QTGUI::DirectX11Widget::paintEvent(QPaintEvent * event)
			{
				if (mCreated)
				{
					OnPaintDirectX11();
				}
			}
		}
	}
}