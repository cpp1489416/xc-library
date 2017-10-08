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

    void Print(std::map<XC::String, double>& map)
    {
        for (auto itr : map)
        {
            std::cout << itr.first << " = " << itr.second << std::endl;
        }
    }
}

int main()
{
 //   Tang::Lexer l("1 + 2 / 3 * 4");
//    std::cout << "ger" << std::endl;
  //  PrintTokens(l);
    Tang::Parser parser(
        "x = 5;"
    "z = 0;"

    "while (x > 0)"
    "{"
     "   z = z + x;"
     "   x = x - 1;"
    "}"
    );
    parser.PrintTokens();
    auto ans = parser.Parse();
    Tang::ProgramPrinter p;
    ans->Accept(new Tang::ProgramPrinter());
    Tang::ExpressionAnswer a;
    ans->Accept(&a);
    Print(a.GetVarialbeValues());
//    std::cout << std::endl << a.GetResult();
    system("Pause");
    return 0;
}

