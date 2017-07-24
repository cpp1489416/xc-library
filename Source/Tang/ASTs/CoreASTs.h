#pragma once

#include "../../Core/Core.h"
#include "../Token.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    using namespace XC;

    class AST;
    class Expression;
    class NumberExpression;
    class BinaryExpression;

    class IVisitor
    {
    public:
        virtual void Visit(Expression* node) = 0;
        virtual void Visit(NumberExpression* node) = 0;
        virtual void Visit(BinaryExpression* node) = 0;
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

    struct BinaryExpression : public Expression
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
        Token mOperatorToken;
        Pointer<Expression> mLeftExpression;
        Operator mOperator;
        Pointer<Expression> mRightExpression;
    };

} XC_END_NAMESPACE_1;