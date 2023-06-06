#pragma once

#include <string>
#include <regex>
#include "debug.hpp"
#include "syntree/block.hpp"

extern std::regex tabs;
extern std::regex invisibles;
extern std::regex single_line_comment;
extern std::regex multi_line_comment[3];

void Scan(std::string& line, bool& is_multi_line_commented, int& tab_level, std::string& filtered_line, std::string& file_name, int& line_number);