/********************************************************************************
** Form generated from reading UI file 'RBTreeGUITest.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RBTREEGUITEST_H
#define UI_RBTREEGUITEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RBTreeGUITestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RBTreeGUITestClass)
    {
        if (RBTreeGUITestClass->objectName().isEmpty())
            RBTreeGUITestClass->setObjectName(QStringLiteral("RBTreeGUITestClass"));
        RBTreeGUITestClass->resize(600, 400);
        menuBar = new QMenuBar(RBTreeGUITestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        RBTreeGUITestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RBTreeGUITestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RBTreeGUITestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(RBTreeGUITestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        RBTreeGUITestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(RBTreeGUITestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RBTreeGUITestClass->setStatusBar(statusBar);

        retranslateUi(RBTreeGUITestClass);

        QMetaObject::connectSlotsByName(RBTreeGUITestClass);
    } // setupUi

    void retranslateUi(QMainWindow *RBTreeGUITestClass)
    {
        RBTreeGUITestClass->setWindowTitle(QApplication::translate("RBTreeGUITestClass", "RBTreeGUITest", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RBTreeGUITestClass: public Ui_RBTreeGUITestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RBTREEGUITEST_H
