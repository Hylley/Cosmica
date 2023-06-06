#pragma once

#include <string>
#include <regex>

#include "parser.hpp"
#include "debug.hpp"
#include "syntree/block.hpp"

void Scan(std::string& line, bool& is_multi_line_commented, int& tab_level, std::string& filtered_line, std::string& file_name, int& line_number);