#pragma once

#include "CoreASTs.h"
#include <Core/Containers/Array.h>

XC_BEGIN_NAMESPACE_1(Tang)
{
    class Symbol : public IVisitable
    {
    };

    class VariableSymbol : public Symbol
    {
    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        double mValue;
    };

    class FunctionSymbol : public Symbol
    {
    public:
        FunctionSymbol(ParameterList parameterList, Pointer<BlockStatement> blockStatement)
        {
            mParemeterList = parameterList;
            mBlockStatement = blockStatement;
            for (int i = 0; i < mParemeterList.GetSize(); ++i)
            {
                mArgumentList.PushBack(Pointer<Expression>(nullptr));
            }
        }

    public:
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }

    public:
        ParameterList mParemeterList;
        Pointer<BlockStatement> mBlockStatement;
        ArgumentList mArgumentList;
    };

    class Environment
    {
    public:
        Environment()
        {
            Push();
        }

    public:
        void AddFunctionSymbol(XC::String name, Pointer<FunctionSymbol> symbol)
        {
            mStringToFunctionSymbol[name] = symbol;
        }

        void AddVariableSymbol(XC::String name, Pointer<VariableSymbol> symbol)
        {
            mStringToVariableSymbolStack.GetBack()[name] = symbol;
        }

        Pointer<VariableSymbol> GetVariableSymbol(XC::String name)
        {
            for (XC::xsize i = mStringToVariableSymbolStack.GetSize() - 1; i >= 0; --i)
            {
                if (mStringToVariableSymbolStack[i].count(name))
                {
                    return mStringToVariableSymbolStack[i][name];
                }
            }

            return Pointer<VariableSymbol>(nullptr);
        }

        void Push() 
        {
            mStringToVariableSymbolStack.PushBack(std::map<XC::String, Pointer<VariableSymbol> >());//))
        }

        void Pop() 
        {
            mStringToVariableSymbolStack.PopBack();
        }

    public:
        std::map<XC::String, Pointer<FunctionSymbol> > mStringToFunctionSymbol;
        XC::Array<std::map<XC::String, Pointer<VariableSymbol> > > mStringToVariableSymbolStack;
    };


} XC_END_NAMESPACE_1;