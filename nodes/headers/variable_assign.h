#ifndef VARIABLE_ASSIGN_NODE_H
#define VARIABLE_ASSIGN_NODE_H

#include "node.h"
#include "literal.h"

class VariablAssign : public Node
{
	public:
		std::string name;
		LiteralNode* literal;
};

#endif