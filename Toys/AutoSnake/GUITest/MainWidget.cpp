#include "MainWidget.h"
#include <qevent.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include "../AutoSnake/AutoSnake.h"
#include <cassert>

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent), mSnake(20, 20)
{
	connect(&mTimer, &QTimer::timeout, this, &MainWidget::timeout);
	mTimer.start(1);
}

MainWidget::~MainWidget()
{
}

void MainWidget::timeout()
{
	mSnake.timeout();
	update();
//	QMessageBox::information(this, QString::number(mSnake.GetMap().GetSnakeQueue().size()), "");
//	QMessageBox::information(this, "ghier" "", "terwt");
}

void MainWidget::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	int d = 25;
	for (int r = 0; r < mSnake.GetMap().GetCountRows(); r++)
	{
		for (int c = 0; c < mSnake.GetMap().GetCountColumns(); c++)
		{
			if (mSnake.GetMap().GetDot(r, c) == SnakeMap::Dot::Road)
			{
				painter.setBrush(Qt::white);
				painter.drawEllipse(d * r, d * c, d, d);
			}
			else if (mSnake.GetMap().GetDot(r, c) == SnakeMap::Dot::Snake)
			{
				//QMessageBox::warning(this, "greug", "hewgewhjgewhgj ew ");
				painter.setBrush(QBrush(Qt::black));
				// painter.drawRect(d * r, d * c, d, d);
			}
			else if (mSnake.GetMap().GetDot(r, c) == SnakeMap::Dot::Food)
			{
				painter.setBrush(QBrush(Qt::blue));
				painter.drawEllipse(d * r, d * c, d, d);
			}
			else 
			{
				assert(false);
			}
		}
	}

	auto squeue = mSnake.GetMap().GetSnakeQueue();
	QColor curcolor = QColor(Qt::black);
	int red = 0;
	for (auto itr = squeue.begin(); itr != squeue.end(); ++itr)
	{
		auto cur = *itr;
		int r = cur.row;
		int c = cur.column;
		if (itr + 1 == squeue.end()) 
		{
			painter.setBrush(Qt::blue);
		}
		else
		{
			painter.setBrush(QBrush(QColor(red, 0, 0)));
		}
		painter.drawRect(d * r, d * c, d, d);
		red += 50;
		if (red > 255)
		{
			red = 255;
		}
	}

	painter.end();
}
