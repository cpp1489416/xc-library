#include "RBTreeGUITest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RBTreeGUITest w;
	w.show();
	return a.exec();
}
