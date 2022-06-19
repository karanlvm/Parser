//
// Created by karan on 18-06-2022.
//

#pragma once

#include <vector>
#include <string>

namespace simpleparser {

    using namespace std;

    enum TokenType{
        WHITESPACE,  // No token ever has this type
        IDENTIFIER,
        INTEGER_LITERAL,
        DOUBLE_LITERAL,
        STRING_LITERAL,
        OPERATOR,
        STRING_ESCAPE_SEQUENCE,
        POTENTIAL_DOUBLE,
    };

    class Token{
    public:
        enum TokenType mType{WHITESPACE};
        string mText;
        size_t mStartOffset{0};
        size_t mEndOffset{0};
        size_t mLineNumber{0};
    };

    class Tokenizer{
    public:
        vector<Token> parse(const string &inProgram);

    private:
        void endToken(Token &token, vector<Token> &tokens );
    };
}