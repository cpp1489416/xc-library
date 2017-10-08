#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Test.h"

class Test : public QMainWindow
{
    Q_OBJECT

public:
    Test(QWidget *parent = Q_NULLPTR);

private:
    Ui::TestClass ui;
};
