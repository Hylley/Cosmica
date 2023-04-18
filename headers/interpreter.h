#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "main.h"
#include "parser.h"
#include "syntree/block.h"
#include "syntree/if.h"

Node* generateOp(std::smatch& matches, std::string& fileName, int &lineNumber);
void implementIf(std::smatch& matches, BlockNode* parent, std::string& fileName, int &lineNumber, std::unordered_map<unsigned int, BlockNode*>& tabtable, int tabLevel);

#endif