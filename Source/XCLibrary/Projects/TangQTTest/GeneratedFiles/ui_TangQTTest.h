/********************************************************************************
** Form generated from reading UI file 'TangQTTest.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TANGQTTEST_H
#define UI_TANGQTTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TangQTTestClass
{
public:
    QAction *actionRun;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *plainTextEdit_2;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QPlainTextEdit *plainTextEdit_3;
    QLabel *label;
    QLabel *label_2;
    QPlainTextEdit *plainTextEdit;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *TangQTTestClass)
    {
        if (TangQTTestClass->objectName().isEmpty())
            TangQTTestClass->setObjectName(QStringLiteral("TangQTTestClass"));
        TangQTTestClass->resize(698, 529);
        actionRun = new QAction(TangQTTestClass);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/EE0D258040D18DB8558AE92A70FAFACF.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon);
        centralWidget = new QWidget(TangQTTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        plainTextEdit_2 = new QPlainTextEdit(tab);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));
        plainTextEdit_2->setStyleSheet(QStringLiteral("font: 11pt \"Consolas\";"));

        horizontalLayout->addWidget(plainTextEdit_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_2 = new QHBoxLayout(tab_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        plainTextEdit_3 = new QPlainTextEdit(tab_2);
        plainTextEdit_3->setObjectName(QStringLiteral("plainTextEdit_3"));
        plainTextEdit_3->setStyleSheet(QStringLiteral("font: 11pt \"Consolas\";"));

        horizontalLayout_2->addWidget(plainTextEdit_3);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 1, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("font: 9pt \"Arial\";"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("font: 9pt \"Arial\";"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setStyleSheet(QStringLiteral("font: 11pt \"Consolas\";"));

        gridLayout->addWidget(plainTextEdit, 1, 0, 1, 1);

        TangQTTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TangQTTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TangQTTestClass->setStatusBar(statusBar);
        toolBar = new QToolBar(TangQTTestClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMovable(false);
        toolBar->setOrientation(Qt::Horizontal);
        toolBar->setIconSize(QSize(36, 36));
        TangQTTestClass->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionRun);

        retranslateUi(TangQTTestClass);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(TangQTTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *TangQTTestClass)
    {
        TangQTTestClass->setWindowTitle(QApplication::translate("TangQTTestClass", "TangQTTest", Q_NULLPTR));
        actionRun->setText(QApplication::translate("TangQTTestClass", "Run", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("TangQTTestClass", "ASTSolver", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("TangQTTestClass", "ASTStringer", Q_NULLPTR));
        label->setText(QApplication::translate("TangQTTestClass", "source code:", Q_NULLPTR));
        label_2->setText(QApplication::translate("TangQTTestClass", "result:", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("TangQTTestClass", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TangQTTestClass: public Ui_TangQTTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TANGQTTEST_H
