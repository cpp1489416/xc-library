/********************************************************************************
** Form generated from reading UI file 'CCGame.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CCGAME_H
#define UI_CCGAME_H

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

class Ui_CCGameClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CCGameClass)
    {
        if (CCGameClass->objectName().isEmpty())
            CCGameClass->setObjectName(QStringLiteral("CCGameClass"));
        CCGameClass->resize(600, 400);
        menuBar = new QMenuBar(CCGameClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CCGameClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CCGameClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CCGameClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CCGameClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CCGameClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CCGameClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CCGameClass->setStatusBar(statusBar);

        retranslateUi(CCGameClass);

        QMetaObject::connectSlotsByName(CCGameClass);
    } // setupUi

    void retranslateUi(QMainWindow *CCGameClass)
    {
        CCGameClass->setWindowTitle(QApplication::translate("CCGameClass", "CCGame", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CCGameClass: public Ui_CCGameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CCGAME_H
