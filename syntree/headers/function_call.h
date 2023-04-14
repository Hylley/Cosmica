#ifndef FUNCTION_CALL_NODE_H
#define FUNCTION_CALL_NODE_H

#include "node.h"
#include "literal.h"

class FunctionCallNode : public Node
{
	public:
		std::string name;
		std::vector<LiteralNode*> arguments;
};

#endif