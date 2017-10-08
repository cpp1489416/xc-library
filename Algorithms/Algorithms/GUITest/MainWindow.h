#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <BinaryTree.h>
#include "TreeWidget.h"
#include <AVLTree.h>
#include <RedBlackTree.h>
#include <RedBlackTreeWidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    public slots :
    void addClicked();
    void eraseClicked();
    void randomClicked();
    void showClicked();

private:
    RedBlackTreeWidget * widget;
    Xc::RedBlackTree<int> * mTree;
};

#endif // MAINWINDOW_H
