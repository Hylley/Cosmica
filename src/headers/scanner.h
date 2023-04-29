#ifndef SCANNER_H
#define SCANNER_H

#include "main.h"
#include "debug.h"
#include "parser.h"

#include "syntree/block.h"

// std::unordered_map<std::string, std::any> dict;
void Lexer(std::string&	raw, BlockNode&	parent, std::string& fileName);


#endif