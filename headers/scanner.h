#ifndef SCANNER_H
#define SCANNER_H

#include "prch.h"
#include "debug.h"
#include "parser.h"
// #include <unordered_map>

// std::unordered_map<std::string, std::any> dict;
void Lexer(std::string&	raw, BlockNode&	parent, std::string& fileName);
std::vector<std::string> Tokenize(std::string &str, char delimiter);
std::string findDataType(std::string& input);
bool isValidDataType(std::string& value);


#endif