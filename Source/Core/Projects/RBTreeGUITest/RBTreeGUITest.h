#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RBTreeGUITest.h"

class RBTreeGUITest : public QMainWindow
{
	Q_OBJECT

public:
	RBTreeGUITest(QWidget *parent = Q_NULLPTR);

private:
	Ui::RBTreeGUITestClass ui;
};
