#ifndef RUNNERVIEW_H
#define RUNNERVIEW_H
#include <qtimer.h>
#include <RunnerModel.h>  

#include <QWidget>

class RunnerView : public QWidget
{
    Q_OBJECT

public:
    RunnerView(QWidget *parent = nullptr);
    ~RunnerView();

private:
 //   World world;
};

#endif // RUNNERVIEW_H
