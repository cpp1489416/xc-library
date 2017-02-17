#include "xfpiprovider.h"
#include <QPainter>
#include <qimage.h>
#include <qrect.h>
#include <qpoint.h>

XFPIProvider::XFPIProvider(QObject *parent)
    : QObject(parent)
{
    image = new QImage(width, height, QImage::Format::Format_RGBA8888);
    painter = nullptr;
}

XFPIProvider::~XFPIProvider()
{
    delete image;
}

QImage * XFPIProvider::getImage() const
{
    return image;
}

void XFPIProvider::setParser(XFunctionParser &parser)
{
    root = parser.getRoot();
}

void XFPIProvider::genImage(XAbstractParseNode *root, QRectF area)
{
    int cntChilds = root->getCountChilds();
    QPointF startPoint((area.right() + area.left()) / 2, area.top());
    if (cntChilds <= 0)
    {
        if (typeid(*root) == typeid(XConstantParseNode))
        {
            painter->drawText(startPoint, QString::number(root->getValue()));
        }
        else if (typeid(*root) == typeid(XVariableParseNode))
        {
            painter->drawText(startPoint, QString(QChar(static_cast<XVariableParseNode *>(root)->getIndex())));
        }
        return;
    }
    // opposite

    painter->drawText(startPoint, QString::fromStdString(root->getName()));
    QString str = QString::fromStdString(root->getName());
    float dx = area.width() / (float)cntChilds;
    float sx = startPoint.x() - area.width() / 2.0f;
    float curY = startPoint.y() + 70;
    for (int i = 0; i < cntChilds; i++)
    {
        QPointF endPoint(sx + i * dx + dx / 2, curY);
        painter->drawLine(startPoint, endPoint);
        genImage(root->getChild(i), QRectF(sx + i * dx, curY, dx, 0));
    }

}

void XFPIProvider::draw()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            visited[i][j] = false;
        }
    }

    delete painter;
    painter = new QPainter();
    painter->begin(image);
    painter->setFont(QFont("consolas", 11));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillRect(QRectF(0, 0, width, height), Qt::GlobalColor::white);
    genImage(root, QRectF(0, 50, width, height));
    painter->end();
    delete painter;
    painter = nullptr;
}
