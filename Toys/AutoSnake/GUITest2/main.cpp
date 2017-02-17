#include "guitest2.h"
#include <QtWidgets/QApplication>
#include "MainWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWidget widget(nullptr);
	widget.show();
	return a.exec();
}
