#ifndef GUITEST_H
#define GUITEST_H

#include <QtWidgets/QMainWidget>
#include "ui_guitest.h"

class GUITest : public QMainWidget
{
	Q_OBJECT

public:
	GUITest(QWidget *parent = 0);
	~GUITest();

private:
	Ui::GUITestClass ui;
};

#endif // GUITEST_H
