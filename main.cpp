#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>

void RunLexer(Lexer* lexer, const std::string &fileName);

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: interpreter <inputFile>" << std::endl;
        return 0;
    }

    auto lexer = new Lexer();
    RunLexer(lexer, argv[1]);
    auto parser = new Parser(lexer->GetTokens());
    auto interpreter = new Interpreter(parser->Parse());
    //std::cout << interpreter->ToString();
    interpreter->Interpret();

    delete lexer;
    delete parser;
    return 0;
}

void RunLexer(Lexer* lexer, const std::string &fileName) {
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cout << "Could not open file." << std::endl;
        exit(1);
    }
    std::ostringstream ss = std::ostringstream{};
    ss << inFile.rdbuf();
    std::string inp = ss.str();
    lexer->Run(inp);
}