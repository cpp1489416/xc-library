#pragma once

#include "../../Core/Core.h"
#include "../Token.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    using namespace XC;

    class IVisitable;

    class AST;

    class Expression;
    class EmptyExpression;
    class NumberExpression;
    class VariableExpression;
    class FunctionExpression;
    class CalculateExpression;
    class CompareExpression;
    class AssignExpression;

    class Statement;
    class ExpressionStatement;
    class BlockStatement;
    class IfStatement;
    class WhileStatement;
    class ForStatement;

    class VariableDefinition;
    class ParameterDefinition;
    class FunctionDefinition;
    using ParameterList = XC::Array<XC::Pointer<ParameterDefinition> >;
    using ArgumentList = XC::Array<XC::Pointer<Expression> >;

    class Program;

    class Symbol;
    class VariableSymbol;
    class FunctionSymbol;

    class IVisitor
    {
    public:
        virtual void Visit(NumberExpression* node) {}

        virtual void Visit(EmptyExpression* node) {}

        virtual void Visit(VariableExpression* node) {}

        virtual void Visit(CalculateExpression* node) {}

        virtual void Visit(CompareExpression* node) {}

        virtual void Visit(AssignExpression* node) {}

        virtual void Visit(ExpressionStatement* node) {}

        virtual void Visit(BlockStatement* node) {}

        virtual void Visit(IfStatement* node) {}

        virtual void Visit(WhileStatement* node) {}

        virtual void Visit(ForStatement* node) {}

        virtual void Visit(FunctionExpression* node) {}

        virtual void Visit(VariableDefinition* node) {}

        virtual void Visit(FunctionDefinition* node) {}

        virtual void Visit(Program* node) {}

        virtual void Visit(VariableSymbol *node) {}

        virtual void Visit(ParameterDefinition* node) {}

        virtual void Visit (FunctionSymbol *node) {}
    };

    class IVisitable
    {
    public:
        virtual void Accept(IVisitor* visitor) = 0;
    };

    class AST : public IVisitable
    {
    };

    class Expression : public AST
    {
    };

    class EmptyExpression : public Expression
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }
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

    class FunctionExpression : public Expression
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        String mName;
        ArgumentList mArgumentList;
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

    class IfStatement : public Statement
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Pointer<Expression> mConditionExpression;
        Pointer<Statement> mMainStatement;
        Pointer<Statement> mElseStatement;
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

    class ForStatement : public Statement
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Pointer<Expression> mBeginStatement;
        Pointer<Expression> mConditionExpression;
        Pointer<Expression> mAfterExpression;
        Pointer<Statement> mBodyStatement;
    };

    class VariableDefinition : public AST
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        String mName;
        Pointer<Expression> mValueExpression;
    };

    class ParameterDefinition : public AST
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Pointer<VariableExpression> mVariableExpression;
        bool mIsByReference = false;
    };

    class FunctionDefinition : public AST
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        String mName;
        ParameterList mParemeterList;
        Pointer<BlockStatement> mBlockStatement;
    };

    class Program : public AST
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        Array<Pointer<AST> > mASTs;
    };

} XC_END_NAMESPACE_1;
