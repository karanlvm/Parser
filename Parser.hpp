//
// Created by karan on 19-06-2022.
//

#pragma once
#include "Tokenizer.hpp"
#include <optional>

namespace simpleparser {

    using namespace std;


    class Parser {
    public:
        void parse(vector<Token> &tokens);

    private:
        optional<Token> expectIdentifier(const string& name);
        vector<Token>::iterator mCurrentToken;

    };

}