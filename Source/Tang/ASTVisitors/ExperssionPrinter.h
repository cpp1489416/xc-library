#pragma once

#include <iostream>
#include "../ASTs/CoreASTs.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    class ExpressionPrinter : public IVisitor
    {
    public:
        void Visit(Expression* node) override
        {
            std::cout << "geg";
        }

        void Visit(NumberExpression* node) override
        {
            std::cout << node->mValue;
        }

        void Visit(BinaryExpression* node) override
        {
            std::cout << "(";
            node->mLeftExpression->Accept(this);
            std::string s;
            switch (node->mOperator)
            {
            case BinaryExpression::Operator::Plus:
                s = "+";
                break;
            case BinaryExpression::Operator::Minus:
                s = "-";
                break;
            case BinaryExpression::Operator::Multiply:
                s = "*";
                break;
            case BinaryExpression::Operator::Divide:
                s = "/";
                break;
            default:
                break;
            }

            std::cout << " " << s << " ";
            node->mRightExpression->Accept(this);
            std::cout << ")";
        }
    };

    class ExpressionAnswer : public IVisitor
    {
    public:
        void Visit(Expression* node) override
        {

        }

        void Visit(NumberExpression* node) override
        {
            mResult = node->mValue;
        }

        void Visit(BinaryExpression* node) override
        {
            node->mLeftExpression->Accept(this);
            double leftResult = mResult;
            node->mRightExpression->Accept(this);
            double rightResult = mResult;
            switch (node->mOperator)
            {
            case BinaryExpression::Operator::Plus:
                mResult = leftResult + rightResult;
                break;
            case BinaryExpression::Operator::Minus:
                mResult = leftResult - rightResult;
                break;
            case BinaryExpression::Operator::Multiply:
                mResult = leftResult * rightResult;
                break;
            case BinaryExpression::Operator::Divide:
                mResult = leftResult / rightResult;
                break;
            default:
                break;
            }
        }

    public:
        double GetResult()
        {
            return mResult;
        }// = 0.0;

    private:
        double mResult;
    };
} XC_END_NAMESPACE_1;