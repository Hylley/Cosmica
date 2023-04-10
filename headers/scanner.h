#ifndef SCANNER_H
#define SCANNER_H

#include "prch.h"
#include "syntree.h"

std::vector<std::string> Lexer(std::string& raw, BlockNode& parent);

#endif