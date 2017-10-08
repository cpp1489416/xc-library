#ifndef REDBLACKTREEWIDGET_H
#define REDBLACKTREEWIDGET_H

#include <QWidget>
#include <RedBlackTree.h>

class RedBlackTreeWidget : public QWidget
{
    Q_OBJECT

public:
    typedef Xc::RedBlackTree<int> Tree;
    typedef Xc::RedBlackTree<int>::Node Node;

public:
    RedBlackTreeWidget(QWidget *parent = 0);
    ~RedBlackTreeWidget();
    inline Tree * & rTree() { return mTree; }

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    void unitPaint(QPainter & painter, Node * node, QRectF location);

    Tree *mTree;

    const float unitHeight = 40.0f;
};

#endif // REDBLACKTREEWIDGET_H
