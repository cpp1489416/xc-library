#pragma once

#include <iostream>
#include <sstream>
#include "../ASTs/CoreASTs.h"
#include "../ASTs/Environment.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    class ASTSolver : public IVisitor
    {
    public:
        void Visit(Program* node) override
        {
            for (auto itr : node->mASTs)
            {
                itr->Accept(this);
            }
        }

        void Visit(ExpressionStatement* node) override
        {
            node->mExpression->Accept(this);
        }

        void Visit(BlockStatement* node) override
        {
            for (auto itr : node->mStatements)
            {
                itr->Accept(this);
            }
        }

        void Visit(IfStatement* node) override
        {
            node->mConditionExpression->Accept(this);
            if (mLastResult != 0.0)
            {
                node->mMainStatement->Accept(this);
            }
            else
            {
                node->mElseStatement->Accept(this);
            }
        }

        void Visit(WhileStatement* node) override
        {
            while (true)
            {
                node->mConditionExpression->Accept(this);
                if (mLastResult == 0.0)
                {
                    break;
                }
                else
                {
                    node->mBodyStatement->Accept(this);
                }
            }
        }

        void Visit(ForStatement* node) override
        {
            node->mBeginStatement->Accept(this);
            while (true)
            {
                node->mConditionExpression->Accept(this);
                if (mLastResult == 0.0)
                {
                    break;
                }

                node->mBodyStatement->Accept(this);
                node->mAfterExpression->Accept(this);
            }
        }

        void Visit(NumberExpression* node) override
        {
            mLastResult = node->mValue;
        }

        void Visit(VariableExpression* node) override
        {
            mLastResult = mEnvironment.GetVariableSymbol(node->mName)->mValue;
            mLastVariableName = node->mName;
        }

        void Visit(CalculateExpression* node) override
        {
            node->mLeftExpression->Accept(this);
            double leftResult = mLastResult;
            node->mRightExpression->Accept(this);
            double rightResult = mLastResult;
            switch (node->mOperator)
            {
            case CalculateExpression::Operator::Plus:
                mLastResult = leftResult + rightResult;
                break;
            case CalculateExpression::Operator::Minus:
                mLastResult = leftResult - rightResult;
                break;
            case CalculateExpression::Operator::Multiply:
                mLastResult = leftResult * rightResult;
                break;
            case CalculateExpression::Operator::Divide:
                mLastResult = leftResult / rightResult;
                break;
            default:
                break;
            }
        }

        void Visit(CompareExpression* node) override
        {
            node->mLeftExpression->Accept(this);
            double leftResult = mLastResult;
            node->mRightExpression->Accept(this);
            double rightResult = mLastResult;
            switch (node->mOperator)
            {
            case  CompareExpression::Operator::Greater:
                mLastResult = leftResult > rightResult ? 1 : 0;
                break;
            case CompareExpression::Operator::Lesser:
                mLastResult = leftResult < rightResult ? 1 : 0;
                break;
            default:
                break;
            }
        }

        void Visit(AssignExpression* node) override
        {
            node->mLeftExpression->Accept(this);
            std::string str = mLastVariableName;
            node->mRightExpression->Accept(this);
            std::cout << str << std::endl;
            mEnvironment.GetVariableSymbol(str)->mValue = mLastResult;
        }

        void Visit(FunctionExpression* node) override
        {
            Pointer<FunctionSymbol> s = mEnvironment.mStringToFunctionSymbol[node->mName];
            for (int i = 0; i < node->mArgumentList.GetSize(); ++i)
            {
                s->mArgumentList[i] = node->mArgumentList[i];
            }
            s->Accept(this);
        }

        void Visit(VariableDefinition* node) override
        {
            Pointer<VariableSymbol> s(new VariableSymbol());
            mLastResult = 0.0;
            node->mValueExpression->Accept(this);
            s->mValue = mLastResult;
            mEnvironment.AddVariableSymbol(node->mName, s);
        }

        void Visit(FunctionDefinition* node) override
        {
            Pointer<FunctionSymbol> s(new FunctionSymbol(node->mParemeterList, node->mBlockStatement));
            s->mParemeterList = node->mParemeterList;
            s->mBlockStatement = node->mBlockStatement;
            mEnvironment.AddFunctionSymbol(node->mName, s);
        }

        void Visit(FunctionSymbol* node) override
        {
            mEnvironment.Push();
            for (int i = 0; i < node->mParemeterList.GetSize(); ++i)
            {
                if (node->mParemeterList[i]->mIsByReference)
                {
                    node->mArgumentList[i]->Accept(this);
                    mEnvironment.AddVariableSymbol(
                        node->mParemeterList[i]->mVariableExpression->mName,
                        mEnvironment.GetVariableSymbol(mLastVariableName)
                    );
                }
                else
                {
                    node->mArgumentList[i]->Accept(this);
                    Pointer<VariableSymbol> v(new VariableSymbol());
                    v->mValue = mLastResult;
                    mEnvironment.AddVariableSymbol(
                        node->mParemeterList[i]->mVariableExpression->mName,
                        v
                    );
                }
            }
            node->mBlockStatement->Accept(this);
            mEnvironment.Pop();
        }

    public:
        auto GetVarialbeValues()
        {
            return 0;// return mVariablesValues;
        }

        auto GetResult()
        {
            std::string ans;
            std::stringstream s(ans);
            for (auto itr : mEnvironment.mStringToVariableSymbolStack[0])
            {
                s << itr.first << std::string(": ") << (itr.second->mValue) << "\n";
            }

            return s.str();
        }

    private:
        Environment mEnvironment;
        String mLastVariableName;
        double mLastResult = 0.0;
    };
} XC_END_NAMESPACE_1;