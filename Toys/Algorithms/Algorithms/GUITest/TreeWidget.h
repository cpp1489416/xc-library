#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <BinaryTree.h>
#include <qrect.h>
#include <AVLTree.h>

class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    typedef Xc::AVLTree<int> Tree;
    typedef Tree::Node Node;

public:
    TreeWidget(QWidget *parent = 0);
    Tree * & rTree() { return mTree; }
    ~TreeWidget();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    inline Node *root() { return mTree->root(); }
    void unitPaint(QPainter &painter, Node *root, QRectF location);

    Tree *mTree;
    double unitHeight = 30;
};

#endif // TREEWIDGET_H
