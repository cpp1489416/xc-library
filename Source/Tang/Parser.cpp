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
            if (mLexer->LookAhead().GetString() == "function")
            {
                ans->mASTs.PushBack(ParseFunctionDeclaration());
            }
            else
            {
                ans->mASTs.PushBack(ParseStatement());
            }
        }

        return ans;
    }

    Pointer<FunctionDefinition> Parser::ParseFunctionDeclaration()
    {
        Pointer<FunctionDefinition> ans(new FunctionDefinition());
        mLexer->GetNextToken(); // function
        ans->mName = mLexer->GetNextToken().GetString();
        mLexer->GetNextToken(); // (
        if (mLexer->LookAhead().GetString() != ")")
        {
            ans->mParemeterList.PushBack(ParseVariable());
            while (mLexer->LookAhead().GetString() == ",")
            {
                mLexer->GetNextToken(); // ,
                ans->mParemeterList.PushBack(ParseVariable());
            }
        }
        mLexer->GetNextToken(); // )
        ans->mBlockStatement = ParseBlockStatement();
        return ans;
    }

    Pointer<Statement> Parser::ParseStatement()
    {
        Token lookAhead = mLexer->LookAhead();
        if (lookAhead.GetString() == "if")
        {
            return ParseIfStatement();
        }
        else if (lookAhead.GetString() == "while")
        {
            return ParseWhileStatement();
        }
        else if (lookAhead.GetString() == "for")
        {
            return ParseForStatement();
        }
        else if (lookAhead.GetString() == "{")
        {
            return ParseBlockStatement();
        }
        else
        {
            return ParseExpressionStatement();
        }
    }

    Pointer<ExpressionStatement> Parser::ParseExpressionStatement()
    {
        Pointer<ExpressionStatement> ans(new ExpressionStatement());
        ans->mExpression = ParseAssign();
        mLexer->GetNextToken();
        return ans;
    }

    Pointer<BlockStatement> Parser::ParseBlockStatement()
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

    Pointer<IfStatement> Parser::ParseIfStatement()
    {
        Pointer<IfStatement> ans(new IfStatement);
        mLexer->GetNextToken(); // if
        mLexer->GetNextToken(); // (
        ans->mConditionExpression = ParseAssign();
        mLexer->GetNextToken(); // )
        ans->mMainStatement = ParseStatement();
        if (mLexer->LookAhead().GetString() == "else")
        {
            mLexer->GetNextToken();
            ans->mElseStatement = ParseStatement();
        }
        else
        {
            Pointer<ExpressionStatement> elseStatement(new ExpressionStatement());
            elseStatement->mExpression = Pointer<Expression>(new EmptyExpression());
            ans->mElseStatement = elseStatement;
        }

        return ans;
    }

    Pointer<WhileStatement> Parser::ParseWhileStatement()
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

    Pointer<ForStatement> Parser::ParseForStatement()
    {
        Pointer<ForStatement> ans(new ForStatement());
        mLexer->GetNextToken(); // for
        mLexer->GetNextToken(); // (
        ans->mBeginStatement = ParseAssign();
        mLexer->GetNextToken(); // ;
        ans->mConditionExpression = ParseAssign();
        mLexer->GetNextToken(); // ;
        ans->mAfterExpression = ParseAssign();
        mLexer->GetNextToken(); // )
        ans->mBodyStatement = ParseStatement();
        return ans;
    }

    Pointer<Expression> Parser::ParseExpression()
    {
        return ParseAssign();
    }

    Pointer<Expression> Parser::ParseAssign()
    {
        if (mLexer->LookAhead().GetString() == ";" || mLexer->LookAhead().GetString() == ")")
        {
            return Pointer<Expression>(new EmptyExpression());
        }
        else
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
        Pointer<Expression> leftChild = ParseSmallExpression();
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
            node->mRightExpression = ParseSmallExpression();
            return ParseMultiplyPlus(Pointer<Expression>(node));
        }
        else
        {
            return leftParsed;
        }
    }

    Pointer<Expression> Parser::ParseSmallExpression()
    {
        if (mLexer->LookAhead().GetString() == "(")
        {
            return ParseBracket();
        }
        else if (mLexer->LookAhead().GetType() == Token::Type::Number)
        {
            return ParseNumber();
        }
        else if (mLexer->LookAhead(2).GetString() == "(")
        {
            return ParseFunctionExpression();
        }
        else
        {
            return ParseVariable();
        }
    }

    Pointer<Expression> Parser::ParseBracket()
    {
        mLexer->GetNextToken(); // (
        Pointer<Expression> ans = ParseExpression();
        mLexer->GetNextToken(); // )
        return ans;
    }

    Pointer<NumberExpression> Parser::ParseNumber()
    {
        Token token = mLexer->GetNextToken();
        NumberExpression* ans = new NumberExpression();
        ans->mToken = token;
        ans->mValue = atoi(ans->mToken.GetString().c_str());
        return Pointer<NumberExpression>(ans);
    }

    Pointer<VariableExpression> Parser::ParseVariable()
    {
        Token token = mLexer->GetNextToken();
        VariableExpression* ans = new VariableExpression();
        ans->mToken = token;
        ans->mName = token.mString;
        return Pointer<VariableExpression>(ans);
    }

    Pointer<FunctionExpression> Parser::ParseFunctionExpression()
    {
        Pointer<FunctionExpression> ans(new FunctionExpression());
        ans->mName = mLexer->GetNextToken().GetString();

        mLexer->GetNextToken(); // (
        if (mLexer->LookAhead().GetString() != ")")
        {
            ans->mArgumentList.PushBack(ParseExpression());
            while (mLexer->LookAhead().GetString() == ",")
            {
                mLexer->GetNextToken();
                ans->mArgumentList.PushBack(ParseExpression());
            }
        }

        mLexer->GetNextToken(); // )
        return ans;
    }

} XC_END_NAMESPACE_1;