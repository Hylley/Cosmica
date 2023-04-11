#ifndef SCANNER_H
#define SCANNER_H

#include "prch.h"
#include "syntree.h"
#include <regex>

std::vector<std::string> Lexer(std::string&	raw, BlockNode&	parent, std::string& fileName);

extern std::regex invisibles;
extern std::regex singleLineComment;
extern std::regex multiLineComment[3];
extern std::regex se;
extern std::regex variableAssign;
extern std::regex equalCompare;

#endif