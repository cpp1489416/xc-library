#include "guitest.h"
#include <QtWidgets/QApplication>
#include "../AutoSnake/AutoSnake.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.aboutQt();
	GUITest w;
	w.show();
	return a.exec();
}
