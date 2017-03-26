#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUITest1.h"

class GUITest1 : public QMainWindow
{
	Q_OBJECT

public:
	GUITest1(QWidget *parent = Q_NULLPTR);

private:
	Ui::GUITest1Class ui;
};
