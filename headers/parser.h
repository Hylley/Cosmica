#ifndef PARSER_H
#define PARSER_H

#include "prch.h"
#include "syntree.h"

BlockNode GenerateAbstractSyntaxTree(std::vector<std::vector<std::string>> tokens);

#endif