#include "TangQTTest.h"

#include <Core/Core.h>
#include <GUI/GUI.h>
#include <Tang/Tang.h>
#include <Tang/ASTVisitors/ExperssionPrinter.h>
#include <qmessagebox.h>

TangQTTest::TangQTTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    mSourceWidget = ui.plainTextEdit;
    mResultWidget = ui.plainTextEdit_2;
    connect(ui.actionRun, &QAction::triggered, this, &TangQTTest::Run);
//    ui.menuRun->addAction("run");
}

void TangQTTest::Run()
{
    std::string source = mSourceWidget->toPlainText().toStdString();
    Tang::Parser parser(source);
    auto tree = parser.Parse();
    Tang::ExpressionAnswer a;
    tree->Accept(&a);
    QString ans = QString::fromStdString(a.GetResult());
    mResultWidget->setPlainText(ans);
 //   QMessageBox::information(this, mSourceWidget->toPlainText(), mSourceWidget->toPlainText());
}