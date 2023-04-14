#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "main.h"
#include "parser.h"
#include "../syntree/headers/block.h"
#include "../syntree/headers/variable_assign.h"

void implementVariableAssign(std::smatch& matches, BlockNode* parent, std::string& fileName, int &lineNumber);
void implementIf(std::smatch& matches, BlockNode* parent, std::string& fileName, int &lineNumber, std::unordered_map<unsigned int, BlockNode*>& tabtable, int tabLevel);

#endif