//
// Created by karan on 18-06-2022.
//

#include "Tokenizer.hpp"
#include <stdexcept>

namespace simpleparser {

    using namespace std;

    vector<Token> simpleparser::Tokenizer::parse(const string &inProgram) {
        vector<Token> tokens;
        Token currentToken;

        currentToken.mLineNumber = 1;


        for (char currCh: inProgram) {
            if (currentToken.mType == STRING_ESCAPE_SEQUENCE) {
                switch (currCh) {
                    case 'n':
                        currentToken.mText.append(1, '\n');
                        break;
                    case 'r':
                        currentToken.mText.append(1, '\r');
                        break;
                    case 't':
                        currentToken.mText.append(1, '\t');
                        break;
                    case '\\':
                        currentToken.mText.append(1, '\\');
                        break;
                    default:
                        throw runtime_error(string("Unknown escape sequence: \\") + string(1, currCh) + " on Line" +
                                            to_string(currentToken.mLineNumber) + ".");
                        break;
                }
            }

            switch (currCh) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (currentToken.mType == WHITESPACE) {
                        currentToken.mType = INTEGER_LITERAL;
                        currentToken.mText.append(1, currCh);
                    } else {
                        currentToken.mText.append(1, currCh);
                    }
                    break;

                case '.':
                    if (currentToken.mType == WHITESPACE) {
                        currentToken.mType = POTENTIAL_DOUBLE;
                        currentToken.mText.append(1, currCh);
                    } else if(currentToken.mType == INTEGER_LITERAL){
                        currentToken.mType = DOUBLE_LITERAL;
                        currentToken.mText.append(1, currCh);
                    }
                    else if(currentToken.mType == STRING_LITERAL){
                        currentToken.mType = DOUBLE_LITERAL;
                        currentToken.mText.append(1, currCh);
                    }
                    else{
                        endToken(currentToken, tokens);
                        currentToken.mType = OPERATOR;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken, tokens);
                    }
                    break;


                case '{':
                case '}':
                case '(':
                case ')':
                case '=':
                case '-':
                case ';':
                case ',':
                    if (currentToken.mType == STRING_LITERAL) {
                        endToken(currentToken, tokens);
                        currentToken.mType = OPERATOR;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken, tokens);
                    } else {
                        currentToken.mText.append(1, currCh);
                    }
                    break;

                case ' ':
                case '\t':
                    endToken(currentToken, tokens);
                    break;
                    // r is for unix and combination of both is used for windows native files
                case '\r':
                case '\n':
                    endToken(currentToken, tokens);
                    ++currentToken.mLineNumber;
                    break;

                case '"':
                    if (currentToken.mType != STRING_LITERAL) {
                        endToken(currentToken, tokens);
                        currentToken.mType = STRING_LITERAL;
                        currentToken.mText.append(1, currCh);
                    } else if (currentToken.mType == STRING_LITERAL) {
                        endToken(currentToken, tokens);
                    }
                    break;

                case '\\':
                    if (currentToken.mType == STRING_LITERAL) {
                        currentToken.mType = STRING_ESCAPE_SEQUENCE;
                    } else {
                        endToken(currentToken, tokens);
                        currentToken.mType = OPERATOR;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken, tokens);
                    }

                    break;

                default:
                    break;
            }
        }


        return tokens;
    }


    void Tokenizer::endToken(Token &token, vector<Token> &tokens) {
        if (token.mType != WHITESPACE) {
            tokens.push_back(token);
        }
        // Push to token list and clear the string, so we can move to the next
        token.mType = WHITESPACE;
        token.mText.erase();
    }
}