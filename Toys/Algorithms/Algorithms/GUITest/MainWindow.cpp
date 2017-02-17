#include "MainWindow.h"
#include <qinputdialog.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget = new RedBlackTreeWidget;
    mTree = new Xc::RedBlackTree<int>;
    widget->rTree() = mTree;

    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout *topLayout = new QHBoxLayout;

    QPushButton *button = new QPushButton("&Add Node");
    connect(button, &QPushButton::clicked, this, &MainWindow::addClicked);

    topLayout->addWidget(button);

    button = new QPushButton("&Erase Node");
    connect(button, &QPushButton::clicked, this, &MainWindow::eraseClicked);
    topLayout->addWidget(button);

    button = new QPushButton("&Random");
    connect(button, &QPushButton::clicked, this, &MainWindow::randomClicked);
    topLayout->addWidget(button);

    button = new QPushButton("&Show");
    connect(button, &QPushButton::clicked, this, &MainWindow::showClicked);
    topLayout->addWidget(button);

    layout->addLayout(topLayout);
    layout->addWidget(widget);

    QWidget *tmp = new QWidget;
    tmp->setLayout(layout);
    setCentralWidget(tmp);
    setGeometry(100, 100, 500, 500);

    srand(time(nullptr));

}

MainWindow::~MainWindow()
{
    delete mTree;
}

void MainWindow::addClicked()
{
    QInputDialog dialog;
    dialog.exec();
    int value = dialog.textValue().toInt();
    mTree->insert(value);
    widget->update();
}

void MainWindow::eraseClicked()
{
    QInputDialog dialog;
    dialog.exec();
    int value = dialog.textValue().toInt();
    mTree->erase(value);

    widget->update();
}

void MainWindow::randomClicked()
{
    static int num = 1;
    int times = 1;
    while (times--)
    {
        mTree->insert(rand());
    }

    widget->update();

    //    setWindowTitle(QString::number(mTree->height()));
}

void MainWindow::showClicked()
{
    QString str;
    for (Xc::RedBlackTree<int>::ConstantIterator itr = --mTree->end(); itr != mTree->end(); --itr)
    {
        str += QString::number(*itr) + " ";
    }
    QMessageBox::information(this, str, str);
    ; // do nothing
}
