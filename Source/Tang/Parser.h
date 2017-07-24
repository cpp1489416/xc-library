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
        Pointer<Expression> Parse();

    private:
        // E -> T E1
        Pointer<Expression> ParseE(); 

        // E1 -> + T E1 | - T E1 | null
        Pointer<Expression> ParseE1(Pointer<Expression> leftParsed);

        // T -> F T1
        Pointer<Expression> ParseT();

        // T1 -> * F T1 | / F T1 | null
        Pointer<Expression> ParseT1(Pointer<Expression> leftParsed);

        // F -> (E) | number
        Pointer<Expression> ParseF();

    private:
        Pointer<Lexer> mLexer;
    };

} XC_END_NAMESPACE_1;