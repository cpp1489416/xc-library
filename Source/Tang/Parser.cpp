#include "Parser.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    Parser::Parser(Pointer<Lexer> lexer) :
        mLexer(lexer)
    {
    }

    Parser::Parser(std::string sourceCode) :
        mLexer(new Lexer(sourceCode))
    {
    }

    Pointer<Expression> Parser::Parse()
    {
        mLexer->MoveToFront();
        return ParseE();
    }

    Pointer<Expression> Parser::ParseE()
    {
        Pointer<Expression> leftChild = ParseT();
        return ParseE1(leftChild);
    }

    Pointer<Expression> Parser::ParseE1(Pointer<Expression> leftParsed)
    {
        Token lookAhead = mLexer->LookAhead();
        std::string string = lookAhead.GetString();
        if (string == "+" || string == "-")
        {
            mLexer->GetNextToken();
            BinaryExpression* node = new BinaryExpression();
            node->mLeftExpression = leftParsed;
            node->mOperator = string == "+" ? BinaryExpression::Operator::Plus : BinaryExpression::Operator::Minus;
            node->mRightExpression = ParseT();
            return ParseE1(Pointer<Expression>(node));
        }
        else
        {
            return leftParsed;
        }
    }

    Pointer<Expression> Parser::ParseT()
    {
        Pointer<Expression> leftChild = ParseF();
        return ParseT1(leftChild);
    }

    Pointer<Expression> Parser::ParseT1(Pointer<Expression> leftParsed)
    {
        Token lookAhead = mLexer->LookAhead();
        std::string string = lookAhead.GetString();
        if (string == "*" || string == "/")
        {
            mLexer->GetNextToken();
            BinaryExpression* node = new BinaryExpression();
            node->mLeftExpression = leftParsed;
            node->mOperator = string == "*" ? BinaryExpression::Operator::Multiply : BinaryExpression::Operator::Divide;
            node->mRightExpression = ParseF();
            return ParseT1(Pointer<Expression>(node));
        }
        else
        {
            return leftParsed;
        }
    }

    Pointer<Expression> Parser::ParseF()
    {
        if (mLexer->LookAhead().GetString() == "(")
        {
            mLexer->GetNextToken();
            Pointer<Expression> ans = ParseE();
            mLexer->GetNextToken();
            return ans;
        }
        else
        {
            NumberExpression * ans = new NumberExpression();
            ans->mToken = mLexer->GetNextToken();
            ans->mValue = atoi(ans->mToken.GetString().c_str());
            return Pointer<Expression>(ans);
        }
    }


} XC_END_NAMESPACE_1;