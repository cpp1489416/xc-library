#include "stdafx.h"
#include "MWidget.h"
#include "XButton.h"

MWidget::MWidget()
    : XWidget()
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            XButton * button = new XButton;
            button->setBoundary(XRectangle(i * 50, j * 50, 50, 50));
            addWidget(button);
            button->clickedSignal.connect(this, &MWidget::clickedSlot);
            buttonArr[i][j] = button;
        }
    }
}

MWidget::~MWidget()
{
}

void MWidget::clickedSlot()
{
}

void MWidget::onSize(XSizeEvent * event)
{
    int d = event->getHeight() / 19;
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            buttonArr[i][j]->setBoundary(XRectangle(i * d, j * d, d, d));
        }
    }
}
