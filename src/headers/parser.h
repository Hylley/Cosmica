#ifndef PARSER_H
#define PARSER_H

#include "main.h"
#include "debug.h"
#include "scanner.h"
#include "interpreter.h"

#include "syntree/block.h"

extern std::regex invisibles;
extern std::regex tabs;
extern std::regex variableName;
extern std::regex singleLineComment;
extern std::regex multiLineComment[3];
extern std::regex ifCases[3];
extern std::regex variableAssign;
extern std::regex arithmeticOperator;
extern std::regex inteiro;
extern std::regex fita;
extern std::regex flutuante;
extern std::regex booleano;

void Parse(std::string line, BlockNode& parent, std::string& fileName, int lineNumber, bool& isMultiCommented, std::unordered_map<unsigned int, BlockNode*>& tabtable);
unsigned int findTabLevel(std::string tabs, std::unordered_map<unsigned int, BlockNode*>& tabtable);
void unelevate(std::unordered_map<unsigned int, BlockNode*>& tabtable, unsigned int tabLevel);

#endif