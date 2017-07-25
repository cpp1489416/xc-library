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

    Pointer<Program> Parser::Parse()
    {
        mLexer->MoveToFront();
        return ParseProgram();
    }

    void Parser::PrintTokens()
    {
        mLexer->MoveToFront();
        while (mLexer->IsHasNext())
        {
            std::cout << mLexer->GetNextToken().GetString() << std::endl;
        }
    }

    Pointer<Program> Parser::ParseProgram()
    {
        Pointer<Program> ans(new Program);
        while (mLexer->LookAhead().GetType() != Token::Type::End)
        {
            ans->mStatements.PushBack(ParseStatement());
        }

        return ans;
    }

    Pointer<Statement> Parser::ParseStatement()
    {
        Token lookAhead = mLexer->LookAhead();
        if (lookAhead.GetString() == "while")
        {
            Pointer<WhileStatement> ans(new WhileStatement());
            mLexer->GetNextToken(); // while
            std::cout << mLexer->LookAhead().GetString() << std::endl;
            mLexer->GetNextToken(); // (
            ans->mConditionExpression = ParseAssign();
            std::cout << mLexer->LookAhead().GetString() << std::endl;
            mLexer->GetNextToken(); // )
            std::cout << mLexer->LookAhead().GetString() << std::endl;
            ans->mBodyStatement = ParseStatement();
            return ans;
        }
        else if (lookAhead.GetString() == "{")
        {
            Pointer<BlockStatement> ans(new BlockStatement());
            mLexer->GetNextToken(); // {
            while (mLexer->LookAhead().GetString() != "}")
            {
                ans->mStatements.PushBack(ParseStatement());
                std::cout << mLexer->LookAhead().GetString() << std::endl;
            }

            mLexer->GetNextToken(); // {
            return ans;
        }
        else
        {
            Pointer<ExpressionStatement> ans(new ExpressionStatement());
            ans->mExpression = ParseAssign();
            mLexer->GetNextToken();
            return ans;
        }
    }

    Pointer<Expression> Parser::ParseAssign()
    {
        Pointer<Expression> leftChild = ParseGreater();

        std::string string = mLexer->LookAhead().GetString();

        if (string == "=")
        {
            mLexer->GetNextToken();
            Pointer<AssignExpression> ans(new AssignExpression());
            ans->mLeftExpression = leftChild;
            ans->mRightExpression = ParseGreater();
            ParseAssignPlus(ans);
            return ans;
        }
        else
        {
            return leftChild;
        }
    }

    void Parser::ParseAssignPlus(Pointer<AssignExpression> leftParsed)
    {
        Token lookAhead = mLexer->LookAhead();
        std::string string = lookAhead.GetString();
        if (string == "=")
        {
            mLexer->GetNextToken();
            Pointer<AssignExpression> node(new AssignExpression());
            node->mLeftExpression = leftParsed->mRightExpression;
            node->mRightExpression = ParseGreater();
            leftParsed->mRightExpression = node;
            ParseAssignPlus(node);
        }
        else
        {
            return;
        }
    }

    Pointer<Expression> Parser::ParseGreater()
    {
        Pointer<Expression> leftChild = ParsePlus();
        return ParseGreaterPlus(leftChild);
    }

    Pointer<Expression> Parser::ParseGreaterPlus(Pointer<Expression> leftParsed)
    {
        Token lookAhead = mLexer->LookAhead();
        std::string string = lookAhead.GetString();
        if (string == ">" || string == "<")
        {
            mLexer->GetNextToken();
            CompareExpression* node = new CompareExpression();
            node->mLeftExpression = leftParsed;
            node->mOperator = string == ">" ? CompareExpression::Operator::Greater : CompareExpression::Operator::Lesser;
            node->mRightExpression = ParsePlus();
            return ParsePlusPlus(Pointer<Expression>(node));
        }
        else
        {
            return leftParsed;
        }
    }

    Pointer<Expression> Parser::ParsePlus()
    {
        Pointer<Expression> leftChild = ParseMultiply();
        return ParsePlusPlus(leftChild);
    }

    Pointer<Expression> Parser::ParsePlusPlus(Pointer<Expression> leftParsed)
    {
        Token lookAhead = mLexer->LookAhead();
        std::string string = lookAhead.GetString();
        if (string == "+" || string == "-")
        {
            mLexer->GetNextToken();
            CalculateExpression* node = new CalculateExpression();
            node->mLeftExpression = leftParsed;
            node->mOperator = string == "+" ? CalculateExpression::Operator::Plus : CalculateExpression::Operator::Minus;
            node->mRightExpression = ParseMultiply();
            return ParsePlusPlus(Pointer<Expression>(node));
        }
        else
        {
            return leftParsed;
        }
    }

    Pointer<Expression> Parser::ParseMultiply()
    {
        Pointer<Expression> leftChild = ParseBracket();
        return ParseMultiplyPlus(leftChild);
    }

    Pointer<Expression> Parser::ParseMultiplyPlus(Pointer<Expression> leftParsed)
    {
        Token lookAhead = mLexer->LookAhead();
        std::string string = lookAhead.GetString();
        if (string == "*" || string == "/")
        {
            mLexer->GetNextToken();
            CalculateExpression* node = new CalculateExpression();
            node->mLeftExpression = leftParsed;
            node->mOperator = string == "*" ? CalculateExpression::Operator::Multiply : CalculateExpression::Operator::Divide;
            node->mRightExpression = ParseBracket();
            return ParseMultiplyPlus(Pointer<Expression>(node));
        }
        else
        {
            return leftParsed;
        }
    }

    Pointer<Expression> Parser::ParseBracket()
    {
        if (mLexer->LookAhead().GetString() == "(")
        {
            mLexer->GetNextToken();
            Pointer<Expression> ans = ParseAssign();
            mLexer->GetNextToken();
            return ans;
        }
        else
        {
            Token token = mLexer->GetNextToken();
            if (token.mType == Token::Type::Number)
            {
                NumberExpression* ans = new NumberExpression();
                ans->mToken = token;
                ans->mValue = atoi(ans->mToken.GetString().c_str());
                return Pointer<Expression>(ans);
            }
            else
            {
                VariableExpression* ans = new VariableExpression();
                ans->mToken = token;
                ans->mName = token.mString;
                return Pointer<Expression>(ans);
            }
        }
    }


} XC_END_NAMESPACE_1;