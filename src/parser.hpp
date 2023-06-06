#pragma once

#include <regex>
#include <string>

#include "debug.hpp"
#include "syntree/node.hpp"

extern std::regex invisibles;
extern std::regex tabs;
extern std::regex variableName;
extern std::regex singleLineComment;
extern std::regex multiLineComment[3];
extern std::regex ifCases[3];
extern std::regex variableAssign;
extern std::regex arithmeticOperator;

Node* Parse(std::string& line, int tab_level, std::string& file_name, int& line_number);