#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "main.h"
#include "parser.h"
#include "../syntree/headers/block.h"
#include "../syntree/headers/variable_assign.h"

void implementVariableAssign(std::smatch& matches, BlockNode& parent, std::string& fileName, int &lineNumber);

#endif