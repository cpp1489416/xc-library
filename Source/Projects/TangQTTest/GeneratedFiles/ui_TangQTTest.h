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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TangQTTestClass
{
public:
    QAction *actionRun;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QPlainTextEdit *plainTextEdit_2;
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
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("font: 9pt \"Arial\";"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("font: 9pt \"Arial\";"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setStyleSheet(QStringLiteral("font: 11pt \"Consolas\";"));

        gridLayout->addWidget(plainTextEdit, 2, 0, 1, 1);

        plainTextEdit_2 = new QPlainTextEdit(centralWidget);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));
        plainTextEdit_2->setStyleSheet(QStringLiteral("font: 11pt \"Consolas\";"));

        gridLayout->addWidget(plainTextEdit_2, 2, 1, 1, 1);

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

        QMetaObject::connectSlotsByName(TangQTTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *TangQTTestClass)
    {
        TangQTTestClass->setWindowTitle(QApplication::translate("TangQTTestClass", "TangQTTest", Q_NULLPTR));
        actionRun->setText(QApplication::translate("TangQTTestClass", "Run", Q_NULLPTR));
        label_2->setText(QApplication::translate("TangQTTestClass", "result:", Q_NULLPTR));
        label->setText(QApplication::translate("TangQTTestClass", "source code:", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("TangQTTestClass", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TangQTTestClass: public Ui_TangQTTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TANGQTTEST_H
