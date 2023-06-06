#pragma once

#include <unordered_map>

#include "node.hpp"
#include "eval.hpp"
#include "literal.hpp"

class Block : public Node, public Evaluable
{
	public:
		std::unordered_map<std::string, Block*> functions;
		std::unordered_map<std::string, Literal*> symbolTable;

		void Evaluate() override;
};