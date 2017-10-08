#include "CCGame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CCGame w;
	w.show();
	return a.exec();
}
