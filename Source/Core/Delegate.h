#pragma once

#include "Containers/Array.h"
#include "Object.h"

namespace XC
{
    namespace Details
    {
        template <typename TReturnType, typename ... TArguments>
        class Function
        {
        public:
            virtual bool IsConstant() const = 0;
            virtual TReturnType Invoke(TArguments ...) const = 0;
        };

        // static function is global function or static member function
        template <typename TReturnType, typename ... TArguments>
        class StaticFunction : public Function<TReturnType, TArguments ...>
        {
        public:
            using FunctionPointer = TReturnType(*)(TArguments ...);

        public:
            StaticFunction(FunctionPointer function)
            {
                mFunctionPointer = function;
            }

        public:
            bool IsConstant() const override
            {
                return true;
            }

            TReturnType Invoke(TArguments ... arguments) const override
            {
                return (*mFunctionPointer)(arguments ...);
            }

        private:
            FunctionPointer mFunctionPointer;
        };

        template <typename TReturnType, typename ... TArguments>
        StaticFunction<TReturnType, TArguments ...> *
            CreateStaticFunction(TReturnType(*function)(TArguments ...))
        {
            return new StaticFunction<TReturnType, TArguments ...>(function);
        }

        template <bool TConstant, typename TReturnType, typename TClassType, typename ... TArguments>
        class MemberFunction;

        template <typename TReturnType, typename TClassType, typename ... TArguments>
        class MemberFunction<false, TReturnType, TClassType, TArguments ...> : public Function<TReturnType, TArguments ...>
        {
        public:
            using FunctionPointer = TReturnType(TClassType::*)(TArguments ...);

        public:
            MemberFunction(TClassType * className, FunctionPointer function)
            {
                mClassName = className;
                mFunctionPointer = function;
            }

        public:
            bool IsConstant() const override
            {
                return false;
            }

            TReturnType Invoke(TArguments ... arguments) const override
            {
                return (mClassName->*mFunctionPointer)(arguments ...);
            }

        private:
            TClassType * mClassName;
            FunctionPointer mFunctionPointer;
        };

        template <typename TReturnType, typename TClassType, typename ... TArguments>
        MemberFunction <false, TReturnType, TClassType, TArguments ...> *
            CreateMemberFunction(TClassType * className, TReturnType(TClassType::*function)(TArguments ...))
        {
            return new MemberFunction<false, TReturnType, TClassType, TArguments ...>(className, function);
        }

        template <typename TReturnType, typename TClassType, typename ... TArguments>
        class MemberFunction<true, TReturnType, TClassType, TArguments ...> : public Function<TReturnType, TArguments ...>
        {
        public:
            using FunctionPointer = TReturnType(TClassType::*)(TArguments ...) const;

        public:
            MemberFunction(TClassType * className, FunctionPointer function)
            {
                mClassName = className;
                mFunctionPointer = function;
            }

        public:
            bool IsConstant() const override
            {
                return true;
            }

            TReturnType Invoke(TArguments ... arguments) const override
            {
                return (mClassName->*mFunctionPointer)(arguments ...);
            }

        private:
            TClassType * mClassName;
            FunctionPointer mFunctionPointer;
        };

        template <typename TReturnType, typename TClassType, typename ... TArguments>
        MemberFunction <true, TReturnType, TClassType, TArguments ...> *
            CreateMemberFunction(TClassType * className, TReturnType(TClassType::*function)(TArguments ...) const)
        {
            return new MemberFunction<true, TReturnType, TClassType, TArguments ...>(className, function);
        }
    }

    template <typename TReturnType, typename ... TArguments>
    class Delegate;

    // return type is not void, only one function.
    template <typename TReturnType, typename ... TArguments>
    class Delegate
    {
    public:
        typedef Delegate<TReturnType, TArguments ...> Self;

    public:
        Delegate()
        {
            mFunction = nullptr;
        }

        Delegate(const Self *) = delete;

        ~Delegate()
        {
            RemoveAll();
        }

        Self & operator = (const Self &) = delete;

    public:
        void Add(TReturnType(*function)(TArguments ...))
        {
            mFunction = Details::CreateStaticFunction(function);
        }

        template <typename TClassType>
        void Add(TClassType * className, TReturnType(TClassType::*function)(TArguments ...))
        {
            mFunctions = Details::CreateMemberFunction(className, function);
        }

        template <typename TClassType>
        void Add(TClassType * className, TReturnType(TClassType::*function)(TArguments ...) const)
        {
            mFunction = Details::CreateMemberFunction(className, function);
        }

        TReturnType Invoke(TArguments ... arguments) const // first bug : camnot make sure if is const
        {
            if (mFunction->IsConstant())
            {
                return mFunction->Invoke(arguments ...);
            }
            else
            {
                throw "cannot return type because function is not constant";
            }
        }

        TReturnType Invoke(TArguments ... arguments)
        {
            return mFunction->Invoke(arguments ...);
        }

        void RemoveAll()
        {
            delete mFunction;
        }

        int GetCount() const
        {
            return mFunction != nullptr ? 1 : 0;
        }

    private:
        Details::Function<TReturnType, TArguments ...> * mFunction;
    };

    // return type is void, have many functions
    template <typename ... TArguments>
    class Delegate <void, TArguments ...>
    {
    public:
        typedef Delegate<void, TArguments ...> Self;

    public:
        Delegate() = default;

        Delegate(const Self *) = delete;

        ~Delegate()
        {
            RemoveAll();
        }

        Self & operator = (const Self &) = delete;

    public:
        void Add(void(*function)(TArguments ...))
        {
            mFunctions.PushBack(Details::CreateStaticFunction(function));
        }

        template <typename TClassType>
        void Add(TClassType * className, void(TClassType::*function)(TArguments ...))
        {
            mFunctions.PushBack(Details::CreateMemberFunction(className, function));
        }

        template <typename TClassType>
        void Add(TClassType * className, void(TClassType::*function)(TArguments ...) const)
        {
            mFunctions.PushBack(Details::CreateMemberFunction(className, function));
        }

        void Invoke(TArguments ... arguments) const
        {
            for (auto i : mFunctions)
            {
                if (i->IsConstant())
                {
                    i->Invoke(arguments ...);
                }
            }
        }

        void Invoke(TArguments ... arguments)
        {
            for (auto i : mFunctions)
            {
                i->Invoke(arguments ...);
            }
        }

        void RemoveAll()
        {
            for (auto i : mFunctions)
            {
                delete i;
            }

            mFunctions.Clear();
        }

        int GetCount() const
        {
            return mFunctions.GetSize();
        }

    private:
        Array<Details::Function<void, TArguments ...> *> mFunctions;
    };
}