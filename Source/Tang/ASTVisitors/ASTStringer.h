#pragma once

#include <iostream>
#include <sstream>
#include "../ASTs/CoreASTs.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    class ASTStringer : public IVisitor
    {
    public:
        void Visit(NumberExpression* node) override;

        void Visit(EmptyExpression* node) override;

        void Visit(VariableExpression* node) override;

        void Visit(CalculateExpression* node) override;

        void Visit(CompareExpression* node) override;

        void Visit(AssignExpression* node) override;

        void Visit(ExpressionStatement* node) override;

        void Visit(BlockStatement* node) override;

        void Visit(IfStatement* node) override;

        void Visit(WhileStatement* node) override;

        void Visit(ForStatement* node) override;

        void Visit(FunctionExpression* node) override;

        void Visit(FunctionDefinition* node) override;

        void Visit(Program* node) override;

        void Visit(FunctionSymbol *node) override;

    public:
        std::string GetResult()
        {
            return mStream.str();
        }

    private:
        XC::String mResult;
        std::stringstream mStream;
    };

} XC_END_NAMESPACE_1;