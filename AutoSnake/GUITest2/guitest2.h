#ifndef GUITEST2_H
#define GUITEST2_H

#include <QtWidgets/QMainWindow>
#include "ui_guitest2.h"

class GUITest2 : public QMainWindow
{
	Q_OBJECT

public:
	GUITest2(QWidget *parent = 0);
	~GUITest2();

private:
	Ui::GUITest2Class ui;
};

#endif // GUITEST2_H
