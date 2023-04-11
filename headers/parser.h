#ifndef PARSER_H
#define PARSER_H

#include "prch.h"
#include "syntree.h"
#include "debug.h"
#include "scanner.h"
#include <regex>

extern std::regex invisibles;
extern std::regex singleLineComment;
extern std::regex multiLineComment[3];
extern std::regex stringLiteral;
extern std::regex ifCase[3];
extern std::regex variableAssign;
extern std::regex equalCompare;

void Parse(std::string& line, BlockNode&	parent, std::string& fileName, int lineNumber, bool& isMultiCommented);

#endif