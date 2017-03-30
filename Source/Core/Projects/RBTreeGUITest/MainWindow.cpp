#include "MainWindow.h"
#include <qlayout.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <cstdlib>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    QHBoxLayout* topLayout = new QHBoxLayout();
    mainLayout->addLayout(topLayout);
    mMainWidget = new MainWidget();
    mainLayout->addWidget(mMainWidget);
    setGeometry(0, 100, 1000, 800);

    QPushButton* button = new QPushButton("add");
    connect(button, &QPushButton::clicked, this, &MainWindow::AddClicked);
    topLayout->addWidget(button);

    button = new QPushButton("Erase Random");
    connect(button, &QPushButton::clicked, this, &MainWindow::EraseRandomClicked);
    topLayout->addWidget(button);

    button = new QPushButton("Erase");
    connect(button, &QPushButton::clicked, this, &MainWindow::EraseClicked);
    topLayout->addWidget(button);
}

MainWindow::~MainWindow()
{
}

void MainWindow::AddClicked()
{
    for (int i = 0; i < 100;++i)
    {
        mMainWidget->mTree.InsertUnique(-rand() % 1000);
        mMainWidget->update();
    }
    mMainWidget->TestNodesRelationship();
}

void MainWindow::EraseRandomClicked()
{
    auto itr = mMainWidget->mTree.GetBegin();
    ++itr;
    int val = itr.mNode->mValue;
    QMessageBox::information(this, QString::number(val), "ge4gg4e");
    mMainWidget->mTree.Erase(itr);
    mMainWidget->update();
    mMainWidget->TestNodesRelationship();
}

void MainWindow::EraseClicked()
{

}