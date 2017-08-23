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

        Pointer<VariableDefinition> ParseVariableDefinition();

        Pointer<FunctionDefinition> ParseFunctionDefinition();

        Pointer<Statement> ParseStatement();

        Pointer<ExpressionStatement> ParseExpressionStatement();

        Pointer<BlockStatement> ParseBlockStatement();

        Pointer<IfStatement> ParseIfStatement();

        Pointer<WhileStatement> ParseWhileStatement();

        Pointer<ForStatement> ParseForStatement();

        Pointer<Expression> ParseExpression();
        
        Pointer<Expression> ParseAssign();

        void ParseAssignPlus(Pointer<AssignExpression> leftParsed);

        Pointer<Expression> ParseGreater();

        Pointer<Expression> ParseGreaterPlus(Pointer<Expression> leftParsed);

        Pointer<Expression> ParsePlus(); 

        Pointer<Expression> ParsePlusPlus(Pointer<Expression> leftParsed);

        Pointer<Expression> ParseMultiply();

        Pointer<Expression> ParseMultiplyPlus(Pointer<Expression> leftParsed);

        Pointer<Expression> ParseSmallExpression();

        Pointer<Expression> ParseBracket();

        Pointer<NumberExpression> ParseNumber();

        Pointer<VariableExpression> ParseVariable();

        Pointer<FunctionExpression> ParseFunctionExpression();

    private:
        Pointer<Lexer> mLexer;
    };

} XC_END_NAMESPACE_1;