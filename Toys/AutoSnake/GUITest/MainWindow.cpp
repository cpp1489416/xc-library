#include "MainWidget.h"
#include <qevent.h>
#include <qpainter.h>
#include "../AutoSnake/AutoSnake.h"

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent), mSnake(40, 40)
{
	connect(&mTimer, &QTimer::timeout, this, &MainWidget::timeout);
	mTimer.start(100);
}

MainWidget::~MainWidget()
{

}

void MainWidget::timeout()
{

}

void MainWidget::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	int d = 500;
	for (int r = 0; r < mSnake.GetMap().GetCountRows(); r++)
	{
		for (int c = 0; c < mSnake.GetMap().GetCountColumns(); c++)
		{
			painter.drawRect(d * r, d * c, d, d);
			if (mSnake.GetMap().GetDot(r, c) == SnakeMap::Dot::Snake)
			{
				painter.drawEllipse(d * r, d * c, d, d);
			}
		}
	}
	painter.end();
}
