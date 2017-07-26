#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TangQTTest.h"

class TangQTTest : public QMainWindow
{
    Q_OBJECT

public:
    TangQTTest(QWidget *parent = Q_NULLPTR);

private:
    void Run();

private:
    Ui::TangQTTestClass ui;

    QPlainTextEdit* mSourceWidget;
    QPlainTextEdit* mResultWidget;
    QPlainTextEdit* mStringerWidget;
};
