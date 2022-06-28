//
// Created by karan on 19-06-2022.
//

#include "Parser.hpp"


namespace simpleparser {

    using namespace std;



    void Parser::parse(vector<Token> &tokens) {
        vector<Token>:: iterator currentToken =  tokens.begin();

        // I will use while because I am not progressing one token at a time
        while(currentToken != tokens.end()) {

        }


    }

    optional<Token> Parser::expectIdentifier(const string &name) {
        return nullptr;
    }
}
