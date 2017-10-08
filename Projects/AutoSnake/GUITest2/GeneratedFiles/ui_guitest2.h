/********************************************************************************
** Form generated from reading UI file 'guitest2.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUITEST2_H
#define UI_GUITEST2_H

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

class Ui_GUITest2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GUITest2Class)
    {
        if (GUITest2Class->objectName().isEmpty())
            GUITest2Class->setObjectName(QStringLiteral("GUITest2Class"));
        GUITest2Class->resize(600, 400);
        menuBar = new QMenuBar(GUITest2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        GUITest2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GUITest2Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GUITest2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(GUITest2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GUITest2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GUITest2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GUITest2Class->setStatusBar(statusBar);

        retranslateUi(GUITest2Class);

        QMetaObject::connectSlotsByName(GUITest2Class);
    } // setupUi

    void retranslateUi(QMainWindow *GUITest2Class)
    {
        GUITest2Class->setWindowTitle(QApplication::translate("GUITest2Class", "GUITest2", 0));
    } // retranslateUi

};

namespace Ui {
    class GUITest2Class: public Ui_GUITest2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUITEST2_H
