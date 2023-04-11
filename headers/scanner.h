#ifndef SCANNER_H
#define SCANNER_H

#include "prch.h"
#include "syntree.h"
#include <regex>

std::vector<std::string> Lexer(std::string&	raw, BlockNode&	parent, std::string& fileName);

extern std::regex se;
extern std::regex variableAssign;
extern std::regex equalCompare;
extern std::regex invisible;

#endif