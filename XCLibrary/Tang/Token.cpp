#include "Token.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    Token::Token(std::string string, Token::Type type)
    {
        mString = string;
        mType = type;
    }
} XC_END_NAMESPACE_1;