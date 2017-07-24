// TangTestConsole.cpp : 定义控制台应用程序的入口点。
//

#include <cstdlib>
#include <Tang/Tang.h>
#include <Tang/ASTVisitors/ExperssionPrinter.h>
#include "stdafx.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    void Main()
    {
    }
} XC_END_NAMESPACE_2;

namespace
{
    void PrintTokens(Tang::Lexer lexer)
    {
        while (lexer.IsHasNext())
        {
            Tang::Token token = lexer.GetNextToken();
            std::cout << token.GetString() << " " << (int)token.GetType() << std::endl;
        }
    }
}

int main()
{
 //   Tang::Lexer l("1 + 2 / 3 * 4");
//    std::cout << "ger" << std::endl;
  //  PrintTokens(l);
    Tang::Parser parser("1 + 2 / 3 * 4");
    auto ans = parser.Parse();
    Tang::ExpressionPrinter p;
    ans->Accept(new Tang::ExpressionPrinter());
    Tang::ExpressionAnswer a;
    ans->Accept(&a);
    std::cout << std::endl << a.GetResult();
    system("Pause");
    return 0;
}

