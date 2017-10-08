#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CCGame.h"

class CCGame : public QMainWindow
{
	Q_OBJECT

public:
	CCGame(QWidget *parent = Q_NULLPTR);

private:
	Ui::CCGameClass ui;
};
