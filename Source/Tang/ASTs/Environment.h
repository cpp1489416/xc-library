#pragma once

#include "CoreASTs.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    class Symbol : public IVisitable
    {
    public:

    };

    class FunctionSymbol : public Symbol
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

        void SetFunctionDefinition(Pointer<FunctionDefinition> functionDefinition)
        {
            mFunctionDefinition = functionDefinition;
            mArgumentList.Resize(mFunctionDefinition->mParemeterList.GetSize());
        }

    public:
        Pointer<FunctionDefinition> mFunctionDefinition;
        ArgumentList mArgumentList;
    };

    class Environment
    {
    public:
        std::map<XC::String, Symbol> mStringToSymbol;
    };

  
} XC_END_NAMESPACE_1;