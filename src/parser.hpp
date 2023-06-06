#pragma once

#include <regex>
#include <string>

#include "debug.hpp"
#include "syntree/node.hpp"
#include "syntree/block.hpp"

#pragma region regex declaration
extern std::regex invisibles;
extern std::regex tabs;
extern std::regex variableName;
extern std::regex single_line_comment;
extern std::regex multi_line_comment[3];
#pragma endregion

Node* Parse(std::string& line, int tab_level, std::unordered_map<unsigned int, Block*>& tab_table, std::string& file_name, int& line_number);