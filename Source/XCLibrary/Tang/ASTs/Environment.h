#pragma once

#include "CoreASTs.h"
#include <Core/Containers/Array.h>

XC_BEGIN_NAMESPACE_1(Tang)
{
    class Type
    {
    public:
        enum class TypeName
        {
            None, IntegerType, RealType, FunctionType,
        };

    public:
        virtual TypeName GetType()
        {
            return TypeName::None;
        }
    };

    class BuiltInType : public Type
    {
    };

    class IntegerType : public BuiltInType
    {
    public:
        Type::TypeName GetType() override
        {
            return Type::TypeName::IntegerType;
        }
    };

    class RealType : public BuiltInType
    {
    public:
        Type::TypeName GetType() override
        {
            return Type::TypeName::RealType;
        }
    };

    class FunctionType : public Type
    {
    public:
        Type::TypeName GetType() override
        {
            return Type::TypeName::FunctionType;
        }
    };

    class Symbol
    {
    public:
        virtual Type GetType() = 0;

        virtual XC::String GetName() = 0;
    };

    class IntegerSymbol : public Symbol
    {
    public:
        Type GetType() override
        {
            return IntegerType();
        }

        XC::String GetName() override
        {
            return mName;
        }

    public:
        XC::String mName;
        int mValue;
    };

    class FunctionSymbol : public Symbol
    {
    public:
        Type GetType() override
        {
            return FunctionType();
        }

        XC::String GetName() override
        {
            return mName;
        }

    public:
        String mName;
        FunctionDefinition mDefinition;
        Pointer<IScope> mScope;
    };

    class IScope
    {
    public:
        virtual Pointer<Symbol> Get(String name) = 0;

        virtual void Define(String name, Pointer<Symbol> symbol) = 0;
    };

    class LocalScope : public IScope
    {
    public:
        LocalScope(Pointer<IScope> parent = Pointer<IScope>(nullptr)) : mParent(parent)
        {
        }

    public:
        Pointer<Symbol> Get(String name) override
        {
            if (mSymbols.count(name))
            {
                return mSymbols[name];
            }
            else
            {
                return mParent->Get(name);
            }
        }

        void Define(String name, Pointer<Symbol> symbol)
        {
            mSymbols[name] = symbol;
        }

    public:
        Pointer<IScope> mParent;
        std::map<String, Pointer<Symbol> > mSymbols;
    };

} XC_END_NAMESPACE_1;