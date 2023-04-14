#ifndef PARSER_H
#define PARSER_H

#include "main.h"
#include "debug.h"
#include "scanner.h"
#include "interpreter.h"

#include "../syntree/headers/block.h"
#include "../syntree/headers/variable_assign.h"

extern std::regex invisibles;
extern std::regex singleLineComment;
extern std::regex multiLineComment[3];
extern std::regex stringLiteral;
extern std::regex ifCase[3];
extern std::regex variableAssign;
extern std::regex validVariableName;
extern std::regex equalCompare;

void Parse(std::string line, BlockNode&	parent, std::string& fileName, int lineNumber, bool& isMultiCommented);

#endif