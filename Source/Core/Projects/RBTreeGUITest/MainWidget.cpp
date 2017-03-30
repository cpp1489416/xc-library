#include "MainWidget.h"
#include <qpainter.h>
#include <qevent.h>
#include <qmessagebox.h>
#include <qpen.h>
#include <cstdlib>
#include <ctime>

using namespace XC;
using namespace XC::Containers;
using namespace XC::Containers::Details;

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    srand(time(nullptr));
    for (int i = 0; i < 10000; ++i)
    {
        mTree.InsertUnique(rand() % 100);
    }
    mCircleRadius = 10;
    TestNodesRelationship();
    mTree.ChangedEvent.Add(this, &MainWidget::TreeChanged);
}

MainWidget::~MainWidget()
{
}

bool MainWidget::TestNodesRelationship()
{
    return TestNodesRelationship(mTree.mHeader->mParent);
}

bool MainWidget::TestNodesRelationship(Node * node)
{
    if (node == nullptr)
    {
        return true;
    }

    if ((node->mLeft == nullptr || node->mLeft->mParent == node) &&
        (node->mRight == nullptr || node->mRight->mParent == node)
        )
    {
        return TestNodesRelationship(node->mLeft) && TestNodesRelationship(node->mRight);
    }
    else
    {
        QMessageBox::information(nullptr, QString::number(node->mValue), "ge");
        return false;
    }
}

void MainWidget::TreeChanged()
{
    update();
}

void MainWidget::paintEvent(QPaintEvent * event)
{
    QPainter painter;
    painter.begin(this);

    RBTreeNode<int>* root = mTree.mHeader;
    Paint(mTree.mHeader->mParent, QRect(0, 100, width(), height()), painter);
}

void MainWidget::Paint(Node * node, QRect boundary, QPainter& painter)
{
    if (node == nullptr)
    {
        return;
    }

    QPointF location = QPointF(boundary.x() + boundary.width() / 2.0f, boundary.y());
    QRect leftBoundary(boundary.x(), boundary.y() + mDeltaY, boundary.width() / 2, 0);
    QRect rightBoundary(boundary.x() + boundary.width() / 2, boundary.y() + mDeltaY, boundary.width() / 2, 0);

    if (node->mColor == Color::Red)
    {
        painter.setBrush(Qt::red);
        painter.drawEllipse(location, mCircleRadius, mCircleRadius);
        painter.setPen(Qt::green);
        painter.drawText(QPoint(location.x() - 4, location.y() + 4), QString::number(node->mValue));
    }
    else
    {
        painter.setBrush(Qt::black);
        painter.drawEllipse(location, mCircleRadius, mCircleRadius);
        painter.setPen(Qt::white);
        painter.drawText(QPoint(location.x() - 4, location.y() + 4), QString::number(node->mValue));
    }

    painter.setPen(Qt::black);
    painter.drawLine(location, QPoint(leftBoundary.x() + leftBoundary.width() / 2, leftBoundary.y()));
    painter.drawLine(location, QPoint(rightBoundary.x() + rightBoundary.width() / 2, rightBoundary.y()));

    Paint(node->mLeft, leftBoundary, painter);
    Paint(node->mRight, rightBoundary, painter);
}
