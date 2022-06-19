#include "Tokenizer.hpp"
#include <iostream>

using namespace std;
using namespace simpleparser;

int main() {
    std::cout << "Simple Parser 0.1\n" << endl;

    FILE * fh = fopen("C:\\Users\\karan\\Documents\\GitHub\\Parser\\test.myc", "r");
    if (!fh) { cerr <<"Cant Find the file." <<endl;}
    fseek(fh, 0, SEEK_END);
    size_t fileSize = ftell(fh);
    fseek(fh, 0, SEEK_SET);
    string fileContents(fileSize, ' '); //Buffer Created
    fread((void *) fileContents.data(), 1, fileSize, fh);

    cout<< fileContents <<endl<< endl;

    Tokenizer tokenizer;
    vector<Token> tokens = tokenizer.parse(fileContents);

    for(Token curToken : tokens) {
        curToken.debugPrint();
    }

    return 0;
}
