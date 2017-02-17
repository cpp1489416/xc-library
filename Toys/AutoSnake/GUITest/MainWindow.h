#ifndef MainWidget_H
#define MainWidget_H

#include <QWidget>
#include "../AutoSnake/AutoSnake.h"
#include <qtimer.h>

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent);
	~MainWidget();

public:	public slots :
	void timeout();
		
protected:
	virtual void paintEvent(QPaintEvent *event) override;

private:
	AutoSnake mSnake;
	QTimer mTimer;
};

#endif // MainWidget_H
