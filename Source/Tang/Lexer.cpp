#include "Lexer.h"

#include <cstring>

using namespace std;

namespace
{
    bool IsBracket(char c)
    {
        return c == '(' || c == ')' || c == '{' || c == '}';
    }

    bool IsBlank(char c)
    {
        return c == ' ' || c == '\n' || c == '\r';
    }

    bool IsDigit(char c)
    {
        return isdigit(c);
    }

    bool IsAlpha(char c)
    {
        return isalpha(c);
    }

    bool IsNumber(char c)
    {
        return c >= '0' && c <= '9';
    }

    bool IsSymbol(char c)
    {
        return !IsDigit(c) && !IsAlpha(c) && !IsNumber(c) && !IsBracket(c) && !IsBlank(c) && c != '\0';
    }
}

XC_BEGIN_NAMESPACE_1(Tang)
{
    bool Lexer::IsHasNext() const
    {
        return mCurrentIndex < mTokenArray.GetSize();
    }

    void Lexer::MoveToFront()
    {
        mCurrentIndex = 0;
    }

    Token Lexer::GetNextToken()
    {
        if (mCurrentIndex >= mTokenArray.GetSize())
        {
            throw "error";
        }

        return mTokenArray[mCurrentIndex++];
    }

    Token Lexer::GetPreviousToken()
    {
        return mTokenArray[--mCurrentIndex];
    }

    Token Lexer::LookAhead(int more)
    {
        if (mCurrentIndex + more - 1>= mTokenArray.GetSize())
        {
            return Token("END", Token::Type::End);
        }

        return mTokenArray[mCurrentIndex + more - 1];
    }

    void Lexer::Solve()
    {
        int position = 0;
        while (true)
        {
            if (position >= mSourceCode.size())
            {
                break;
            }

            char c = mSourceCode[position];
            std::string newString;

            if (IsBlank(c))
            {
                ++position;
                continue;
            }

            if (c == '\0')
            {
                break;
            }

            if (c == '-')
            {
                if (IsNumber(mSourceCode[position + 1]))
                {
                    newString = "-";
                    ++position;

                    while (IsNumber(mSourceCode[position]))
                    {
                        newString += mSourceCode[position];
                        ++position;
                    }
                    
                    AddString(newString);
                    continue;
                }
                else
                {
                    AddString("-");
                    ++position;
                    continue;
                }
            }
            else if (IsDigit(c))
            {
                std::string newString;
                while (IsDigit(mSourceCode[position]))
                {
                    newString += mSourceCode[position];
                    ++position;
                }

                AddString(newString);
                continue;
            }
            else if (IsBracket(c))
            {
                AddString(std::string(1, c));
                ++position;
                continue;
            }
            else if (IsAlpha(c))
            {
                std::string newString;
                while (IsNumber(mSourceCode[position]) || IsAlpha(mSourceCode[position]))
                {
                    newString += mSourceCode[position];
                    ++position;
                }

                AddString(newString);
                continue;
            }
            else if (c == ';')
            {
                ++position;
                AddString(";");
                continue;
            }
            else if (IsSymbol(c))
            {
                std::string newString;
                while (IsSymbol(mSourceCode[position]))
                {
                    newString += mSourceCode[position];
                    ++position;
                }
                AddString(newString);
                continue;
            }
            else
            {
                throw "Error";
            }
        }

        mTokenArray.PushBack(Token("", Token::Type::End));
    }

    void Lexer::AddString(std::string s)
    {
        mTokenArray.PushBack(ConvertStringToToken(s));
    }

    Token Lexer::ConvertStringToToken(std::string s)
    {
        if (s == "(" || s == ")")
        {
            return Token(s, Token::Type::Bracket);
        }
        else if (IsAlpha(s[0]))
        {
            return Token(s, Token::Type::Name);
        }
        else if (IsDigit(s[0]) || s[0] == '-' && s.length() > 1 && IsDigit(s[1]))
        {
            return Token(s, Token::Type::Number);
        }
        else
        {
            return Token(s, Token::Type::None);
        }
    }

} XC_END_NAMESPACE_1;