#pragma once

#include "../Core/Core.h"
#include "Token.h"

XC_BEGIN_NAMESPACE_1(Tang)
{
    class Lexer
    {
    public:
        explicit Lexer(std::string sourceCode)
        {
            mSourceCode = sourceCode;
            Solve();
        } 

    public:
        bool IsHasNext() const;

        void MoveToFront();

        Token GetNextToken();

        Token GetPreviousToken();

        Token LookAhead();

    private:
        void Solve();

        void AddString(std::string s);

        Token ConvertStringToToken(std::string s);

    private:
        XC::Array<Token> mTokenArray;
        std::string mSourceCode;
        int mCurrentIndex = 0;
    };

    

} XC_END_NAMESPACE_1;