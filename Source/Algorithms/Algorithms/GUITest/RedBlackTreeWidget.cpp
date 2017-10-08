#include "RedBlackTreeWidget.h"
#include <QMessageBox>
#include <QPainter>

RedBlackTreeWidget::RedBlackTreeWidget(QWidget *parent)
    : QWidget(parent)
{
    mTree = nullptr;
}

RedBlackTreeWidget::~RedBlackTreeWidget()
{

}

void RedBlackTreeWidget::paintEvent(QPaintEvent * event)
{
    if (mTree == nullptr)
    {
        return;
    }

    QPainter painter(this);
    painter.begin(this);
    painter.fillRect(0, 0, width(), height(), Qt::white);
    painter.setRenderHint(QPainter::Antialiasing);
    unitPaint(painter, mTree->UNSAFERoot(), QRectF(0, 100, width(), height()));
}

void RedBlackTreeWidget::unitPaint(QPainter & painter, Node * node, QRectF location)
{
    QPointF centre((location.left() + location.right()) / 2, location.top());

    if (node == nullptr)
    {
        painter.setBrush(QBrush(Qt::black));
        // painter.drawRect(centre.rx() - 5, centre.ry() - 5, 10, 10);
        return;
    }

    if (node->mColor == Node::BLACK)
    {
        painter.setBrush(Qt::black);
        painter.setPen(Qt::black);
    }
    else
    {
        painter.setBrush(Qt::GlobalColor::red);
        painter.setPen(Qt::GlobalColor::red);
    }

    painter.drawEllipse(centre, 10, 10);

    painter.setPen(Qt::GlobalColor::magenta);
    painter.drawText(centre, QString::number(node->value()));


    painter.setPen(Qt::black);
    QRectF left(location.left(), location.top() + unitHeight, location.width() / 2, 100);


    if (node->mLeft != nullptr)
    {
        painter.drawLine(centre, QPointF((left.left() + left.right()) / 2.0f, left.top()));
        unitPaint(painter, node->mLeft, left);
    }

    QRectF right(location.left() + location.width() / 2.0f, location.top() + unitHeight, location.width() / 2, 100);
    if (node->mRight != nullptr)
    {
        painter.drawLine(centre, QPointF((right.left() + right.right()) / 2, right.top()));
        unitPaint(painter, node->mRight, right);
    }
}
