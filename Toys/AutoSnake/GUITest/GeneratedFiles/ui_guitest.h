/********************************************************************************
** Form generated from reading UI file 'guitest.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUITEST_H
#define UI_GUITEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUITestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWidget *GUITestClass)
    {
        if (GUITestClass->objectName().isEmpty())
            GUITestClass->setObjectName(QStringLiteral("GUITestClass"));
        GUITestClass->resize(600, 400);
        menuBar = new QMenuBar(GUITestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        GUITestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GUITestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GUITestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(GUITestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GUITestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GUITestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GUITestClass->setStatusBar(statusBar);

        retranslateUi(GUITestClass);

        QMetaObject::connectSlotsByName(GUITestClass);
    } // setupUi

    void retranslateUi(QMainWidget *GUITestClass)
    {
        GUITestClass->setWindowTitle(QApplication::translate("GUITestClass", "GUITest", 0));
    } // retranslateUi

};

namespace Ui {
    class GUITestClass: public Ui_GUITestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUITEST_H
