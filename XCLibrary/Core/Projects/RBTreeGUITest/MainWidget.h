#pragma once

#include <qwidget.h>
#include <Core/Core.h>

class MainWidget : public QWidget, virtual public XC::CallableObject
{
    Q_OBJECT

public:
    using Node = XC::Containers::Details::RBTreeNode<int>;
    using Tree = XC::Containers::Details::RBTree<int, int, XC_RBTREE_TEST::KeyOfValue, XC::Functors::Less<int> >;
    using Color = XC::Containers::Details::RBTreeColorType;

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

public:
    bool TestNodesRelationship();
    bool TestNodesRelationship(Node* node);
    void TreeChanged();

protected:
    void paintEvent(QPaintEvent* event) override;

    private slots:
    void Timeout();

private: public:
    void Paint(Node* node, QRect boundary, QPainter& painter);
    
    Tree mTree;
    qreal mDeltaY = 50;
    qreal mCircleRadius = 15;
};
