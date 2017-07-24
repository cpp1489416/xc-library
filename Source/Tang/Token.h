#pragma once
#include <string>
#include "../Core/Core.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    class Token
    {
    public:
        enum class Type
        {
            None, End, Bracket, Number, Operator, Keyword, Name,
        };

    public:
        Token(std::string string = "", Type type = Type::None);

    public:
        std::string GetString() const
        {
            return mString;
        }

        Type GetType() const
        {
            return mType;
        }
        
    private:
        std::string mString;
        Type mType;

        friend class Parser;
        friend class Lexer;
    };
      
} XC_END_NAMESPACE_1;