#pragma once

#include "../../Core/Core.h"
#include "../Token.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    using namespace XC;

    class AST;
    class Expression;

    class NumberExpression;
    class VariableExpression;
    class CalculateExpression;
    class CompareExpression;
    class AssignExpression;

    class Statement;
    class ExpressionStatement;
    class BlockStatement;
    class WhileStatement;

    class Program;

    class IVisitor
    {
    public:
        virtual void Visit(NumberExpression* node)
        {
        }

        virtual void Visit(VariableExpression* node)
        {
        }

        virtual void Visit(CalculateExpression* node)
        {
        }

        virtual void Visit(CompareExpression* node)
        {
        }

        virtual void Visit(AssignExpression* node)
        {
        }

        virtual void Visit(ExpressionStatement* node)
        {
        }

        virtual void Visit(BlockStatement* node)
        {
        }

        virtual void Visit(WhileStatement* node)
        {
        }

        virtual void Visit(Program* node)
        {
        }
    };

    class AST
    {
    public:
        virtual void Accept(IVisitor* visitor) = 0;
    };

    class Expression : public AST
    {
    };

    class NumberExpression : public Expression
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Token mToken;
        double mValue;
    };

    class VariableExpression : public Expression
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Token mToken;
        String mName;
    };

    struct CalculateExpression : public Expression
    {
    public:
        enum class Operator
        {
            Plus, // +
            Minus, // -
            Multiply, // *
            Divide, // /
        };

    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Pointer<Expression> mLeftExpression;
        Operator mOperator;
        Pointer<Expression> mRightExpression;
    };

    class CompareExpression : public Expression
    {
    public:
        enum class Operator
        {
            Greater,
            Lesser,
        };

    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Pointer<Expression> mLeftExpression;
        Operator mOperator;
        Pointer<Expression> mRightExpression;
    };

    struct AssignExpression : public Expression
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Token mOperatorToken;
        Pointer<Expression> mLeftExpression;
        Pointer<Expression> mRightExpression;
    };

    class Statement : public AST
    {
    };

    class ExpressionStatement : public Statement
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Pointer<Expression> mExpression;

    };

    class BlockStatement : public Statement
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Array<Pointer<Statement> > mStatements;
    };

    class WhileStatement : public Statement
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Pointer<Expression> mConditionExpression;
        Pointer<Statement> mBodyStatement;
    };

    class Program : public AST
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Array<Pointer<Statement> > mStatements;
    };

} XC_END_NAMESPACE_1;