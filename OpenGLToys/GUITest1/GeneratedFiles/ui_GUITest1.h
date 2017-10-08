/********************************************************************************
** Form generated from reading UI file 'GUITest1.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUITEST1_H
#define UI_GUITEST1_H

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

class Ui_GUITest1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GUITest1Class)
    {
        if (GUITest1Class->objectName().isEmpty())
            GUITest1Class->setObjectName(QStringLiteral("GUITest1Class"));
        GUITest1Class->resize(600, 400);
        menuBar = new QMenuBar(GUITest1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        GUITest1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GUITest1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GUITest1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(GUITest1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GUITest1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GUITest1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GUITest1Class->setStatusBar(statusBar);

        retranslateUi(GUITest1Class);

        QMetaObject::connectSlotsByName(GUITest1Class);
    } // setupUi

    void retranslateUi(QMainWindow *GUITest1Class)
    {
        GUITest1Class->setWindowTitle(QApplication::translate("GUITest1Class", "GUITest1", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GUITest1Class: public Ui_GUITest1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUITEST1_H
