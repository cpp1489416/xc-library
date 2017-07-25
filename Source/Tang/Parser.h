#pragma once

#include "../Core/Core.h"
#include "Lexer.h"
#include "ASTs/CoreASTs.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    class Parser
    {
    public:
        Parser(Pointer<Lexer> lexer);

        Parser(std::string sourceCode);
        
    public:
        Pointer<Program> Parse();

        void PrintTokens();

    private:
        Pointer<Program> ParseProgram();

        Pointer<Statement> ParseStatement();
        
        Pointer<Expression> ParseAssign();

        void ParseAssignPlus(Pointer<AssignExpression> leftParsed);

        Pointer<Expression> ParseGreater();

        Pointer<Expression> ParseGreaterPlus(Pointer<Expression> leftParsed);

        // E -> T E1
        Pointer<Expression> ParsePlus(); 

        // E1 -> + T E1 | - T E1 | null
        Pointer<Expression> ParsePlusPlus(Pointer<Expression> leftParsed);

        // T -> F T1
        Pointer<Expression> ParseMultiply();

        // T1 -> * F T1 | / F T1 | null
        Pointer<Expression> ParseMultiplyPlus(Pointer<Expression> leftParsed);

        // F -> (E) | number
        Pointer<Expression> ParseBracket();

    private:
        Pointer<Lexer> mLexer;
    };

} XC_END_NAMESPACE_1;