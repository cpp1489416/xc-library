#include "ximagewidget.h"
#include <qpainter.h>

XImageWidget::XImageWidget(QWidget *parent)
    : QWidget(parent)
{
    image = nullptr;
}

XImageWidget::~XImageWidget()
{
}

void XImageWidget::setImage(QImage *image)
{
    this->image = image;
    update();
}

void XImageWidget::paintEvent(QPaintEvent *event)
{
    if (image == nullptr)
    {
        return;
    }
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(10, 10), *image);
    painter.end();
}