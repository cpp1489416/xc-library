#include "TreeWidget.h"
#include <qpainter.h>
#include <queue>
#include <qpoint.h>
#include <cstdlib>
#include <ctime>

TreeWidget::TreeWidget(QWidget *parent)
    : QWidget(parent)
{
    mTree = nullptr;
}

TreeWidget::~TreeWidget()
{

}

void TreeWidget::paintEvent(QPaintEvent * event)
{
    if (mTree == nullptr)
    {
        return;
    }

    QPainter painter;
    painter.begin(this);

    unitPaint(painter, root(), QRectF(0, 100, width(), height()));

    painter.end();
}

void TreeWidget::unitPaint(QPainter & painter, Node * node, QRectF location)
{
    if (node == nullptr)
    {
        return;
    }

    QPointF centre((location.left() + location.right()) / 2, location.top());

    //    painter.drawText(centre, QString::number(node->value) + ": " + QString::number(node->count));

    QRectF left(location.left(), location.top() + unitHeight, location.width() / 2, 100);

    if (node->left != nullptr)
    {
        painter.drawLine(centre, QPointF((left.left() + left.right()) / 2.0f, left.top()));
        unitPaint(painter, node->left, left);
    }

    QRectF right(location.left() + location.width() / 2.0f, location.top() + unitHeight, location.width() / 2, 100);
    if (node->right != nullptr)
    {
        painter.drawLine(centre, QPointF((right.left() + right.right()) / 2, right.top()));
        unitPaint(painter, node->right, right);
    }
}
