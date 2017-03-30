#pragma once

#include <qwidget.h>
#include <Core/Core.h>

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent);
	~MainWidget();

private:
	//XC::Containers::Details::RBTree<int, int, XC_RBTREE_TEST::KeyOfValue, XC::Functors::Less<int> > mTree;
};
