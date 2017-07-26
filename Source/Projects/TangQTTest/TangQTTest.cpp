#include "TangQTTest.h"

#include <Core/Core.h>
#include <GUI/GUI.h>
#include <Tang/Tang.h>
#include <Tang/ASTVisitors/ASTStringer.h>
#include <Tang/ASTVisitors/ASTSolver.h>
#include <qmessagebox.h>

TangQTTest::TangQTTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    mSourceWidget = ui.plainTextEdit;
    mResultWidget = ui.plainTextEdit_2;
    mStringerWidget = ui.plainTextEdit_3;
    connect(ui.actionRun, &QAction::triggered, this, &TangQTTest::Run);
//    ui.menuRun->addAction("run");
}

void TangQTTest::Run()
{
    std::string source = mSourceWidget->toPlainText().toStdString();
    Tang::Parser parser(source);
    auto tree = parser.Parse();
    Tang::ASTSolver a;
    tree->Accept(&a);
    QString ans = QString::fromStdString(a.GetResult());
    mResultWidget->setPlainText(ans);
    Tang::ASTStringer stringer;
    tree->Accept(&stringer);
    mStringerWidget->setPlainText(QString::fromStdString(stringer.GetResult()));
 //   QMessageBox::information(this, mSourceWidget->toPlainText(), mSourceWidget->toPlainText());
}