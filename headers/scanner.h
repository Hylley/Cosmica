#ifndef SCANNER_H
#define SCANNER_H

#include "prch.h"

std::vector<std::vector<std::string>> Tokenize(std::string rawContent);
std::vector<std::string> SplitLine(std::string &line);

#endif